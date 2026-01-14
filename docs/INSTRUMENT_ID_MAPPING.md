# InstrumentId y SecurityID: Mapeo y Garantías

Este documento explica la relación entre `instrumentId` (usado en `OrderBook`) y `securityId` (usado en mensajes del protocolo UMDF), y cómo se realiza el mapeo a símbolos.

## Pregunta Original

Cuando OnixS llama `onOrderBookUpdated(const OrderBook& book)`, ¿cómo obtenemos el símbolo del instrumento? ¿El `book.instrumentId()` es el mismo que el `securityId` de los mensajes `SecurityDefinition_12`? ¿Es un identificador global de B3 o solo un puntero local a ese libro?

## Respuesta Corta

- **`instrumentId` == `securityId`**: Son el mismo valor (ambos `UInt64`)
- **Es global**: Es el SecurityID definido en el protocolo UMDF de B3, no un puntero local
- **El mapeo existe**: El `InstrumentRegistry` mapea `instrumentId` ↔ `symbol` usando datos de `SecurityDefinition_12`

## 1. De Dónde Sale el Símbolo

El símbolo proviene del **mensaje `SecurityDefinition_12` del protocolo UMDF de B3**.

### Flujo de Población del Registry

```
B3 Exchange (UMDF Feed)
    ↓
SequenceReset_1 (inicio de security list)
    ↓
SecurityDefinition_12 (uno por instrumento)
    ├─ securityId(): 10018438 (uint64)
    └─ symbol(): "PETR4"
    ↓
SecurityDefinition_12 (otro instrumento)
    ├─ securityId(): 10018439
    └─ symbol(): "VALE3"
    ↓
SequenceReset_1 (fin de security list)
    ↓
InstrumentRegistry populated with:
    10018438 → "PETR4"
    10018439 → "VALE3"
```

### Código: Listener que Captura los Instrumentos

**Archivo:** `b3-md-connector/src/onixs/B3InstrumentRegistryListener.hpp:40-62`

```cpp
void onSecurityDefinition_12(const SecurityDefinition_12 msg, ...) {
    const uint64_t iid = static_cast<uint64_t>(msg.securityId());
    std::string sym = trimRight(msg.symbol());

    if (iid == 0 || sym.empty())
        return;

    // Captura entre primer y segundo SequenceReset_1
    if (!capturing_.load(std::memory_order_acquire))
        return;

    staging_[iid] = extractInstrumentData(msg); // guarda iid → InstrumentData
}
```

## 2. Evidencia: instrumentId == securityId

### Evidencia 1: Documentación Explícita del Protocolo

En **todos** los mensajes que manejan órdenes, OnixS documenta:

**Archivo:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/messaging/Messages.h`

#### Mensaje `Order_MBO_50` (líneas 6304-6313)
```cpp
/// Security ID as defined by B3. For the SecurityID list, see
/// the Security Definition message in Market Data feed.
ONIXS_B3_UMDF_MD_NODISCARD
SecurityID securityId() const
{
    ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;
    return ordinary<SecurityID>(offset);
}
```

#### Mensaje `SnapshotFullRefresh_Header_30` (líneas 6036-6045)
```cpp
/// Security ID as defined by B3. For the SecurityID list, see
/// the Security Definition message in Market Data feed.
ONIXS_B3_UMDF_MD_NODISCARD
SecurityID securityId() const
{
    ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;
    return ordinary<SecurityID>(offset);
}
```

**Interpretación:** El comentario dice explícitamente: *"For the SecurityID list, see the Security Definition message"*

Esto significa:
- `SecurityDefinition_12::securityId()` → define el instrumento
- `Order_MBO_50::securityId()` → actualiza el OrderBook usando el **mismo SecurityID**
- `SnapshotFullRefresh_Header_30::securityId()` → snapshot del OrderBook usando el **mismo SecurityID**

### Evidencia 2: OrderBook Usa Internamente ese SecurityID

**Archivo:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/OrderBookListener.h:39-43`

```cpp
/// Is called when the book is changed within it's depth,
/// when Order_MBO_50, DeleteOrder_MBO_51 or MassDeleteOrders_MBO_52 are received.
virtual void onOrderBookChanged(const OrderBook& book, const Messaging::SbeMessage message) = 0;

/// Is called when the book is updated, when a message with MatchEventIndicator::EndOfEvent
/// is received and the book was changed within it's depth.
virtual void onOrderBookUpdated(const OrderBook& book) = 0;
```

Los mensajes que actualizan el OrderBook (`Order_MBO_50`, `DeleteOrder_MBO_51`, etc.) **todos tienen `securityId()`**.

OnixS construye el `OrderBook` internamente indexando/agrupando por ese `SecurityID`.

**Archivo:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/OrderBook.h:306-309`

```cpp
/// Instrument Id
inline InstrumentId instrumentId() const ONIXS_B3_UMDF_MD_NOTHROW
{
    return id_;
}
```

Y el typedef (línea 126):
```cpp
/// Alias for Instrument Id type.
typedef UInt64 InstrumentId;
```

### Evidencia 3: Handler.subscribe() Usa el Mismo ID

**Archivo:** `external/B3/UMDF/samples/Benchmark/Benchmark.cpp:72-74, 192-193`

```cpp
std::set<Messaging::SecurityID> instruments() const {
    return argSetOrDefault<Messaging::SecurityID>(options(), "instruments", 10018438);
}

// ... en main():
for(auto instrumentId: instruments)  // SecurityID se convierte en instrumentId
    handler.subscribe(instrumentId);
```

**Observación crítica:** El nombre de la variable cambia de `SecurityID` a `instrumentId`, pero es el **mismo valor**.

OnixS usa ambos términos (`SecurityID` e `InstrumentId`) indistintamente porque representan el mismo concepto.

**Archivo:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/Handler.h:126-135`

```cpp
/// Adds security id to the security filter
Handler& subscribe(Messaging::SecurityID securityId);

/// Adds a few security ids to the security filter
Handler& subscribe(std::initializer_list<Messaging::SecurityID> securityIds);

/// Removes security id from the security filter
Handler& unsubscribe(Messaging::SecurityID securityId);

/// Removes a few security ids from the security filter
Handler& unsubscribe(std::initializer_list<Messaging::SecurityID> securityIds);
```

El `Handler` recibe un `Messaging::SecurityID` en `subscribe()`, y ese mismo ID es el que luego aparece como `OrderBook::instrumentId()`.

### Evidencia 4: Es Parte del Protocolo SBE de B3

**Archivo:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/messaging/Fields.h:168`

```cpp
typedef UInt64 SecurityID;
```

**Archivo:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/OrderBook.h:126`

```cpp
typedef UInt64 InstrumentId;
```

Ambos son `UInt64`. El comentario en múltiples lugares dice: **"Security ID as defined by B3"**.

No es generado por OnixS, **viene del protocolo binario UMDF de B3** (Simple Binary Encoding - SBE).

## 3. ¿Es Global o Solo un Puntero Local?

### Respuesta: Es GLOBAL (Persistente del Protocolo B3)

El `SecurityID` / `InstrumentId` **NO es un puntero de memoria local**.

**Características:**
- Es el campo `SecurityID` del protocolo UMDF de B3 (especificación SBE)
- Viene en **todos** los mensajes del feed: `SecurityDefinition_12`, `Order_MBO_50`, `Trade_53`, etc.
- Es **estable dentro de una sesión de trading** (día)
- **Puede cambiar entre días** (B3 puede reasignar IDs, aunque es raro en práctica)

**Archivo:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/messaging/Messages.h:1720-1724`

```cpp
/// Security ID as defined by B3.
ONIXS_B3_UMDF_MD_NODISCARD
SecurityID securityId() const
    ONIXS_B3_UMDF_MD_NOTHROW
{
    // ... implementación
}
```

El comentario dice explícitamente: **"Security ID as defined by B3"** - es parte del protocolo, no generado por OnixS.

## 4. Cómo se Resuelve el Símbolo en el Pipeline

### Flujo Completo

```
OnixS Handler (recibe UMDF feed)
    ↓
SecurityDefinition_12 (al inicio del día)
    securityId: 10018438
    symbol: "PETR4"
    ↓
B3InstrumentRegistryListener::onSecurityDefinition_12()
    ↓
InstrumentRegistry::upsertFull()
    byId_[10018438] = InstrumentData{symbol: "PETR4", ...}
    bySymbol_["PETR4"] = 10018438
    ↓
ready_ = true (después del segundo SequenceReset_1)

─────────────────────────────────────────────────────────

OnixS Handler (feed de órdenes en tiempo real)
    ↓
Order_MBO_50, DeleteOrder_MBO_51, etc.
    securityId: 10018438
    price: 109000000 (mantissa)
    qty: 1000
    ↓
OnixS construye OrderBook internamente (id_ = 10018438)
    ↓
OnixsOrderBookListener::onOrderBookUpdated(book)
    book.instrumentId() → 10018438
    ↓
MarketDataEngine::onOrderBookUpdated()
    ↓
OnixsOrdersSnapshotBuilder::buildFromBook()
    out.instrumentId = book.instrumentId() → 10018438
    ↓
MdPublishPipeline::tryEnqueue(snapshot)
    hash(10018438) % 4 → shard 2
    ↓
MdPublishWorker (shard 2)
    ↓
InstrumentTopicMapper::getTopic(10018438)
    registry_.tryResolveSymbol(10018438) → "PETR4"
    return {"PETR4", 5}
    ↓
MdSnapshotMapper::mapToSerializedEnvelope()
    topic = "PETR4"
    payload = WrapperMessage (protobuf MarketDataUpdate)
    ↓
ZmqPublishConcentrator::publish()
    ↓
MarketHub.Messaging::Publisher
    tcp://*:8081
    [topic: "PETR4"][payload: protobuf bytes]
```

### Código: Resolución del Topic

**Archivo:** `b3-md-connector/src/mapping/InstrumentTopicMapper.hpp:38-49`

```cpp
std::pair<const char*, std::uint8_t> getTopic(b3::common::InstrumentId iid) const noexcept {
    const std::string *sym = registry_.tryResolveSymbol(iid);
    if (sym) {
        const std::size_t n = sym->size();
        if (n > 0 && n <= SerializedEnvelope::kMaxTopic) {
            return {sym->data(), static_cast<std::uint8_t>(n)};
        }
    }

    // No fallback - if symbol not in registry, drop the message
    return {nullptr, 0};
}
```

**Archivo:** `b3-md-connector/src/core/MdPublishWorker.hpp:202-206`

```cpp
auto [topicPtr, topicLen] = topicMapper_.getTopic(s.instrumentId);
if (!topicPtr || topicLen == 0) {
    dropped_.fetch_add(1, std::memory_order_relaxed);
    return;  // Drop message if symbol cannot be resolved
}
```

## 5. Validación en Runtime

### ¿Cómo Verificar que el Mapeo es Correcto?

Durante la operación normal, puedes verificar:

1. **Al inicio (después de `ready_ = true`):**
   ```cpp
   registry_.size() // Debe ser > 0 (ej: 500-1000 instrumentos)
   ```

2. **En el hot path (MarketDataEngine):**
   ```cpp
   if (registryReady_ && !registryReady_->load(std::memory_order_acquire)) {
       gatedDrops_++;  // Si esto incrementa, registry no está listo
       return;
   }
   ```

3. **En los workers (MdPublishWorker):**
   ```cpp
   if (!topicPtr || topicLen == 0) {
       dropped_++;  // Si esto incrementa, hay instrumentId sin símbolo
       return;
   }
   ```

### Logs Esperados

**Durante startup:**
```
[Registry] Capturing SecurityDefinition messages (between SequenceReset pair)
[Registry] Received SecurityDefinition: id=10018438 symbol=PETR4
[Registry] Received SecurityDefinition: id=10018439 symbol=VALE3
...
[Registry] Second SequenceReset received, registry ready with 847 instruments
[Engine] Registry ready, accepting OrderBook updates
```

**Durante operación:**
```
[Worker-0] Health tick: enqueued=1234 published=1234 dropped=0
[Worker-1] Health tick: enqueued=2345 published=2345 dropped=0
```

Si `dropped > 0` en workers, significa que hay `instrumentId` que no están en el registry (puede pasar si B3 envía órdenes de instrumentos que no estaban en la security list inicial - es raro pero posible).

## 6. Garantías y Limitaciones

### Garantías

✅ **Dentro de una sesión de trading:**
- `instrumentId` en `OrderBook` == `securityId` en `SecurityDefinition_12`
- El mapeo `instrumentId → symbol` es 1:1 y estable
- Todos los mensajes de órdenes (`Order_MBO_50`, etc.) usan el mismo `securityId`

✅ **Protocolo UMDF de B3:**
- `SecurityID` es un campo obligatorio del protocolo SBE
- Todos los mensajes relacionados con un instrumento usan el mismo `SecurityID`

### Limitaciones

⚠️ **Entre días:**
- B3 puede reasignar `SecurityID` values (poco común, pero posible)
- El registry **debe recargarse al inicio de cada sesión** (ya implementado con `SequenceReset_1`)

⚠️ **Instrumentos nuevos durante el día:**
- B3 puede publicar nuevos instrumentos después del inicio (corporate actions, nuevas opciones)
- El código actual tiene `strict freeze` (ignora `SecurityDefinition` después de `ready=true`)
- Si necesitas soporte para instrumentos nuevos intraday, hay que modificar `B3InstrumentRegistryListener`

## 7. Resumen Ejecutivo

| Pregunta | Respuesta |
|----------|-----------|
| ¿`instrumentId` == `securityId`? | **SÍ**, son el mismo valor (`UInt64`) |
| ¿De dónde sale el símbolo? | Del mensaje `SecurityDefinition_12` al inicio del día |
| ¿Es global o local? | **Global**, definido por el protocolo UMDF de B3 |
| ¿El mapeo es confiable? | **SÍ**, garantizado por el protocolo y OnixS SDK |
| ¿Necesito cambiar algo? | **NO**, el diseño actual es correcto |

## Referencias

### Archivos Clave del Proyecto

- **Listener de Registry:** `b3-md-connector/src/onixs/B3InstrumentRegistryListener.hpp`
- **Registry:** `b3-common/include/b3/common/InstrumentRegistry.hpp`
- **Topic Mapper:** `b3-md-connector/src/mapping/InstrumentTopicMapper.hpp`
- **Engine:** `b3-md-connector/src/core/MarketDataEngine.hpp`
- **Worker:** `b3-md-connector/src/core/MdPublishWorker.hpp`

### Headers de OnixS SDK

- **OrderBook:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/OrderBook.h`
- **Messages:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/messaging/Messages.h`
- **Handler:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/Handler.h`
- **Fields:** `external/B3/UMDF/include/OnixS/B3/MarketData/UMDF/messaging/Fields.h`

### Samples de OnixS

- **Benchmark:** `external/B3/UMDF/samples/Benchmark/Benchmark.cpp` (líneas 72-74, 192-193)
- **Getting Started:** `external/B3/UMDF/samples/GettingStarted/`

---

**Última actualización:** 2026-01-14
**Autor:** Claude Code (con revisión del equipo)
