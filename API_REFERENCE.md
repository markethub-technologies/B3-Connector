# B3-Connector API Reference

Complete API documentation for key interfaces and data structures in the B3-Connector project.

## Table of Contents

1. [Core Pipeline](#core-pipeline)
2. [Data Structures](#data-structures)
3. [Interfaces](#interfaces)
4. [Mapping & Registry](#mapping--registry)
5. [Publishing](#publishing)
6. [Telemetry](#telemetry)
7. [OnixS Adapters](#onixs-adapters)
8. [Testing Utilities](#testing-utilities)

---

## Core Pipeline

### MdPublishPipeline

**Location**: `b3-md-connector/src/core/MdPublishPipeline.hpp:1`

**Purpose**: Orchestrates N worker shards with deterministic instrument-based routing.

#### Constructor
```cpp
MdPublishPipeline(
    uint32_t workerCount,
    IPublishSink& sink,
    const InstrumentTopicMapper& topicMapper,
    const MdSnapshotMapper& snapshotMapper
)
```

**Parameters**:
- `workerCount`: Number of worker threads to spawn (typically 4)
- `sink`: Publish sink (usually `ZmqPublishConcentrator`)
- `topicMapper`: Resolves instrument ID → ZMQ topic
- `snapshotMapper`: Serializes `BookSnapshot` → protobuf bytes

#### Methods

##### `tryEnqueue`
```cpp
bool tryEnqueue(const OrdersSnapshot& snapshot) noexcept
```

**Description**: Routes snapshot to appropriate shard based on instrument ID.

**Parameters**:
- `snapshot`: MBO window snapshot from OnixS callback

**Returns**: `true` if enqueued, `false` if target worker's queue is full (drop)

**Thread Safety**: Thread-safe (can be called from OnixS callback thread)

**Sharding Algorithm**:
```cpp
uint32_t shard = (snapshot.instrumentId * 11400714819323198485ull) % workerCount
```

##### `start`
```cpp
void start()
```

**Description**: Starts all worker threads.

**Preconditions**: Must be called before `tryEnqueue`.

##### `stop`
```cpp
void stop(bool drain)
```

**Description**: Stops all worker threads.

**Parameters**:
- `drain`: If `true`, workers process remaining queued events before shutdown. If `false`, workers return immediately (drop remaining).

**Blocking**: Waits for all worker threads to terminate.

---

### MdPublishWorker

**Location**: `b3-md-connector/src/core/MdPublishWorker.hpp:1`

**Purpose**: Processes snapshots (aggregate MBO→MBP, serialize, publish) in dedicated thread.

#### Constructor
```cpp
MdPublishWorker(
    uint32_t shardId,
    IPublishSink& sink,
    const InstrumentTopicMapper& topicMapper,
    const MdSnapshotMapper& snapshotMapper,
    SpdlogLogPublisher<4096>& logPublisher
)
```

**Parameters**:
- `shardId`: Numeric identifier for this worker (0-based)
- `sink`: Where to publish `PublishEvent` (concentrator)
- `topicMapper`: Resolves topics
- `snapshotMapper`: Serializes snapshots
- `logPublisher`: Telemetry sink for health metrics

#### Methods

##### `tryEnqueue`
```cpp
bool tryEnqueue(const OrdersSnapshot& snapshot) noexcept
```

**Description**: Enqueues snapshot to this worker's SPSC queue.

**Returns**: `true` if enqueued, `false` if queue full (capacity: 4096)

**Thread Safety**: Single producer (OnixS thread via pipeline), single consumer (worker thread)

##### `start`
```cpp
void start()
```

**Description**: Spawns worker thread.

##### `stop`
```cpp
void stop(bool drain)
```

**Description**: Stops worker thread.

**Parameters**:
- `drain`: If `true`, processes all queued events before returning. If `false`, returns immediately.

#### Health Metrics

Workers emit `LogEvent` with `Code::HealthTick` every 5 seconds:

```cpp
struct WorkerHealthMetrics {
    uint64_t enqueued_total;    // Cumulative snapshots received
    uint64_t published_total;   // Cumulative snapshots published
    uint64_t dropped_total;     // Cumulative drops (queue full)
    uint32_t queue_size;        // Current queue depth
};
```

---

## Data Structures

### OrdersSnapshot

**Location**: `b3-md-connector/src/core/OrdersSnapshot.hpp:1`

**Purpose**: Market By Order (MBO) snapshot with bounded window (up to 256 orders per side).

#### Definition
```cpp
struct OrderEntry {
    int64_t priceMantissa;  // Fixed-point price (4 decimals implied)
    int64_t qty;            // Quantity
};

struct OrdersSnapshot {
    static constexpr size_t K = 256;  // Max orders per side

    // Identifiers
    uint64_t instrumentId;       // B3 instrument ID
    uint64_t exchangeTsNs;       // Exchange timestamp (nanoseconds)
    uint64_t rptSeq;             // OnixS RptSeq (per-instrument sequence)
    uint64_t channelSeq;         // OnixS ChannelSeq (global channel sequence)

    // Counts
    uint16_t bidCountRaw;        // Total bids reported by OnixS
    uint16_t askCountRaw;        // Total asks reported by OnixS
    uint16_t bidsCopied;         // Bids actually copied (non-null price)
    uint16_t asksCopied;         // Asks actually copied (non-null price)
    uint8_t bidTruncated;        // 1 if bidCountRaw > K
    uint8_t askTruncated;        // 1 if askCountRaw > K

    // Orders
    OrderEntry bids[K];          // Bid orders
    OrderEntry asks[K];          // Ask orders
};

static_assert(std::is_trivially_copyable_v<OrdersSnapshot>);
```

#### Properties
- **Size**: ~8KB (256 * 2 * 16 bytes + metadata)
- **Trivially copyable**: Safe for `memcpy`, no destructor overhead
- **Stack-allocated**: Created in OnixS callback, copied to SPSC queue

#### Usage Example
```cpp
void onOrderBookUpdated(uint64_t nowNs, const IOrderBookView& book) {
    OrdersSnapshot snapshot;
    OnixsOrdersSnapshotBuilder::buildFromBook(book, nowNs, snapshot);

    if (!pipeline.tryEnqueue(snapshot)) {
        // Queue full, drop
        dropped_++;
    }
}
```

---

### BookSnapshot

**Location**: `b3-md-connector/src/core/BookSnapshot.hpp:1`

**Purpose**: Market By Price (MBP) aggregated snapshot (Top N price levels).

#### Definition
```cpp
struct Level {
    int64_t price;  // Fixed-point price
    int64_t qty;    // Total quantity at this price level
};

template <int N>
struct BookSnapshotT {
    uint64_t instrumentId;
    uint64_t exchangeTsNs;
    uint8_t bidCount;     // Actual bid levels (≤ N)
    uint8_t askCount;     // Actual ask levels (≤ N)
    Level bids[N];        // Best bid at index 0
    Level asks[N];        // Best ask at index 0
};

using BookSnapshot = BookSnapshotT<5>;  // Top 5 levels

static_assert(std::is_trivially_copyable_v<BookSnapshot>);
```

#### Properties
- **Size**: ~200 bytes
- **Trivially copyable**: POD, stack-allocated
- **Created**: In worker thread (off hot path) from `OrdersSnapshot`

#### Aggregation
Orders at the same price level are summed:
```
MBO:
  Bid: 100.00 qty 10
  Bid: 100.00 qty 5
  Bid: 99.50 qty 20

MBP:
  Level 0: price=100.00 qty=15  (10 + 5)
  Level 1: price=99.50  qty=20
```

---

### PublishEvent

**Location**: `b3-md-connector/src/publishing/PublishEvent.hpp:1`

**Purpose**: Transport serialized message from worker to concentrator.

#### Definition
```cpp
struct PublishEvent {
    static constexpr size_t kMaxTopic = 128;
    static constexpr size_t kMaxBytes = 4096;

    uint32_t size;              // Payload size (bytes written)
    uint8_t topicLen;           // Topic length (bytes written)
    char topic[kMaxTopic];      // ZMQ topic (NOT null-terminated)
    uint8_t bytes[kMaxBytes];   // Serialized protobuf payload
};

static_assert(std::is_trivially_copyable_v<PublishEvent>);
```

#### Properties
- **Size**: 4224 bytes
- **Self-contained**: No pointers, safe for SPSC queue
- **Topic**: Human-readable symbol (e.g., "PETR4") or fallback ("IID:123456")

#### Usage Example
```cpp
// Worker serializes BookSnapshot
BookSnapshot book = /* ... */;
PublishEvent event;

event.size = snapshotMapper.mapAndSerialize(book, event.bytes, kMaxBytes);
topicMapper.tryWriteTopic(book.instrumentId, event.topic, event.topicLen);

sink.tryPublish(shardId, event);
```

---

### LogEvent

**Location**: `b3-md-connector/src/telemetry/LogEvent.hpp:1`

**Purpose**: Structured telemetry for off-hot-path logging.

#### Definition
```cpp
enum class LogLevel : uint8_t { Health, Info, Error };

enum class Component : uint8_t {
    Core, Pipeline, Worker, Mapping, Publishing, Adapter
};

enum class Code : uint8_t {
    Startup, Shutdown, HealthTick, Drops, QueueSaturated,
    LogDrops, PublishOk, PublishFail, MapMiss
};

struct LogEvent {
    uint64_t tsNs;          // Nanosecond timestamp
    LogLevel level;
    Component component;
    Code code;
    uint64_t instrumentId;  // Context (0 if N/A)
    uint16_t shard;         // Shard ID (0xFFFF if N/A)
    uint64_t arg0;          // Generic counter
    uint64_t arg1;          // Generic counter
};

static_assert(std::is_trivially_copyable_v<LogEvent>);
```

#### Properties
- **Size**: 56 bytes
- **POD**: Safe for SPSC queue
- **Generic args**: `arg0`/`arg1` can encode multiple counters

#### Usage Examples

##### Health Tick
```cpp
LogEvent{
    .tsNs = nowNs(),
    .level = LogLevel::Health,
    .component = Component::Worker,
    .code = Code::HealthTick,
    .shard = shardId_,
    .arg0 = queueSize,
    .arg1 = (deltaEnqueued << 32) | deltaPublished
};
```

##### Drop Event
```cpp
LogEvent{
    .tsNs = nowNs(),
    .level = LogLevel::Error,
    .component = Component::Worker,
    .code = Code::Drops,
    .instrumentId = snapshot.instrumentId,
    .shard = shardId_,
    .arg0 = deltaDrops
};
```

---

## Interfaces

### IOrderBookView

**Location**: `b3-md-connector/src/core/IOrderBookView.hpp:1`

**Purpose**: Abstraction over OnixS `OrderBook` for testability.

#### Definition
```cpp
struct Order {
    int64_t priceMantissa;
    int64_t qty;
    bool priceIsNull;
};

class IOrderBookView {
public:
    virtual ~IOrderBookView() = default;

    virtual uint64_t instrumentId() const = 0;
    virtual uint64_t lastRptSeq() const = 0;
    virtual uint64_t lastChannelSeq() const = 0;

    virtual size_t bidCount() const = 0;
    virtual size_t askCount() const = 0;

    virtual Order bidAt(size_t index) const = 0;
    virtual Order askAt(size_t index) const = 0;
};
```

#### Implementations
- **Production**: `OnixOrderBookView` wraps OnixS `OrderBook`
- **Testing**: `FakeOrderBook` with in-memory vectors

---

### IPublishSink

**Location**: `b3-md-connector/src/publishing/IPublishSink.hpp:1`

**Purpose**: Abstraction for publish targets (enables testing without ZMQ).

#### Definition
```cpp
class IPublishSink {
public:
    virtual ~IPublishSink() = default;

    virtual bool tryPublish(uint32_t shardId, const PublishEvent& event) noexcept = 0;
};
```

#### Method

##### `tryPublish`
```cpp
bool tryPublish(uint32_t shardId, const PublishEvent& event) noexcept
```

**Parameters**:
- `shardId`: Worker shard ID (for concentrator routing)
- `event`: Serialized message with topic

**Returns**: `true` if published/enqueued, `false` if dropped

**Implementations**:
- **Production**: `ZmqPublishConcentrator` (enqueues to per-shard SPSC)
- **Testing**: `FakePublishSink` (captures to in-memory vector)

---

## Mapping & Registry

### InstrumentRegistry

**Location**: `b3-md-connector/src/mapping/InstrumentRegistry.hpp:1`

**Purpose**: Thread-safe map from B3 instrument ID to human-readable symbol.

#### Definition
```cpp
class InstrumentRegistry {
public:
    InstrumentRegistry() = default;

    // Upsert (thread-safe)
    void upsert(uint64_t instrumentId, std::string symbol);

    // Bulk upsert (for SecurityList messages)
    void upsertBulk(const std::vector<std::pair<uint64_t, std::string>>& entries);

    // Lookup (thread-safe, read-heavy optimized)
    std::optional<std::string_view> tryGet(uint64_t instrumentId) const;

    // Stats
    size_t size() const;

private:
    mutable std::shared_mutex mutex_;  // Read-write lock
    std::unordered_map<uint64_t, std::string> map_;
};
```

#### Methods

##### `upsert`
```cpp
void upsert(uint64_t instrumentId, std::string symbol)
```

**Description**: Inserts or updates instrument mapping.

**Thread Safety**: Uses exclusive lock (write lock).

##### `tryGet`
```cpp
std::optional<std::string_view> tryGet(uint64_t instrumentId) const
```

**Description**: Looks up symbol for instrument ID.

**Returns**: `std::optional` with symbol view if found, `std::nullopt` otherwise.

**Thread Safety**: Uses shared lock (read lock). Multiple readers can proceed concurrently.

#### Usage Example
```cpp
InstrumentRegistry registry;

// Populate (typically from SecurityDefinition messages)
registry.upsert(123456, "PETR4");
registry.upsert(789012, "VALE3");

// Lookup (in worker thread)
auto symbol = registry.tryGet(123456);
if (symbol) {
    // Use *symbol (string_view)
} else {
    // Fallback to "IID:123456"
}
```

---

### InstrumentTopicMapper

**Location**: `b3-md-connector/src/mapping/InstrumentTopicMapper.hpp:1`

**Purpose**: Resolves ZMQ topic from instrument ID (via registry).

#### Definition
```cpp
class InstrumentTopicMapper {
public:
    explicit InstrumentTopicMapper(const InstrumentRegistry& registry)
        : registry_(registry) {}

    bool tryWriteTopic(uint64_t instrumentId,
                       char* topicBuf,
                       uint8_t& outLen) const noexcept;

private:
    const InstrumentRegistry& registry_;
};
```

#### Method

##### `tryWriteTopic`
```cpp
bool tryWriteTopic(uint64_t instrumentId, char* topicBuf, uint8_t& outLen) const noexcept
```

**Description**: Writes topic to buffer.

**Parameters**:
- `instrumentId`: B3 instrument ID
- `topicBuf`: Output buffer (must have capacity ≥ 128 bytes)
- `outLen`: [out] Number of bytes written

**Returns**: Always `true` (fallback guaranteed)

**Topic Format**:
- If found in registry: `"PETR4"` (human symbol)
- If not found: `"IID:123456"` (fallback with instrument ID)

**Thread Safety**: Thread-safe (registry uses shared lock for reads)

---

## Publishing

### ZmqPublishConcentrator

**Location**: `b3-md-connector/src/publishing/ZmqPublishConcentrator.hpp:1`

**Purpose**: Fan-in concentrator (N worker queues → 1 ZMQ socket).

#### Constructor
```cpp
ZmqPublishConcentrator(
    uint32_t numShards,
    const std::string& endpoint,
    SpdlogLogPublisher<4096>& logPublisher
)
```

**Parameters**:
- `numShards`: Number of workers (creates N SPSC queues)
- `endpoint`: ZMQ bind endpoint (e.g., `"tcp://*:8081"`)
- `logPublisher`: Telemetry sink

#### Methods

##### `tryPublish`
```cpp
bool tryPublish(uint32_t shardId, const PublishEvent& event) noexcept override
```

**Description**: Enqueues event to shard's SPSC queue.

**Parameters**:
- `shardId`: Worker shard ID (0-based, must be < `numShards`)
- `event`: Serialized message

**Returns**: `true` if enqueued, `false` if shard's queue is full (capacity: 4096)

**Thread Safety**: Multiple workers can call concurrently (each writes to own queue)

##### `start`
```cpp
void start()
```

**Description**: Spawns concentrator thread.

**Slow Joiner Mitigation**: Sleeps 1.5s before binding socket.

##### `stop`
```cpp
void stop()
```

**Description**: Stops concentrator thread, drains remaining events.

#### Processing Loop

The concentrator thread:
1. Round-robin across shard queues
2. Dequeues up to 8 events per shard per iteration
3. Sends ZMQ multipart message: `[topic frame][payload frame]`
4. Emits health metrics every 5s

```cpp
for (uint32_t shardId = 0; shardId < numShards_; ++shardId) {
    for (int i = 0; i < 8; ++i) {
        PublishEvent event;
        if (!queues_[shardId].try_dequeue(event)) break;

        socket_.sendMultipart(event.topic, event.topicLen, event.bytes, event.size);
        sent_++;
    }
}
```

---

## Telemetry

### SpdlogLogPublisher

**Location**: `b3-md-connector/src/telemetry/SpdlogLogPublisher.hpp:1`

**Purpose**: Off-hot-path log consumer (formats `LogEvent` → spdlog).

#### Definition
```cpp
template <size_t Capacity>
class SpdlogLogPublisher {
public:
    SpdlogLogPublisher() = default;

    // Producer API (thread-safe)
    bool try_publish(const LogEvent& event) noexcept;

    // Lifecycle
    void start();  // Spawns consumer thread
    void stop();   // Drains queue, stops thread

    // Stats
    uint64_t dropped() const noexcept;

private:
    LogQueueSpsc<LogEvent, Capacity> queue_;
    std::atomic<uint64_t> dropped_{0};
    std::thread thread_;
    std::atomic<bool> running_{false};
};
```

#### Methods

##### `try_publish`
```cpp
bool try_publish(const LogEvent& event) noexcept
```

**Description**: Enqueues log event to SPSC queue.

**Returns**: `true` if enqueued, `false` if queue full (increments `dropped_`)

**Thread Safety**: Single producer (worker or concentrator), single consumer (log thread)

##### `start` / `stop`
```cpp
void start()
void stop()
```

**Description**: Starts/stops consumer thread. `stop()` drains queue before returning.

#### Formatting

Consumer thread formats `LogEvent` based on `Code`:

```cpp
std::string format(const LogEvent& e) {
    switch (e.code) {
        case Code::HealthTick:
            return fmt::format("[Health] {} {} | Queue: {} | Enq: {} | Pub: {}",
                               componentName(e.component), e.shard,
                               e.arg0, e.arg1 >> 32, e.arg1 & 0xFFFFFFFF);
        case Code::Drops:
            return fmt::format("[Error] {} {} | Instrument {} | Drops: {}",
                               componentName(e.component), e.shard,
                               e.instrumentId, e.arg0);
        // ...
    }
}
```

---

## OnixS Adapters

### OnixsOrdersSnapshotBuilder

**Location**: `b3-md-connector/src/onixs/OnixsOrdersSnapshotBuilder.hpp:1`

**Purpose**: Builds `OrdersSnapshot` from OnixS `OrderBook`.

#### Static Method

##### `buildFromBook`
```cpp
static inline void buildFromBook(
    const IOrderBookView& book,
    uint64_t nowNs,
    OrdersSnapshot& out
) noexcept
```

**Description**: Copies up to 256 orders per side from book to snapshot.

**Parameters**:
- `book`: OnixS order book view (via `IOrderBookView` interface)
- `nowNs`: Current system timestamp (nanoseconds)
- `out`: [out] Output snapshot

**Behavior**:
- Skips orders with null price (market orders)
- Sets `bidTruncated` / `askTruncated` if more than 256 orders
- Copies `instrumentId`, `rptSeq`, `channelSeq` from book

**Assumptions**:
- Bids are in ascending order (best bid at end)
- Asks are in ascending order (best ask at start)
- **TODO**: Verify these assumptions with runtime assertions

---

### B3InstrumentRegistryListener

**Location**: `b3-md-connector/src/onixs/B3InstrumentRegistryListener.hpp:1`

**Purpose**: OnixS listener for `SecurityDefinition_12` messages (populates registry).

#### Definition
```cpp
class B3InstrumentRegistryListener : public MessageListener {
public:
    explicit B3InstrumentRegistryListener(InstrumentRegistry& registry)
        : registry_(registry) {}

    void onSecurityDefinition_12(
        const SecurityDefinition_12& msg,
        const SbeMessage& raw) override;

private:
    InstrumentRegistry& registry_;
};
```

#### Method

##### `onSecurityDefinition_12`
```cpp
void onSecurityDefinition_12(const SecurityDefinition_12& msg, const SbeMessage& raw) override
```

**Description**: Captures security definition messages, extracts instrument ID and symbol.

**Processing**:
```cpp
uint64_t instrumentId = msg.securityId();
std::string symbol = trimWhitespace(msg.symbol());
registry_.upsert(instrumentId, symbol);
```

**TODO**: Wire up in `main.cpp`:
```cpp
B3InstrumentRegistryListener listener(registry);
handler.registerListener(&listener);
```

---

## Testing Utilities

### FakePublishSink

**Location**: `tests/md/FakePublishSink.hpp:1`

**Purpose**: Test double for `IPublishSink` (captures publishes in-memory).

#### Definition
```cpp
struct CapturedPublish {
    uint32_t shardId;
    std::string topic;
    std::vector<uint8_t> bytes;
};

class FakePublishSink : public IPublishSink {
public:
    bool tryPublish(uint32_t shardId, const PublishEvent& event) noexcept override {
        std::lock_guard<std::mutex> g(mutex_);
        msgs_.push_back({
            .shardId = shardId,
            .topic = std::string(event.topic, event.topicLen),
            .bytes = std::vector<uint8_t>(event.bytes, event.bytes + event.size)
        });
        return true;
    }

    size_t count() const;
    CapturedPublish at(size_t index) const;
    std::vector<CapturedPublish> getPublishesForTopic(const std::string& topic) const;

private:
    mutable std::mutex mutex_;
    std::vector<CapturedPublish> msgs_;
};
```

#### Usage Example
```cpp
TEST(MdPipelineTests, PublishesFifo) {
    using namespace b3::md;

    testsupport::FakePublishSink sink;
    testsupport::FakeInstrumentTopicMapper fakeTopics{{1001, "PETR4"}};

    MdSnapshotMapper mapper;

    std::vector<std::unique_ptr<MdPublishWorker>> workers;
    workers.push_back(std::make_unique<MdPublishWorker>(
        0, mapper, sink, fakeTopics.get()
    ));

    MdPublishPipeline pipeline(std::move(workers));
    pipeline.start();

    // Send 1000 events
    for (uint64_t ts = 0; ts < 1000; ++ts) {
        OrdersSnapshot snap{};
        snap.instrumentId = 1001;
        snap.exchangeTsNs = ts;
        snap.bidsCopied = 1;
        snap.asksCopied = 1;
        snap.bids[0] = {.priceMantissa = 1000, .qty = 1};
        snap.asks[0] = {.priceMantissa = 2000, .qty = 1};

        while (!pipeline.tryEnqueue(snap)) {
            std::this_thread::yield();
        }
    }

    // Wait for processing
    std::this_thread::sleep_for(100ms);

    pipeline.stop(true);

    // Verify
    ASSERT_EQ(sink.count(), 1000);

    for (size_t i = 0; i < 1000; ++i) {
        auto msg = sink.at(i);
        EXPECT_EQ(msg.topic, "PETR4");
        // Parse and verify timestamp ordering
    }
}
```

---

### FakeInstrumentTopicMapper

**Location**: `b3-md-connector/src/testsupport/FakeInstrumentTopicMapper.hpp:1`

**Purpose**: Test helper that creates a real `InstrumentTopicMapper` with preloaded data.

#### Definition
```cpp
namespace b3::md::testsupport {

class FakeInstrumentTopicMapper final {
public:
    using InstrumentId = b3::md::mapping::InstrumentId;

    // Construct with list of {instrumentId, "SYMBOL"} pairs
    explicit FakeInstrumentTopicMapper(
        std::initializer_list<std::pair<InstrumentId, std::string>> items = {});

    // Access the real mapper that MdPublishWorker needs
    const b3::md::mapping::InstrumentTopicMapper& get() const noexcept;
    b3::md::mapping::InstrumentTopicMapper& get() noexcept;

    // Helper for fluent API
    FakeInstrumentTopicMapper& with(InstrumentId id, std::string symbol);

private:
    b3::md::mapping::InstrumentRegistry registry_;
    b3::md::mapping::InstrumentTopicMapper mapper_;
};

} // namespace b3::md::testsupport
```

#### Methods

##### Constructor
```cpp
FakeInstrumentTopicMapper(
    std::initializer_list<std::pair<InstrumentId, std::string>> items = {})
```

**Description**: Creates a fake mapper with preloaded instrument-to-symbol mappings.

**Parameters**:
- `items`: List of `{instrumentId, "SYMBOL"}` pairs to preload

**Example**:
```cpp
testsupport::FakeInstrumentTopicMapper fakeTopics{
    {1001, "PETR4"},
    {1002, "VALE3"},
    {1003, "ITUB4"}
};
```

##### `get()`
```cpp
const InstrumentTopicMapper& get() const noexcept
InstrumentTopicMapper& get() noexcept
```

**Description**: Returns reference to the real `InstrumentTopicMapper`.

**Returns**: Reference to internal mapper (backed by preloaded registry)

**Usage**: Pass to `MdPublishWorker` constructor

##### `with()`
```cpp
FakeInstrumentTopicMapper& with(InstrumentId id, std::string symbol)
```

**Description**: Adds an instrument mapping (fluent API).

**Parameters**:
- `id`: Instrument ID
- `symbol`: Symbol string

**Returns**: Reference to `*this` for chaining

---

### FakeOrderBook

**Location**: `tests/md/FakeOrderBook.hpp:1`

**Purpose**: Test double for `IOrderBookView` (replaces OnixS dependency).

#### Definition
```cpp
class FakeOrderBook : public IOrderBookView {
public:
    FakeOrderBook(uint64_t instrumentId) : instrumentId_(instrumentId) {}

    void addBid(int64_t price, int64_t qty) {
        bids_.push_back({price, qty, false});
    }

    void addAsk(int64_t price, int64_t qty) {
        asks_.push_back({price, qty, false});
    }

    // IOrderBookView implementation
    uint64_t instrumentId() const override { return instrumentId_; }
    size_t bidCount() const override { return bids_.size(); }
    size_t askCount() const override { return asks_.size(); }
    Order bidAt(size_t i) const override { return bids_[i]; }
    Order askAt(size_t i) const override { return asks_[i]; }

private:
    uint64_t instrumentId_;
    std::vector<Order> bids_;
    std::vector<Order> asks_;
};
```

#### Usage Example
```cpp
TEST(SnapshotBuilderTests, FilterMarketOrders) {
    FakeOrderBook book(1001);
    book.addBid(100'0000, 10);  // Limit order
    book.addBid(0, 5);          // Market order (null price)
    book.addBid(99'5000, 20);   // Limit order

    OrdersSnapshot snapshot;
    OnixsOrdersSnapshotBuilder::buildFromBook(book, nowNs(), snapshot);

    EXPECT_EQ(snapshot.bidsCopied, 2);  // Market order filtered
    EXPECT_EQ(snapshot.bids[0].priceMantissa, 100'0000);
    EXPECT_EQ(snapshot.bids[1].priceMantissa, 99'5000);
}
```

---

## Summary

This API reference covers the key interfaces and data structures in the B3-Connector Market Data pipeline:

- **Core Pipeline**: `MdPublishPipeline`, `MdPublishWorker` (sharding + processing)
- **Data Structures**: `OrdersSnapshot` (MBO), `BookSnapshot` (MBP), `PublishEvent`, `LogEvent` (all PODs)
- **Interfaces**: `IOrderBookView`, `IPublishSink` (abstraction for testability)
- **Mapping**: `InstrumentRegistry`, `InstrumentTopicMapper` (symbol resolution)
- **Publishing**: `ZmqPublishConcentrator` (fan-in pattern)
- **Telemetry**: `SpdlogLogPublisher` (off-hot-path logging)
- **OnixS Adapters**: `OnixsOrdersSnapshotBuilder`, `B3InstrumentRegistryListener`
- **Testing**: `FakePublishSink`, `FakeOrderBook`, `FakeInstrumentTopicMapper`

For complete implementation details, see the corresponding header files in `b3-md-connector/src/`.

---

**Document Version**: 1.0
**Last Updated**: 2025-12-30
**Status**: Current as of commit bcec7bc
