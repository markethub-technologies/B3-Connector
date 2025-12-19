# B3 Market Data Connector – Diseño Consolidado (Contrato)

## 0. Objetivo
Servicio de distribución de Market Data para B3 (UMDF vía OnixS):
- Recibe updates de libro desde OnixS.
- Materializa snapshots Top-N (DEPTH, default 5).
- Distribuye snapshots serializados vía publishers (ej. ZMQ).
- No toma decisiones de negocio, no valida, no normaliza dominio.
- Prioridad absoluta: latencia estable (p99) y no bloquear el feed.

---

## 1. Invariantes (NO negociables)

### I1 — Hot path minimalista (callback OnixS)
En el callback:
- NO bloquea
- NO aloca en heap
- NO serializa
- NO loguea
- NO lanza exceptions por casos esperables

Solo:
1) lee Top-N del libro
2) construye `BookSnapshot` (POD) en stack
3) hace `try_enqueue` al pipeline

Si la cola está llena:
- drop + counter/telemetry
- jamás backpressure hacia el feed

### I2 — Copia explícita y desacople de OnixS
- `OrderBook`/objetos UMDF OnixS NO se guardan ni se referencian fuera del callback.
- Se copia únicamente el Top-N a una estructura propia (`BookSnapshot`).
Motivo: thread-safety, lifetime del SDK, desacople.

### I3 — Concurrencia por sharding (orden garantizado por instrumento)
- `shard = hash(instrumentId) % shardCount`
Garantías:
- FIFO por instrumento (y por shard)
- sin head-of-line blocking entre instrumentos
- escalabilidad horizontal simple

### I4 — Workers dedicados + colas SPSC lock-free
- Un `MdPublishWorker` por shard.
- Cada worker consume de su SPSC ring buffer prealocado.
- Procesamiento secuencial: mapear → serializar → publicar.
Política de overflow:
- drop (no bloquea)
- counters + health

### I5 — Publishing y Logging no deben afectar el core
- `core/` no conoce sockets/endpoints.
- Workers llaman `IMdPublisher` con bytes ya serializados.
- IO lento / backpressure / fallas de publish:
  - nunca bloquean indefinidamente al worker
  - se traducen a drop + counters + logs rate-limited

Logging:
- spdlog NO se invoca desde hot path ni desde el loop del worker.
- los producers encolan `LogEvent` POD en una cola SPSC
- threads dedicados formatean y emiten a spdlog

---

## 2. Contratos de overflow (explícitos)
- SnapshotQueueSpsc llena → `try_enqueue=false` → drop newest + contador.
- LogQueueSpsc llena → drop + contador.
- Publishing saturado/falla → drop + contador + warning/error rate-limited.

---

## 3. Métricas mínimas recomendadas (para health)
Por shard:
- snapshots_enqueued_total
- snapshots_dropped_total
- publish_ok_total
- publish_fail_total
- publish_backpressured_total

Global:
- snapshots_received_total
- log_dropped_total

---

## 4. Fuera de alcance (a propósito)
- Validaciones de negocio
- Normalización de mensajes
- Persistencia
- Lógica por cuenta
- Throttling de mercado
- Auditoría por evento
