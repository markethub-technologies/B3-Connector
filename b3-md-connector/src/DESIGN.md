# B3 Market Data Connector – Diseño Consolidado (Contrato)

## 0. Objetivo
Servicio de distribución de Market Data para B3 (UMDF vía OnixS):
- Recibe updates de libro desde OnixS.
- Materializa snapshots MBO (Market By Order) con ventana acotada (hasta 256 órdenes/lado).
- Agrega a MBP (Market By Price) Top-N niveles (default: Top 5).
- Distribuye snapshots serializados vía ZMQ PUB (endpoint único).
- No toma decisiones de negocio, no valida, no normaliza dominio.
- Prioridad absoluta: latencia estable (p99) y no bloquear el feed.

### Arquitectura Implementada
```
OnixS Feed → MarketDataEngine → MdPublishPipeline (sharding)
                                        ↓
                                [Worker Shards × N]
                                        ↓
                                 Aggregation MBO→MBP
                                        ↓
                                ZmqPublishConcentrator
                                        ↓
                                   ZMQ PUB Socket
```

---

## 1. Invariantes (NO negociables)

### I1 — Hot path minimalista (callback OnixS)
En el callback (`MarketDataEngine::onOrderBookUpdated`):
- NO bloquea
- NO aloca en heap
- NO serializa
- NO loguea
- NO lanza exceptions por casos esperables

Solo:
1) Lee hasta 256 órdenes por lado del libro OnixS
2) Construye `OrdersSnapshot` (POD, ~8KB) en stack
3) Filtra market orders (precio nulo)
4) Hace `pipeline.tryEnqueue(snapshot)` → SPSC lock-free

Si la cola está llena:
- drop + counter/telemetry
- jamás backpressure hacia el feed

**Implementación**: `OnixsOrdersSnapshotBuilder::buildFromBook()` copia la ventana MBO.
**Target latency**: <500ns (callback → enqueue)

### I2 — Copia explícita y desacople de OnixS
- `OrderBook`/objetos UMDF OnixS NO se guardan ni se referencian fuera del callback.
- Se copia la ventana MBO (hasta 256 órdenes/lado) a `OrdersSnapshot` (estructura propia, POD).
- **Motivo**: thread-safety, lifetime del SDK, desacople.

**Implementación**:
- `IOrderBookView` interface abstrae OnixS `OrderBook`
- `OnixOrderBookView` adapta tipos OnixS → interface genérica
- Permite testing sin SDK (ver `FakeOrderBook` en tests)

### I3 — Concurrencia por sharding (orden garantizado por instrumento)
- `shard = (instrumentId * 11400714819323198485ull) % shardCount`
  - Hash multiplicativo de Knuth mejora distribución
  - Previene clustering de IDs secuenciales

**Garantías**:
- FIFO estricto por instrumento (mismo instrumento → mismo shard)
- Sin head-of-line blocking entre instrumentos (shards paralelos)
- Escalabilidad horizontal simple (configurable vía `md.shards`)

**Implementación**:
- `MdPublishPipeline::shardFor()` computa shard
- `MdPublishPipeline::tryEnqueue()` rutea a worker correspondiente
- **Test coverage**: `test_md_pipeline.cpp` verifica FIFO con 10,000 eventos/instrumento

### I4 — Workers dedicados + colas SPSC lock-free
- Un `MdPublishWorker` por shard (thread dedicado).
- Cada worker consume de su SPSC ring buffer prealocado (capacidad: 4096).
- Procesamiento secuencial per-worker:
  1. Dequeue `OrdersSnapshot` de cola SPSC
  2. Agregar MBO → MBP Top-5 (`MboToMbpAggregator`)
  3. Serializar a protobuf (`MdSnapshotMapper`, actualmente stub)
  4. Resolver topic (`InstrumentTopicMapper`: "PETR4" o "IID:123456")
  5. Publicar a `ZmqPublishConcentrator` (otro SPSC)

**Política de overflow**:
- drop (no bloquea)
- counters + health metrics (emitidos cada 5s)

**Implementación**:
- `SnapshotQueueSpsc<OrdersSnapshot, 4096>` lock-free (atomics únicamente)
- Cache-line aligned (64B) para prevenir false sharing
- `try_enqueue` / `try_dequeue` wait-free O(1)

**Graceful shutdown**:
- `stop(true)`: drain mode (procesa cola completa antes de terminar)
- `stop(false)`: fast shutdown (retorna inmediatamente, dropea pendientes)

### I5 — Publishing y Logging no deben afectar el core
- `core/` no conoce sockets/endpoints.
- Workers llaman `IPublishSink` interface con `SerializedEnvelope` (POD, topic + payload).
- IO lento / backpressure / fallas de publish:
  - nunca bloquean indefinidamente al worker
  - se traducen a drop + counters + logs rate-limited

**Publishing Architecture**:
- `ZmqPublishConcentrator` (fan-in pattern):
  - N colas SPSC (una por worker) → 1 socket ZMQ PUB
  - Round-robin batching (procesa hasta 8 eventos/shard/iteración)
  - Single endpoint (`tcp://*:8081` configurable)
  - Slow joiner mitigation: sleep 1.5s en startup
- **Beneficio**: Subscribers conectan a un único endpoint, simplifica configuración

**Logging**:
- spdlog NO se invoca desde hot path ni desde el loop del worker.
- Los producers encolan `LogEvent` POD (56 bytes) en cola SPSC (`LogQueueSpsc`)
- `SpdlogLogPublisher` (thread dedicado por producer) formatea y emite a spdlog
- **Formato estructurado**: LogLevel, Component, Code, args (ver `telemetry/LogEvent.hpp`)

**Implementación**:
- `IPublishSink` interface permite testing sin ZMQ (ver `FakePublishSink` en tests)
- `SerializedEnvelope`: struct flat (16KB payload, 128B topic) sin punteros (SPSC-safe)

---

## 2. Contratos de overflow (explícitos)

**SnapshotQueueSpsc llena** (OnixS → Worker):
- `pipeline.tryEnqueue(snapshot)` retorna `false`
- Drop newest update (no bloquea callback OnixS)
- Incrementa `dropped_total` counter
- Worker emite `LogEvent` (Code::Drops, Code::QueueSaturated)

**LogQueueSpsc llena** (Worker → SpdlogLogPublisher):
- `logPublisher.try_publish(event)` retorna `false`
- Drop log event (prioriza data path sobre telemetría)
- Incrementa `dropped()` counter interno
- Se reporta en siguiente HealthTick

**Publishing saturado/falla** (Worker → Concentrator):
- `sink.tryPublish(event)` retorna `false` (cola concentrator llena)
- Drop snapshot (no bloquea worker)
- Incrementa `dropped_total` counter
- Concentrator emite warning rate-limited

**ZMQ send failure** (Concentrator → Socket):
- `socket.sendMultipart()` retorna `false` (ej. slow subscriber backpressure)
- Drop message (no bloquea thread concentrator)
- Incrementa `dropped_total` counter
- Log error con instrumentId (si parseable del event)

---

## 3. Métricas implementadas (health monitoring)

### Por Worker (emitidas cada 5s vía LogEvent::HealthTick)
```cpp
struct WorkerHealth {
    uint64_t enqueued_total;    // Acumulado encolado desde inicio
    uint64_t published_total;   // Acumulado publicado desde inicio
    uint64_t dropped_total;     // Acumulado dropeado (cola llena)
    uint32_t queue_size;        // Tamaño actual de cola SPSC
};
```

**Formato log**:
```
[Health] Worker 0 | Queue: 128 | Enq: +1234 | Pub: +1230 | Drop: +4
```

### Por Concentrator (emitidas cada 5s)
```cpp
struct ConcentratorHealth {
    uint64_t sent_total;        // Acumulado enviado a ZMQ
    uint64_t dropped_total;     // Acumulado dropeado (todas las colas)
    uint32_t queue_sizes[N];    // Tamaño por shard
};
```

**Formato log**:
```
[Health] Concentrator | Sent: +5678 | Drop: +12 | Queues: [32, 45, 28, 51]
```

### Eventos adicionales
- **Startup/Shutdown**: Lifecycle de workers y concentrator
- **Drops**: Emitido cuando `dropped_total` incrementa (include instrumentId si disponible)
- **QueueSaturated**: Emitido cuando queue_size > 90% capacidad
- **LogDrops**: Telemetry queue drops (meta-log)
- **MapMiss**: Symbol no encontrado en `InstrumentRegistry` (fallback a IID:*)

---

## 4. Fuera de alcance (a propósito)
- Validaciones de negocio (ej. precios fuera de rango)
- Normalización de mensajes (se preserva semántica B3/OnixS)
- Persistencia (no hay replay, no hay tape)
- Lógica por cuenta (el connector no sabe de cuentas/estrategias)
- Throttling de mercado (no rate limiting artificial)
- Auditoría por evento (solo counters agregados, no log per-update)
- Conflation (se envía cada update, no se colapsan snapshots)
- Circuit breakers (decisión upstream, no en connector)

---

## 5. Estado de Implementación

### ✅ Completado
- [x] Pipeline sharding con hash Knuth (`MdPublishPipeline`)
- [x] Workers con SPSC queues lock-free (`MdPublishWorker`)
- [x] Concentrator fan-in con round-robin batching (`ZmqPublishConcentrator`)
- [x] Agregación MBO → MBP Top-N (`MboToMbpAggregator`)
- [x] Telemetría estructurada off-hot-path (`LogEvent`, `SpdlogLogPublisher`)
- [x] Instrument registry thread-safe (`InstrumentRegistry` con shared_mutex)
- [x] Topic mapping con fallback (`InstrumentTopicMapper`: "SYMBOL" o "IID:*")
- [x] Test suite completo (FIFO ordering, worker lifecycle, aggregation, health metrics)

### 🚧 Pendiente (TODOs de alta prioridad)

#### 1. ZMQ Socket Implementation (ZmqPublishConcentrator.hpp:125-138)
**Status**: Stub actual
```cpp
struct ZmqPubSocket {
    explicit ZmqPubSocket(const std::string& endpoint) {
        // TODO: bind socket pub con tu lib
    }
    bool sendMultipart(...) noexcept {
        // TODO: 2 frames: topic + payload
        return true;  // Stub
    }
};
```

**Acción**:
- Usar `cppzmq` (ya linkeado en CMakeLists)
- `zmq::socket_t sock(ctx, zmq::socket_type::pub);`
- `sock.bind(endpoint);`
- `sock.send(zmq::buffer(topic), zmq::send_flags::sndmore);`
- `sock.send(zmq::buffer(payload));`

#### 2. Instrument Registry Population (main.cpp:127-128)
**Status**: Registro vacío (fallback a "IID:*" en todos los topics)

**Acción**:
- Instanciar `B3InstrumentRegistryListener listener(registry);`
- Registrar con handler: `handler.registerListener(&listener);`
- Listener captura `SecurityDefinition_12` messages
- Extrae `securityId()`, `symbol()` y llama `registry.upsert()`
- Ejecuta durante warmup (antes de market open)

#### 3. Protobuf Serialization (MdSnapshotMapper.hpp:8-26)
**Status**: Stub key=value format
```cpp
size_t mapAndSerialize(const BookSnapshot& book, uint8_t* out, size_t cap) {
    // TODO: serializar BookSnapshot a protobuf
    // actualmente stub (key=value)
    return std::snprintf(reinterpret_cast<char*>(out), cap,
                         "iid=%lu ts=%lu bidCnt=%u askCnt=%u",
                         book.instrumentId, book.exchangeTsNs,
                         book.bidCount, book.askCount);
}
```

**Acción**:
- Definir `md_snapshot.proto`:
  ```protobuf
  message BookSnapshot {
      uint64 instrument_id = 1;
      uint64 exchange_ts_ns = 2;
      repeated Level bids = 3;
      repeated Level asks = 4;
  }
  message Level {
      int64 price = 1;
      int64 qty = 2;
  }
  ```
- Generar C++ con `protoc`
- Serializar: `book_proto.SerializeToArray(out, cap);`
- Retornar `book_proto.ByteSizeLong();`

### ⚠️ TODOs de prioridad media

#### 4. Exchange Timestamp Extraction (OnixsOrdersSnapshotBuilder.hpp:34)
**Status**: Usando `nowNs` (system timestamp) en lugar de exchange timestamp

**Problema**: OnixS `OrderBook` no expone timestamp de exchange directamente

**Opciones**:
- A) Extraer de `SbeMessage` en callback `onOrderBookChanged()`
- B) Mantener map separado `instrumentId → lastExchangeTs` (evitar heap en hot path)

#### 5. Bid/Ask Ordering Validation (OnixsOrdersSnapshotBuilder.hpp:40-42)
**Status**: Asumiendo bids ascending (best at end), asks ascending (best at start)

**Acción**: Agregar assertions runtime en producción para verificar suposiciones

---

## 6. Referencias de Código

### Componentes Core
- `MarketDataEngine.hpp` - Entry point desde OnixS
- `MdPublishPipeline.hpp` - Orquestador de sharding (76 LOC)
- `MdPublishWorker.hpp` - Worker thread (279 LOC)
- `OrdersSnapshot.hpp` - MBO snapshot (POD, ~8KB)
- `BookSnapshot.hpp` - MBP snapshot (POD, ~200B)
- `SnapshotQueueSpsc.hpp` - SPSC lock-free queue (57 LOC)
- `MboToMbpAggregator.hpp` - Aggregation logic

### Componentes Mapping
- `InstrumentRegistry.hpp` - InstrumentId → Symbol registry (thread-safe)
- `InstrumentTopicMapper.hpp` - Topic resolution ("PETR4" o "IID:*")
- `MdSnapshotMapper.hpp` - Protobuf serialization (stub)

### Componentes Publishing
- `IPublishSink.hpp` - Interface para publish targets
- `SerializedEnvelope.hpp` - POD para inter-thread transport (16KB)
- `ZmqPublishConcentrator.hpp` - Fan-in concentrator (232 LOC)

### Componentes Telemetry
- `LogEvent.hpp` - Telemetry POD (56B)
- `LogQueueSpsc.hpp` - SPSC queue para logs (45 LOC)
- `SpdlogLogPublisher.hpp` - Consumer thread (129 LOC)

### Componentes OnixS
- `OnixsOrderBookListener.hpp` - Adapter OnixS → Engine
- `OnixOrderBookView.hpp` - Adapter OnixS → IOrderBookView (117 LOC)
- `OnixsOrdersSnapshotBuilder.hpp` - MBO window builder (132 LOC)
- `B3InstrumentRegistryListener.hpp` - SecurityDefinition listener

### Tests
- `test_md_pipeline.cpp` - FIFO ordering (10,000 events/instrument)
- `test_md_worker.cpp` - Worker lifecycle (drain mode, health)
- `test_mbo_to_mbp_aggregator.cpp` - Aggregation correctness
- `FakePublishSink.hpp` - Test double para ZMQ
- `FakeInstrumentTopicMapper.hpp` - Test double para mapper

---

**Documento Version**: 2.0
**Última Actualización**: 2025-12-30
**Commit**: bcec7bc (Replace direct publishing with sharded publish pipeline and ZMQ concentrator)
