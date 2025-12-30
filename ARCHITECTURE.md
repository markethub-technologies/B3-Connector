# B3-Connector Architecture

Comprehensive architectural documentation for the B3-Connector trading infrastructure.

## Table of Contents

1. [System Overview](#system-overview)
2. [Market Data Pipeline](#market-data-pipeline)
3. [Sharding Strategy](#sharding-strategy)
4. [Data Structures](#data-structures)
5. [Concurrency Model](#concurrency-model)
6. [Performance Characteristics](#performance-characteristics)
7. [Telemetry & Observability](#telemetry--observability)
8. [Testing Strategy](#testing-strategy)
9. [Design Decisions](#design-decisions)
10. [Future Enhancements](#future-enhancements)

---

## System Overview

### Purpose

B3-Connector provides low-latency, high-throughput connectivity to the Brazilian B3 exchange. The system is split into two independent connectors:

- **Market Data Connector (MD)**: Consumes B3 UMDF feed, aggregates orderbook snapshots, publishes via ZeroMQ
- **Order Entry Connector (OE)**: Routes orders to B3 BOE protocol, manages order lifecycle

This document focuses primarily on the **Market Data Connector** architecture, which has undergone significant redesign for production-grade performance.

### Design Philosophy

The MD connector is built around these core principles:

1. **Predictable low latency**: p99 latency stability over raw throughput
2. **Never block the feed**: Backpressure handled via drops, not blocking
3. **Zero-allocation hot path**: All critical data structures are stack-only PODs
4. **Lock-free where possible**: SPSC queues eliminate mutex contention
5. **Testability**: Clean interfaces enable unit testing without external dependencies

---

## Market Data Pipeline

### Architecture Evolution

**Previous Architecture (Direct Publish)**:
```
OnixS Handler → MarketDataEngine → Workers (N) → ZMQ PUB (N sockets)
```

**Current Architecture (Sharded Pipeline with Concentrator)**:
```
OnixS Handler → MarketDataEngine → MdPublishPipeline → Workers (N) → ZmqPublishConcentrator → ZMQ PUB (1 socket)
```

### Benefits of New Architecture

| Aspect | Before | After |
|--------|--------|-------|
| **ZMQ Endpoints** | N endpoints (one per worker) | 1 endpoint (concentrator) |
| **Subscriber Config** | Must know all N endpoints | Single endpoint |
| **Topic Mapping** | Embedded in workers | Centralized `InstrumentTopicMapper` |
| **Testing** | Requires ZMQ mocks | `IPublishSink` interface |
| **Slow Joiner Mitigation** | Per-worker (N warmup delays) | Single concentrator warmup |

### Component Breakdown

#### 1. OnixS UMDF Handler

**Responsibility**: Receive UDP multicast market data from B3

**Configuration**:
- Connectivity XML specifies feed A/B endpoints
- Network interfaces (`onixs.if_a`, `onixs.if_b`) for redundancy
- Channel ID (`onixs.channel`) specifies market segment (e.g., 80 = equities)

**Threading**: Internal OnixS thread pool processes UDP packets and builds orderbooks

**Listener Registration**:
```cpp
Handler handler(settings);
OnixsOrderBookListener listener(engine);
handler.registerOrderBookListener(&listener);
handler.start();
```

#### 2. MarketDataEngine

**Location**: b3-md-connector/src/core/MarketDataEngine.hpp:1

**Responsibility**: Adapter between OnixS and internal pipeline

**Hot Path Method**:
```cpp
void onOrderBookUpdated(uint64_t nowNs, const IOrderBookView& book) noexcept {
    OrdersSnapshot snapshot;
    OnixsOrdersSnapshotBuilder::buildFromBook(book, nowNs, snapshot);

    if (!pipeline_.tryEnqueue(snapshot)) {
        // Drop + increment counter (never blocks)
    }
}
```

**Key Properties**:
- Called from OnixS thread (not under our control)
- Must return quickly (<1μs target)
- No exceptions thrown for expected failures (queue full)

#### 3. MdPublishPipeline

**Location**: b3-md-connector/src/core/MdPublishPipeline.hpp:1

**Responsibility**: Route snapshots to appropriate shard

**Sharding Logic**:
```cpp
uint32_t shardFor(uint64_t instrumentId) const noexcept {
    const uint64_t kKnuth = 11400714819323198485ull;  // Knuth's multiplicative hash
    const uint64_t mixed = instrumentId * kKnuth;
    return static_cast<uint32_t>(mixed % workers_.size());
}
```

**Why Knuth Multiplicative Hash?**
- Instrument IDs may have patterns (e.g., sequential allocation)
- Multiplicative hash improves distribution across shards
- Prevents clustering of related instruments on same shard

**API**:
```cpp
bool tryEnqueue(const OrdersSnapshot& snapshot) noexcept {
    uint32_t shard = shardFor(snapshot.instrumentId);
    return workers_[shard]->tryEnqueue(snapshot);
}
```

#### 4. MdPublishWorker

**Location**: b3-md-connector/src/core/MdPublishWorker.hpp:1

**Responsibility**: Process snapshots (aggregate, serialize, publish)

**Threading**: Each worker runs in dedicated thread

**Processing Loop**:
```cpp
void run() {
    while (running_) {
        OrdersSnapshot snapshot;
        if (!queue_.try_dequeue(snapshot)) {
            // Queue empty, wait briefly
            continue;
        }

        // 1. Aggregate MBO → MBP (Top 5 levels)
        BookSnapshot book;
        MboToMbpAggregator::aggregateMboWindowToMbpTopN(snapshot, book);

        // 2. Serialize to protobuf (currently stub)
        PublishEvent event;
        mapper_.mapAndSerialize(book, event.bytes, event.size);

        // 3. Resolve topic
        topicMapper_.tryWriteTopic(book.instrumentId, event.topic, event.topicLen);

        // 4. Publish to concentrator
        sink_.tryPublish(shardId_, event);

        // 5. Update counters
        counters_.published++;
    }
}
```

**Drain Mode**:
- `stop(true)`: Graceful shutdown, processes all queued events
- `stop(false)`: Fast shutdown, returns immediately (drops remaining)

**Health Reporting**:
- Emits `LogEvent` every 5s with counters (enqueued, published, dropped)
- Reports queue depth for capacity monitoring

#### 5. ZmqPublishConcentrator

**Location**: b3-md-connector/src/publishing/ZmqPublishConcentrator.hpp:1

**Responsibility**: Fan-in from N worker queues to single ZMQ socket

**Architecture**:
```
Worker 0 → SPSC Queue 0 ─┐
Worker 1 → SPSC Queue 1 ─┤
Worker 2 → SPSC Queue 2 ─├─→ Round-Robin Dequeue → ZMQ PUB Socket
Worker 3 → SPSC Queue 3 ─┘
```

**Round-Robin Batching**:
```cpp
// Process up to 8 events per shard per iteration
for (uint32_t shardId = 0; shardId < numShards_; ++shardId) {
    for (int i = 0; i < 8; ++i) {
        PublishEvent event;
        if (!queues_[shardId].try_dequeue(event)) break;

        socket_.sendMultipart(event.topic, event.topicLen, event.bytes, event.size);
        sent_++;
    }
}
```

**Why Batching?**
- Amortizes syscall overhead (zmq send)
- Prevents starvation (all shards serviced each iteration)
- Tunable batch size (8 is empirically chosen)

**Slow Joiner Mitigation**:
- Sleeps 1.5s on startup before binding socket
- Allows subscribers to connect before first message
- Prevents missed initial snapshots

#### 6. InstrumentRegistry & Topic Mapping

**Location**:
- b3-md-connector/src/mapping/InstrumentRegistry.hpp:1
- b3-md-connector/src/mapping/InstrumentTopicMapper.hpp:1

**Responsibility**: Map B3 instrument IDs to human-readable symbols

**Registry API**:
```cpp
class InstrumentRegistry {
public:
    void upsert(uint64_t instrumentId, std::string symbol);  // Thread-safe
    std::optional<std::string_view> tryGet(uint64_t instrumentId) const;

private:
    mutable std::shared_mutex mutex_;  // Read-heavy workload
    std::unordered_map<uint64_t, std::string> map_;
};
```

**Topic Mapping**:
```cpp
bool InstrumentTopicMapper::tryWriteTopic(uint64_t instrumentId,
                                          char* topicBuf,
                                          uint8_t& outLen) const noexcept {
    auto symbol = registry_.tryGet(instrumentId);
    if (symbol) {
        // Human-readable: "PETR4"
        std::memcpy(topicBuf, symbol->data(), symbol->size());
        outLen = static_cast<uint8_t>(symbol->size());
    } else {
        // Fallback: "IID:123456"
        outLen = std::snprintf(topicBuf, 128, "IID:%lu", instrumentId);
    }
    return true;
}
```

**Population Strategy** (TODO):
- `B3InstrumentRegistryListener` captures `SecurityDefinition_12` messages from OnixS
- Extracts `securityId()` and `symbol()` fields
- Calls `registry.upsert(securityId, trimmed(symbol))`
- Runs during feed warmup (before market open)

---

## Sharding Strategy

### Goals

1. **Parallelism**: Distribute work across CPU cores
2. **Ordering**: Maintain per-instrument FIFO (critical for book consistency)
3. **Load Balancing**: Avoid hotspots (single shard overloaded)
4. **Simplicity**: No dynamic rebalancing, deterministic routing

### Implementation

**Hash Function**:
```cpp
static constexpr uint64_t kKnuth = 11400714819323198485ull;
uint32_t shard = (instrumentId * kKnuth) % numWorkers;
```

**Properties**:
- **Deterministic**: Same input always produces same output
- **Uniform**: Good distribution across shards (assuming uniform instrument ID distribution)
- **Fast**: Single multiply + modulo (modern CPUs optimize)

### FIFO Guarantee

**Per-Instrument Ordering**:
```
Instrument A: Event 1 → Event 2 → Event 3  (all route to Shard 0)
Instrument B: Event 1 → Event 2 → Event 3  (all route to Shard 2)
```

**Cross-Instrument Non-Determinism**:
```
Shard 0: A1 → A2 → A3
Shard 2: B1 → B2 → B3

Concentrator may publish: A1 → B1 → A2 → B2 → A3 → B3
(order between A and B is non-deterministic)
```

**Why This is OK**:
- Subscribers typically filter by instrument (ZMQ topic prefix)
- Subscribers for "PETR4" see all PETR4 events in order
- Subscribers for "VALE3" see all VALE3 events in order
- Cross-instrument ordering is not required for market data

### Shard Count Selection

**Trade-offs**:
- **Too few shards**: Underutilizes CPU cores, potential bottleneck
- **Too many shards**: Overhead (threads, context switching), diminishing returns

**Recommended**:
- Start with `numWorkers = numCores / 2` (leave headroom for OS, OnixS threads)
- Typical: 4 workers on 8-core machine
- Monitor: Queue depths, throughput, CPU utilization
- Tune: Adjust `md.shards` in config if hotspots observed

---

## Data Structures

All hot-path data structures are **trivially copyable** (no heap allocation, no vtable, no pointers).

### OrdersSnapshot

**Purpose**: Transport MBO (Market By Order) window from OnixS callback to worker

**Definition**:
```cpp
struct OrderEntry {
    int64_t priceMantissa;  // Fixed-point (4 decimals implied)
    int64_t qty;
};

struct OrdersSnapshot {
    static constexpr size_t K = 256;  // Max orders per side

    uint64_t instrumentId;
    uint64_t exchangeTsNs;          // Exchange timestamp (TODO: extract from OnixS)
    uint64_t rptSeq;                // OnixS RptSeq (sequence per instrument)
    uint64_t channelSeq;            // OnixS ChannelSeq (global channel sequence)

    uint16_t bidCountRaw;           // Total bids reported by OnixS
    uint16_t askCountRaw;           // Total asks reported by OnixS
    uint16_t bidsCopied;            // Bids copied (excluding market orders)
    uint16_t asksCopied;            // Asks copied (excluding market orders)
    uint8_t bidTruncated;           // 1 if bidCountRaw > K
    uint8_t askTruncated;           // 1 if askCountRaw > K

    OrderEntry bids[K];             // Bid orders (best bid varies by OnixS ordering)
    OrderEntry asks[K];             // Ask orders (best ask varies by OnixS ordering)
};

static_assert(std::is_trivially_copyable_v<OrdersSnapshot>);
```

**Size**: ~8KB (256 * 2 sides * 16 bytes/entry + metadata)

**Lifetime**: Created on stack in OnixS callback, copied into SPSC queue

**Market Order Filtering**:
- OnixS returns orders with nullable prices
- Market orders (`price.isNull() == true`) are skipped during copy
- Rationale: Market orders don't contribute to price levels in MBP view

### BookSnapshot

**Purpose**: Aggregated MBP (Market By Price) view for publishing

**Definition**:
```cpp
struct Level {
    int64_t price;
    int64_t qty;
};

template <int N>
struct BookSnapshotT {
    uint64_t instrumentId;
    uint64_t exchangeTsNs;
    uint8_t bidCount;  // Actual levels (≤ N)
    uint8_t askCount;  // Actual levels (≤ N)
    Level bids[N];     // Best bid at index 0
    Level asks[N];     // Best ask at index 0
};

using BookSnapshot = BookSnapshotT<5>;  // Top 5 levels

static_assert(std::is_trivially_copyable_v<BookSnapshot>);
```

**Size**: ~200 bytes

**Creation**: Worker aggregates `OrdersSnapshot` → `BookSnapshot` via `MboToMbpAggregator`

**Aggregation Logic**:
```cpp
// Pseudocode
for each order in bids:
    level = find_or_create(levels, order.price)
    level.qty += order.qty

sort(levels, descending)  // Best bid = highest price
take_top_N(levels, N=5)
```

### PublishEvent

**Purpose**: Transport serialized message from worker to concentrator

**Definition**:
```cpp
struct PublishEvent {
    static constexpr size_t kMaxTopic = 128;
    static constexpr size_t kMaxBytes = 4096;

    uint32_t size;              // Payload size (bytes written to `bytes`)
    uint8_t topicLen;           // Topic length (bytes written to `topic`)
    char topic[kMaxTopic];      // ZMQ topic (NOT null-terminated)
    uint8_t bytes[kMaxBytes];   // Serialized payload (protobuf)
};

static_assert(std::is_trivially_copyable_v<PublishEvent>);
```

**Size**: 4224 bytes

**Usage**:
- Worker serializes `BookSnapshot` into `PublishEvent::bytes`
- Worker writes topic into `PublishEvent::topic`
- Entire struct copied into SPSC queue (no pointers, self-contained)

### LogEvent

**Purpose**: Structured telemetry for off-hot-path logging

**Definition**:
```cpp
enum class LogLevel : uint8_t { Health, Info, Error };
enum class Component : uint8_t { Core, Pipeline, Worker, Mapping, Publishing, Adapter };
enum class Code : uint8_t {
    Startup, Shutdown, HealthTick, Drops, QueueSaturated,
    LogDrops, PublishOk, PublishFail, MapMiss
};

struct LogEvent {
    uint64_t tsNs;          // Nanosecond timestamp
    LogLevel level;
    Component component;
    Code code;
    uint64_t instrumentId;  // Context (0 if not applicable)
    uint16_t shard;         // Shard ID (0xFFFF if not applicable)
    uint64_t arg0;          // Generic counter/argument
    uint64_t arg1;          // Generic counter/argument
};

static_assert(std::is_trivially_copyable_v<LogEvent>);
```

**Size**: 56 bytes

**Usage Examples**:
```cpp
// Worker health tick (every 5s)
LogEvent{
    .tsNs = nowNs(),
    .level = LogLevel::Health,
    .component = Component::Worker,
    .code = Code::HealthTick,
    .shard = shardId_,
    .arg0 = queueSize,
    .arg1 = (deltaEnqueued << 32) | deltaPublished
};

// Drop event (queue full)
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

**Formatting** (off-hot-path):
```cpp
// SpdlogLogPublisher consumer thread
std::string format(const LogEvent& e) {
    switch (e.code) {
        case Code::HealthTick:
            return fmt::format("[Health] Worker {} | Queue: {} | Enq: {} | Pub: {}",
                               e.shard, e.arg0, e.arg1 >> 32, e.arg1 & 0xFFFFFFFF);
        case Code::Drops:
            return fmt::format("[Error] Worker {} | Instrument {} | Drops: {}",
                               e.shard, e.instrumentId, e.arg0);
        // ...
    }
}
```

---

## Concurrency Model

### Thread Inventory

For `md.shards=4` configuration:

| Thread | Count | Purpose | Blocking? |
|--------|-------|---------|-----------|
| **OnixS Handler** | 1 | UDP receive + orderbook building | No (busy loop) |
| **MdPublishWorker** | 4 | Aggregate + serialize + publish | Yes (queue wait) |
| **ZmqPublishConcentrator** | 1 | Fan-in + ZMQ send | Yes (queue wait) |
| **SpdlogLogPublisher** | 5 | Format + log (1 per worker + 1 for concentrator) | Yes (queue wait) |

**Total**: ~11 threads

### Thread Communication

All inter-thread communication uses **SPSC queues** (lock-free):

```
OnixS Thread → [SPSC Queue 0] → Worker 0 Thread
OnixS Thread → [SPSC Queue 1] → Worker 1 Thread
OnixS Thread → [SPSC Queue 2] → Worker 2 Thread
OnixS Thread → [SPSC Queue 3] → Worker 3 Thread

Worker 0 Thread → [SPSC Queue 0] → Concentrator Thread
Worker 1 Thread → [SPSC Queue 1] → Concentrator Thread
Worker 2 Thread → [SPSC Queue 2] → Concentrator Thread
Worker 3 Thread → [SPSC Queue 3] → Concentrator Thread

Worker N Thread → [SPSC Log Queue N] → SpdlogLogPublisher N Thread
Concentrator Thread → [SPSC Log Queue C] → SpdlogLogPublisher C Thread
```

### SPSC Queue Implementation

**Location**: b3-md-connector/src/core/SnapshotQueueSpsc.hpp:1

**Key Features**:
```cpp
template <typename T, size_t Capacity>
class SnapshotQueueSpsc {
    static_assert(std::has_single_bit(Capacity), "Capacity must be power of 2");

    // Cache-line aligned to prevent false sharing
    alignas(64) std::atomic<size_t> head_{0};
    alignas(64) std::atomic<size_t> tail_{0};

    std::array<T, Capacity> buffer_;

public:
    bool try_enqueue(const T& item) noexcept {
        const size_t currentHead = head_.load(std::memory_order_relaxed);
        const size_t nextHead = (currentHead + 1) & (Capacity - 1);

        if (nextHead == tail_.load(std::memory_order_acquire)) {
            return false;  // Full
        }

        buffer_[currentHead] = item;
        head_.store(nextHead, std::memory_order_release);
        return true;
    }

    bool try_dequeue(T& item) noexcept {
        const size_t currentTail = tail_.load(std::memory_order_relaxed);

        if (currentTail == head_.load(std::memory_order_acquire)) {
            return false;  // Empty
        }

        item = buffer_[currentTail];
        tail_.store((currentTail + 1) & (Capacity - 1), std::memory_order_release);
        return true;
    }
};
```

**Why SPSC?**
- **Lock-free**: No mutexes, only atomics (faster)
- **Cache-friendly**: Head/tail at separate cache lines (no false sharing)
- **Wait-free enqueue/dequeue**: Constant-time operations
- **Bounded capacity**: Predictable memory footprint

**Capacity Tuning**:
- Default: 4096 entries
- Size per queue: `4096 * sizeof(OrdersSnapshot)` = ~32MB
- Trade-off: Larger = more buffering, longer drain on shutdown

---

## Performance Characteristics

### Target Latencies

| Stage | Target | Notes |
|-------|--------|-------|
| **OnixS callback → SPSC enqueue** | <500ns | Hot path (zero alloc, trivial copy) |
| **SPSC queue latency** | <100ns | Lock-free atomic ops |
| **MBO → MBP aggregation** | <2μs | O(N log N) sort, N ≤ 256 |
| **Protobuf serialization** | <3μs | Once implemented (currently stub) |
| **Topic resolution** | <100ns | Hash map lookup (shared_lock read) |
| **Worker → Concentrator SPSC** | <100ns | Another lock-free enqueue |
| **ZMQ multipart send** | <10μs | Syscall overhead |

**Total Pipeline Latency**: <20μs (OnixS callback → ZMQ publish)

### Throughput Capacity

**Assumptions**:
- 500 active instruments
- 100 updates/sec/instrument average
- Bursts up to 1000 updates/sec/instrument

**Calculations**:
- Sustained: 500 * 100 = 50,000 updates/sec
- Burst: 500 * 1000 = 500,000 updates/sec
- Per-shard sustained: 50,000 / 4 = 12,500 updates/sec/shard
- Per-shard burst: 500,000 / 4 = 125,000 updates/sec/shard

**Worker Processing Time**:
- Aggregate + serialize + publish: ~5μs
- Capacity: 200,000 updates/sec/worker
- 4 workers: 800,000 updates/sec total

**Bottleneck Analysis**:
- **Not CPU-bound**: Workers have 10x headroom
- **Potentially ZMQ-bound**: Concentrator single-threaded, syscall overhead
- **Monitoring**: Watch queue depths, if saturating → increase shards or optimize ZMQ send

### Memory Footprint

| Component | Size | Notes |
|-----------|------|-------|
| **SPSC Queue (OrdersSnapshot)** | 32MB | 4096 * 8KB per worker |
| **SPSC Queue (PublishEvent)** | 16MB | 4096 * 4KB per worker (concentrator) |
| **SPSC Queue (LogEvent)** | 256KB | 4096 * 56B per log publisher |
| **InstrumentRegistry** | ~50KB | 500 instruments * ~100B/entry |
| **Worker thread stacks** | 8MB | 4 workers * 2MB stack (default) |
| **OnixS Handler** | ~100MB | Internal SDK buffers |

**Total**: ~150MB (excluding OnixS internal)

---

## Telemetry & Observability

### Health Metrics

**Per-Worker Metrics** (emitted every 5s):
```cpp
struct WorkerHealth {
    uint64_t enqueued_total;    // Cumulative enqueued since start
    uint64_t published_total;   // Cumulative published since start
    uint64_t dropped_total;     // Cumulative dropped (queue full)
    uint32_t queue_size;        // Current queue depth
};
```

**Concentrator Metrics** (emitted every 5s):
```cpp
struct ConcentratorHealth {
    uint64_t sent_total;        // Cumulative ZMQ sends
    uint64_t dropped_total;     // Cumulative drops (all shards)
    uint32_t queue_sizes[N];    // Per-shard queue depths
};
```

### Log Levels

- **Health**: Regular metrics (not errors)
- **Info**: Lifecycle events (startup, shutdown, config changes)
- **Error**: Drops, queue saturation, publish failures

### Alerting Strategy

**Recommended Alerts**:
1. **Sustained Drops**: `dropped_total` increasing over 60s window → Action: Increase `md.shards`
2. **Queue Saturation**: `queue_size` > 90% capacity → Action: Investigate slow consumer (ZMQ)
3. **Concentrator Backlog**: Any `concentrator.queue_sizes[]` > 90% → Action: Optimize ZMQ send or add shards
4. **Missing Symbols**: `Code::MapMiss` frequent → Action: Verify `InstrumentRegistry` populated

---

## Testing Strategy

### Unit Tests

**Location**: tests/md/

**Coverage**:
- `test_md_pipeline.cpp`: FIFO ordering per instrument (10,000 events * 6 instruments)
- `test_md_worker.cpp`: Worker lifecycle (drain mode, health metrics)
- `test_mbo_to_mbp_aggregator.cpp`: Aggregation correctness (price level summing)
- `test_md_core.cpp`: Data structure properties (trivially copyable, size checks)

**Test Doubles**:
- `FakePublishSink`: Captures publishes in-memory (replaces `ZmqPublishConcentrator`)
- `FakeInstrumentTopicMapper`: Preloaded symbol map (avoids OnixS dependency)
- `FakeOrderBook`: Implements `IOrderBookView` (replaces OnixS `OrderBook`)

**Example Test**:
```cpp
TEST(MdPipelineTests, FifoPerInstrument) {
    FakePublishSink sink;
    InstrumentRegistry registry;
    registry.upsert(1001, "PETR4");

    InstrumentTopicMapper mapper(registry);
    MdPublishPipeline pipeline(4, sink, mapper);  // 4 shards

    // Send 10,000 events for instrument 1001 with incrementing timestamps
    for (uint64_t ts = 0; ts < 10000; ++ts) {
        OrdersSnapshot snap{.instrumentId = 1001, .exchangeTsNs = ts};
        pipeline.tryEnqueue(snap);
    }

    // Wait for workers to process
    std::this_thread::sleep_for(100ms);

    // Verify all events published in order
    auto pubs = sink.getPublishesForTopic("PETR4");
    ASSERT_EQ(pubs.size(), 10000);

    for (size_t i = 0; i < pubs.size(); ++i) {
        // Parse timestamp from serialized payload
        uint64_t ts = extractTimestamp(pubs[i].payload);
        EXPECT_EQ(ts, i) << "FIFO violation at index " << i;
    }
}
```

### Integration Tests

**Manual Testing** (with real OnixS SDK):
1. Configure connectivity XML for B3 test environment
2. Run connector: `./build/md/b3-md-connector test.conf`
3. Subscribe with `zmq-subscriber-tool tcp://localhost:8081`
4. Verify:
   - Topics match symbols (e.g., "PETR4", not "IID:123456")
   - Protobuf decoding succeeds
   - Timestamps increment monotonically per instrument
   - No unexpected drops (check logs)

---

## Design Decisions

### Why SPSC Over MPMC?

**SPSC** (Single Producer Single Consumer):
- Simpler implementation
- Faster (no CAS loops)
- Cache-friendly (head/tail never contested)

**MPMC** (Multi-Producer Multi-Consumer):
- Required when multiple producers write to same queue
- Not needed here: OnixS thread is single producer, each worker is single consumer

**Decision**: Use SPSC everywhere possible, only use mutexes where truly multi-threaded access occurs (e.g., `InstrumentRegistry` shared reads).

### Why Deterministic Sharding Over Work Stealing?

**Deterministic Sharding**:
- Same instrument always routes to same shard
- Guarantees FIFO ordering
- Predictable performance (no dynamic load balancing)

**Work Stealing**:
- Workers steal tasks from each other's queues
- Better load balancing (adaptive to skewed workloads)
- **Breaks FIFO ordering** (instrument A events could be processed by different workers)

**Decision**: FIFO ordering is non-negotiable for market data correctness. Accept potential load imbalance (mitigated by good hash function).

### Why Single ZMQ Socket Over Per-Worker Sockets?

**Single Socket (Concentrator)**:
- Subscribers connect to one endpoint
- Simplifies configuration
- Single slow joiner mitigation point

**Per-Worker Sockets**:
- No concentrator overhead
- Natural sharding (subscribers choose shard)
- **Complexity**: Subscribers must know N endpoints, handle shard count changes

**Decision**: Simplicity > marginal performance gain. Concentrator overhead is negligible compared to ZMQ syscall cost.

### Why Protobuf Over Raw Binary?

**Protobuf**:
- Schema evolution (add fields without breaking subscribers)
- Language-agnostic (Python/Java/Go subscribers)
- Tooling (protoc, reflection, validation)

**Raw Binary**:
- Slightly faster serialization
- Smaller wire size
- **Brittleness**: Version skew, endianness, alignment issues

**Decision**: Protobuf's benefits outweigh ~1μs serialization cost. Production systems prioritize maintainability.

### Why Drop Over Block?

**Drop (Current)**:
- OnixS callback never blocks
- Protects system from cascading failures
- Clear failure mode (counters, logs)

**Block (Alternative)**:
- Never lose updates
- **Risks**: OnixS thread blocks → feed stalls → missed UDP packets → data loss anyway

**Decision**: Dropping explicit updates is better than implicit loss from feed stalls. Capacity planning should prevent drops under normal load.

---

## Future Enhancements

### 1. Dynamic Protobuf Schema

**Current**: Stub serialization (key=value format)

**Future**:
```protobuf
message BookSnapshot {
    uint64 instrument_id = 1;
    uint64 exchange_ts_ns = 2;
    repeated Level bids = 3;
    repeated Level asks = 4;
}

message Level {
    int64 price = 1;  // Fixed-point mantissa
    int64 qty = 2;
}
```

**Benefit**: Standard format, subscribers can decode with protobuf libraries

### 2. Instrument Registry Auto-Population

**Current**: Manual upsert (TODO in main.cpp)

**Future**: Automatic population via `B3InstrumentRegistryListener`
- Subscribes to `SecurityDefinition_12` messages
- Extracts `securityId`, `symbol`
- Updates registry during feed warmup

**Benefit**: Zero manual configuration, always up-to-date symbol mappings

### 3. Adaptive Shedding

**Current**: Drop entire snapshot when queue full

**Future**: Prioritize instruments
- Mark "high-priority" instruments (e.g., liquid stocks)
- Drop low-priority updates first when under pressure
- Requires classification: `InstrumentPriorityMap`

**Benefit**: Graceful degradation (keep most important data flowing)

### 4. Multicast Publishing

**Current**: ZMQ TCP (`tcp://*:8081`)

**Future**: ZMQ PGM (multicast)
- Lower latency (no TCP ACKs)
- Better fanout (switches handle replication)
- Requires: Multicast-enabled network, PGM-capable switches

**Benefit**: Sub-10μs publish latency, unlimited subscribers

### 5. Snapshot Compression

**Current**: Send every update

**Future**: Conflation (send latest snapshot per instrument per time window)
- Buffer updates for 10ms
- Send only latest snapshot per instrument
- Reduces bandwidth for slow subscribers

**Benefit**: Lower network load, suitable for WAN subscribers

---

## Summary

The B3-Connector Market Data architecture is designed for **predictable low latency** and **high throughput** in production trading environments. Key takeaways:

1. **Sharded pipeline** with deterministic routing ensures per-instrument FIFO ordering
2. **Lock-free SPSC queues** eliminate mutex contention in hot path
3. **Zero-allocation** data structures (trivially copyable PODs) minimize GC/heap pressure
4. **Concentrator pattern** simplifies ZMQ topology (N workers → 1 socket)
5. **Off-hot-path telemetry** provides rich observability without impacting latency
6. **Drop-on-full backpressure** protects system from cascading failures

The architecture prioritizes **correctness** (FIFO ordering), **observability** (structured logs), and **testability** (clean interfaces) over micro-optimizations. Future work focuses on completing TODOs (ZMQ socket, protobuf, registry) and potential enhancements (adaptive shedding, multicast).

---

**Document Version**: 1.0
**Last Updated**: 2025-12-30
**Status**: Current as of commit bcec7bc
