# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Quick Reference

**⚠️ CRITICAL**: This project requires building inside devcontainers!
- Each connector (MD and OE) has its own devcontainer
- Host path: `/home/damian/repos/B3-Connector`
- Container path: `/workspaces/MarketHub.B3Connector`
- Open `b3-md-connector/` or `b3-oe-connector/` in VS Code → Reopen in Container
- Always run `rm -rf build/md` or `build/oe` before building to clear old paths

## Project Overview

B3-Connector is a C++20 trading infrastructure project that provides connectors for the B3 (Brasil, Bolsa, Balcão) exchange. It consists of two main executables:
- **b3-md-connector**: Market Data connector using OnixS B3 UMDF (Unified Market Data Feed)
- **b3-oe-connector**: Order Entry connector using OnixS B3 BOE (Binary Order Entry)

Both connectors communicate with the MarketHub messaging system via ZeroMQ pub/sub patterns using Protocol Buffers for message serialization.

## Architecture

### Component Structure

```
B3-Connector/
├── b3-md-connector/          # Market data connector executable
│   └── src/
│       ├── core/             # Pipeline components
│       │   ├── MarketDataEngine.hpp
│       │   ├── MdPublishPipeline.hpp      # Orchestrates worker shards
│       │   ├── MdPublishWorker.hpp        # Worker thread (aggregation + publish)
│       │   ├── OrdersSnapshot.hpp         # MBO window (up to 256 orders/side)
│       │   ├── BookSnapshot.hpp           # MBP aggregated (Top 5 levels)
│       │   ├── SnapshotQueueSpsc.hpp      # Lock-free SPSC queue
│       │   ├── MboToMbpAggregator.hpp     # MBO → MBP conversion
│       │   ├── SubscriptionRegistry.hpp   # Tracks active subscriptions per instrument
│       │   └── IOrderBookView.hpp         # Interface for OnixS abstraction
│       ├── mapping/          # Instrument mapping system
│       │   ├── InstrumentRegistry.hpp     # InstrumentId ↔ Symbol bidirectional registry
│       │   ├── InstrumentTopicMapper.hpp  # Topic resolution (symbol-only, drops if not found)
│       │   └── MdSnapshotMapper.hpp       # Protobuf serialization (✅ IMPLEMENTED)
│       ├── onixs/            # OnixS SDK adapters
│       │   ├── OnixsOrderBookListener.hpp
│       │   ├── OnixOrderBookView.hpp      # IOrderBookView interface
│       │   ├── OnixsOrdersSnapshotBuilder.hpp
│       │   └── B3InstrumentRegistryListener.hpp  # SecurityDefinition listener (✅ WIRED)
│       ├── publishing/       # ZMQ publishing infrastructure
│       │   ├── IPublishSink.hpp           # Interface for publish targets
│       │   ├── SerializedEnvelope.hpp     # Flat event struct (16KB topic + payload)
│       │   ├── PublishMessage.hpp         # Type alias for WrapperMessage
│       │   └── ZmqPublishConcentrator.hpp # Fan-in concentrator (✅ uses MarketHub.Messaging)
│       ├── messaging/        # MarketHub subscription server
│       │   ├── B3MdSubscriptionServer.hpp # On-demand subscription handler (ACTIVE)
│       │   └── B3MdSubscriptionServer.cpp # Implementation
│       ├── telemetry/        # Logging and health monitoring
│       │   ├── LogEvent.hpp               # Structured telemetry POD
│       │   ├── LogQueueSpsc.hpp           # SPSC queue for logs
│       │   └── SpdlogLogPublisher.hpp     # Off-hot-path log consumer
│       ├── testsupport/      # Test utilities
│       │   ├── FakeInstrumentTopicMapper.hpp
│       │   └── OrdersSnapshotFromMbpView.hpp
│       └── main.cpp
├── b3-oe-connector/          # Order entry connector executable
│   └── src/
│       ├── main.cpp
│       ├── OrderEngine.{hpp,cpp}
│       └── OrderMessagingServer.{hpp,cpp}
├── libs/
│   └── markethub/
│       └── messaging/        # MarketHub messaging library
│           ├── include/      # Headers for ZMQ pub/sub clients
│           └── lib/          # libMarketHub.Messaging.so
├── external/
│   └── B3/
│       ├── UMDF/            # OnixS B3 UMDF SDK (market data)
│       └── BOE/             # OnixS B3 BOE SDK (order entry)
└── tests/
    ├── md/                  # Market data tests
    │   ├── test_md_pipeline.cpp      # FIFO ordering tests (gtest)
    │   ├── test_md_worker.cpp        # Worker lifecycle tests (gtest)
    │   ├── test_md_engine.cpp
    │   ├── test_mbo_to_mbp_aggregator.cpp
    │   ├── test_mbo_to_mbp_ordering_contract.cpp
    │   ├── test_spdlog_log_publisher.cpp
    │   ├── test_messaging_lib_integration.cpp  # MarketHub.Messaging integration (standalone)
    │   ├── FakePublishSink.hpp       # Test double for ZMQ
    │   └── FakeMapper.hpp
    └── oe/                  # Order entry tests
```

### Key Dependencies

1. **MarketHub.Messaging** (libs/markethub/messaging/)
   - Custom ZeroMQ-based messaging library using protobuf
   - Provides `PublisherSubscriber`, `Publisher`, and `Subscriber` classes
   - Protocol Buffer message definitions in `include/models/*.pb.h`
   - Links against `libMarketHub.Messaging.so`

2. **OnixS B3 UMDF** (external/B3/UMDF/)
   - Third-party SDK for B3 market data feed
   - Links against `libonixs-b3umdfh.so`

3. **OnixS B3 BOE** (external/B3/BOE/)
   - Third-party SDK for B3 order entry protocol
   - Links against proprietary BOE library

4. **Additional Libraries**
   - spdlog: Logging (libspdlog-dev via apt)
   - fmt: Formatting library (dependency of spdlog, must be explicitly linked)
   - ZeroMQ: Messaging transport (libzmq3-dev, libczmq-dev, cppzmq-dev via apt)
   - Protocol Buffers 28.3: Installed in container from precompiled cache
     - Precompiled tarball: `.devcontainer/cache/protobuf-28.3-ubuntu2404-gcc-v2.tar.gz` (gitignored)
     - Installed to `/usr/local` in container during build
     - Headers only in repo: `third_party/protobuf-28.3/include/` (for reference/IDE)
     - `libMarketHub.Messaging.so` has a runtime dependency on `libprotobuf.so.28.3.0`
   - Abseil (absl): Google's C++ library collection, dependency of protobuf 28.3
     - Included in the protobuf precompiled tarball
     - Link directly using library names (e.g., `absl_log_internal_message`, `absl_strings`)
     - Required absl libs: log_internal_message, log_internal_check_op, strings, str_format_internal, base, raw_logging_internal, synchronization, time

### Market Data Pipeline Architecture (Latest)

The MD connector has been redesigned with a **sharded publish pipeline** for high-throughput, low-latency processing:

```
┌──────────────┐
│ OnixS UMDF   │  UDP multicast feed (B3 market data)
│   Handler    │
└──────┬───────┘
       │ onOrderBookUpdated()
       ▼
┌──────────────────────────────────────────────────────────────┐
│ MarketDataEngine::onOrderBookUpdated()                       │
│  - Builds OrdersSnapshot (MBO window, up to 256 orders/side) │
│  - Filters out market orders (null price)                    │
│  - Zero allocation, stack-only                               │
└──────┬───────────────────────────────────────────────────────┘
       │ pipeline.tryEnqueue(snapshot)
       ▼
┌──────────────────────────────────────────────────────────────┐
│ MdPublishPipeline                                            │
│  - Computes shard: hash(instrumentId) % numWorkers           │
│  - Routes to appropriate worker's SPSC queue                 │
│  - Guarantees: same instrument → same shard → FIFO ordering  │
└──────┬───────────────────────────────────────────────────────┘
       │
       │ Per-shard SPSC queues (lock-free)
       ▼
┌──────────────────────────────────────────────────────────────┐
│ MdPublishWorker (N threads, default N=4)                     │
│  1. Dequeue OrdersSnapshot from SPSC queue                   │
│  2. Aggregate MBO → MBP (Top 5 levels)                       │
│  3. Resolve topic: symbol only (drops if not in registry)    │
│  4. Serialize to protobuf (✅ WrapperMessage/MarketDataUpdate)│
│  5. Publish SerializedEnvelope to ZmqPublishConcentrator     │
└──────┬───────────────────────────────────────────────────────┘
       │ SerializedEnvelope (16KB: topic + protobuf payload)
       ▼
┌──────────────────────────────────────────────────────────────┐
│ ZmqPublishConcentrator (1 thread)                            │
│  - Fan-in: N SPSC queues → 1 MarketHub.Messaging Publisher   │
│  - Round-robin batching (8 events per shard per iteration)   │
│  - Uses Publisher::SendSerialized(topic, topicLen, bytes, sz)│
└──────┬───────────────────────────────────────────────────────┘
       │
       ▼
┌──────────────────────────────────────────────────────────────┐
│ MarketHub.Messaging::Publisher (tcp://*:8081)                │
│  - Wraps ZMQ PUB socket with standardized interface          │
│  - Multipart message: [topic frame][payload frame]           │
│  - Subscribers filter by topic prefix                        │
└──────────────────────────────────────────────────────────────┘
```

**Key Design Principles:**

1. **Hot Path Minimalism** (OnixS callback):
   - NO heap allocation
   - NO serialization
   - NO logging
   - NO blocking
   - Only: read Top-N orders → build OrdersSnapshot → tryEnqueue

2. **Sharding for Parallelism + Ordering**:
   - Hash-based sharding: `hash(instrumentId) % numWorkers`
   - Same instrument always routes to same shard
   - Guarantees per-instrument FIFO ordering
   - Different instruments process in parallel

3. **Lock-Free SPSC Queues**:
   - Single Producer Single Consumer ring buffers
   - Atomic operations only (no mutexes)
   - Cache-line aligned (64-byte) to prevent false sharing
   - Used for: OnixS → Workers, Workers → Concentrator, Producers → Telemetry

4. **Backpressure Strategy**:
   - Queue full → drop newest + increment counter
   - NEVER blocks OnixS callback
   - Health metrics emitted every 5s (enqueued, published, dropped)

5. **Instrument Registry & Topic Mapping** (✅ IMPLEMENTED):
   - `InstrumentRegistry`: Thread-safe bidirectional map (InstrumentId ↔ Symbol)
   - `InstrumentTopicMapper`: Resolves topic by symbol only (e.g., "PETR4")
     - Returns `{nullptr, 0}` if symbol not in registry → worker drops the message
     - **No fallback**: Messages without resolvable symbols are dropped
   - `B3InstrumentRegistryListener`: Populates registry from SecurityDefinition messages
     - Captures between first and second SequenceReset_1 messages
     - Sets `readyAtomic=true` after second reset
     - **Strict Freeze**: After ready=true, ignores all subsequent SecurityDefinition messages (fixed list)
   - **Strict Gating**: Engine drops all updates until `registryReady=true`, workers drop updates for instruments not in registry

6. **On-Demand Subscriptions** (✅ IMPLEMENTED, not yet started):
   - `B3MdSubscriptionServer`: Handles MarketDataSuscriptionRequest via MarketHub.Messaging
   - `SubscriptionRegistry`: Tracks subscriber count per instrument
   - OnixS Handler subscription only when first client subscribes (saves bandwidth)
   - OnixS Handler unsubscription when last client unsubscribes

7. **Off-Hot-Path Telemetry**:
   - Workers emit structured `LogEvent` PODs to SPSC queue
   - `SpdlogLogPublisher` consumes and formats in dedicated thread
   - No spdlog calls in hot path

### Architectural Patterns

- **Sharded Pipeline**: Parallel processing with deterministic sharding for FIFO guarantees
- **SPSC Queues**: Lock-free inter-thread communication (producer/consumer decoupling)
- **Fan-In Concentrator**: N worker queues → 1 MarketHub.Messaging Publisher (simplifies subscriber config)
- **Trivially Copyable Structs**: All hot-path data is POD (OrdersSnapshot, BookSnapshot, SerializedEnvelope, LogEvent)
- **Interface Segregation**: `IPublishSink`, `IOrderBookView` (enables testing without ZMQ/OnixS mocks)
- **RAII**: Publishers and Subscribers use RAII pattern with automatic resource cleanup
- **Thread-safe messaging**: All messaging classes use thread-safe queues with mutex/condition variables
- **Strict Registry Gating**: Engine waits for security list to load before publishing (prevents invalid topic spam)

## Build Commands

**CRITICAL: All build commands must be run inside the appropriate devcontainer!**

The project uses CMake 3.20+ with C++20 standard and requires GCC/G++. All paths below assume you're inside a devcontainer at `/workspaces/MarketHub.B3Connector`.

### Building Market Data Connector

**Inside the b3-md-connector devcontainer:**

```bash
# Clean build (if build directory exists from old paths)
rm -rf build/md

# Configure
cmake -S b3-md-connector -B build/md -G Ninja

# Build
cmake --build build/md

# Run
./build/md/b3-md-connector
```

### Building Order Entry Connector

**Inside the b3-oe-connector devcontainer:**

```bash
# Clean build (if build directory exists from old paths)
rm -rf build/oe

# Configure
cmake -S b3-oe-connector -B build/oe -G Ninja

# Build
cmake --build build/oe

# Run
./build/oe/b3-oe-connector
```

### Why Container-Only Builds?

CMake generates build files with absolute paths to shared libraries. When you build inside a container at `/workspaces/MarketHub.B3Connector`, those paths are embedded in the build artifacts. If you try to build on the host (e.g., `/home/user/repos/B3-Connector`), the linker will fail because it's looking for libraries at the container paths.

**Solution**: Always rebuild inside the correct container after switching environments.

### Running Tests

Tests use GoogleTest (fetched automatically via CMake). Tests can be run from either devcontainer since they access shared code.

**Inside any devcontainer:**

```bash
# Build and run market data tests
cmake -S tests/md -B build/tests-md -G Ninja
cmake --build build/tests-md
ctest --test-dir build/tests-md

# Or run directly
./build/tests-md/b3_md_tests

# Build and run order entry tests
cmake -S tests/oe -B build/tests-oe -G Ninja
cmake --build build/tests-oe
ctest --test-dir build/tests-oe

# Or run directly
./build/tests-oe/b3_oe_tests
```

### Running a Single Test

GoogleTest allows filtering by test name:

```bash
./build/tests-md/b3_md_tests --gtest_filter="MarketDataEngineTests.CanInstantiate"
```

### Running Integration Tests

The messaging library integration test is a standalone executable (not gtest):

```bash
# Build
cmake -S tests/md -B build/tests-md -G Ninja
cmake --build build/tests-md

# Run (interactive, connects to MarketHub server)
./build/tests-md/messaging_lib_integration_test
```

This test validates that MarketHub.Messaging library links and works correctly.

## Development Environment

**CRITICAL: This project uses separate devcontainers for each connector. You MUST build inside the appropriate devcontainer.**

### Devcontainer Architecture

Each connector has its own devcontainer configuration:
- `b3-md-connector/.devcontainer/` - Market data connector container
- `b3-oe-connector/.devcontainer/` - Order entry connector container

**Mount Point Strategy:**
- **Host path**: `/home/damian/repos/B3-Connector` (or your local path)
- **Container path**: `/workspaces/MarketHub.B3Connector` (both containers)
- Both containers mount the **entire repository** (parent directory) to allow access to shared libraries

When you open `b3-md-connector` or `b3-oe-connector` in VS Code with the Dev Containers extension, it:
1. Mounts the entire `B3-Connector` repository to `/workspaces/MarketHub.B3Connector`
2. Sets the workspace folder to `/workspaces/MarketHub.B3Connector`
3. Gives access to `libs/`, `external/`, `third_party/` and both connector directories

### Container Specifications

Both containers are based on Ubuntu 24.04 with:
- CMake 3.20+, Ninja build system
- GCC/G++ (forced via CC/CXX environment variables)
- ZeroMQ stack: libzmq3-dev, libczmq-dev, cppzmq-dev
- spdlog and fmt (libspdlog-dev via apt, which pulls in libfmt-dev as dependency)
- Protocol Buffers 28.3: Installed from precompiled tarball to `/usr/local`
- Network mode: host (for ZeroMQ communication)

**Important**: Do NOT install protobuf from apt (`libprotobuf-dev`, `protobuf-compiler`). The project uses a precompiled Protocol Buffers 28.3 tarball that's extracted during container build to avoid version mismatches with MarketHub.Messaging.

### Protobuf Setup

**BEFORE building the devcontainer**, you must place the precompiled protobuf tarball:

**For Market Data Connector:**
```
b3-md-connector/.devcontainer/cache/protobuf-28.3-ubuntu2404-gcc-v2.tar.gz
```

**For Order Entry Connector:**
```
b3-oe-connector/.devcontainer/cache/protobuf-28.3-ubuntu2404-gcc-v2.tar.gz
```

**Steps:**
1. Create the cache directories if they don't exist:
   ```bash
   mkdir -p b3-md-connector/.devcontainer/cache
   mkdir -p b3-oe-connector/.devcontainer/cache
   ```
2. Run your download script to fetch the protobuf tarball
3. The tarball should be placed in the appropriate `.devcontainer/cache/` folder
4. **Then** rebuild the devcontainer in VS Code

**What happens during build:**
- Build context is set to `../..` (goes up 2 levels from Dockerfile → reaches `B3-Connector/`)
- Path in Dockerfile: `COPY b3-md-connector/.devcontainer/cache/...` (relative to `B3-Connector/`)
- Tarball is extracted to `/usr/local` in the container
- `ldconfig` is run to register the libraries with the system

### Opening Containers in VS Code

To work on Market Data connector:
```bash
# Open the b3-md-connector folder in VS Code
# VS Code will prompt to "Reopen in Container"
code b3-md-connector
```

To work on Order Entry connector:
```bash
# Open the b3-oe-connector folder in VS Code
code b3-oe-connector
```

**Important**: Never build outside the containers! The build directories contain hardcoded container paths and will fail if used on the host system.

## CMake Configuration Details

### Shared Library Linking

Both connectors use INTERFACE libraries to manage external dependencies. All paths are relative using `CMAKE_CURRENT_SOURCE_DIR` to support the devcontainer environment.

**Market Data Connector (b3-md-connector/CMakeLists.txt):**
```cmake
# MarketHub.Messaging + Protobuf
add_library(markethub-messaging INTERFACE)
target_include_directories(markethub-messaging INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../libs/markethub/messaging/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/protobuf-28.3/include
)
target_link_libraries(markethub-messaging INTERFACE
    MarketHub.Messaging
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/protobuf-28.3/lib/libprotobuf.so
)

# OnixS UMDF
add_library(onixs-b3-umdf INTERFACE)
target_include_directories(onixs-b3-umdf INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/UMDF/include
)
target_link_libraries(onixs-b3-umdf INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/UMDF/lib/libonixs-b3umdfh.so
)
```

**Order Entry Connector (b3-oe-connector/CMakeLists.txt):**
```cmake
# Similar structure with protobuf linked by full path
target_link_libraries(markethub-messaging INTERFACE
    MarketHub.Messaging
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/protobuf-28.3/lib/libprotobuf.so
)

target_link_libraries(onixs-b3-boe INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/BOE/lib/libonixs-b3-boe.so
)
```

**Key Points:**
- Both connectors link against `libMarketHub.Messaging.so` (ZeroMQ + protobuf messaging)
- MD uses `libonixs-b3umdfh.so` (market data handler)
- OE uses `libonixs-b3-boe.so` (binary order entry)
- Protobuf 28.3 is installed from precompiled cache to `/usr/local`:
  - Linked with `-lprotobuf` (standard system library location)
  - Requires multiple Abseil (absl) libraries linked by name (e.g., `absl_log_internal_message`)
  - Headers in `third_party/protobuf-28.3/include/` are for IDE/reference only (not used in build)
  - Actual headers/libs come from `/usr/local/include` and `/usr/local/lib` in container

### Runtime Library Paths

The executables use `BUILD_RPATH` to locate shared libraries without requiring `LD_LIBRARY_PATH`:

```cmake
set_target_properties(b3-md-connector PROPERTIES
    BUILD_RPATH
        "${CMAKE_CURRENT_SOURCE_DIR}/../libs/markethub/messaging/lib;
         ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/UMDF/lib"
)
```

**Note**: Protobuf is installed in `/usr/local/lib` (standard system path) so it doesn't need to be in RPATH. The `ldconfig` command during container build registers it with the dynamic linker.

## Configuration

The MD connector uses a simple key=value configuration file format loaded at startup.

### Example Configuration (b3-md-connector.conf)

```ini
# OnixS UMDF Settings
onixs.license_dir=/path/to/licenses
onixs.connectivity_file=/path/to/connectivity.xml
onixs.channel=80           # B3 channel ID
onixs.if_a=eth0            # Optional: Network interface A (multicast)
onixs.if_b=eth1            # Optional: Network interface B (redundancy)

# Pipeline Settings
md.shards=4                # Number of worker threads (default: 4)

# Subscription Server (on-demand subscriptions)
sub.endpoint=tcp://*:8080  # Receives MarketDataSuscriptionRequest (configurable)
# Note: Responses sent on tcp://*:8082 (hardcoded)

# Market Data Publishing
pub.endpoint=tcp://*:8081  # Publishes MarketDataUpdate (book snapshots)
```

### Configuration Loading

Configuration is loaded in main.cpp using a simple parser:
```cpp
ConfigMap config = loadConfig(argv[1]);
std::string licenseDir = config["onixs.license_dir"];
uint32_t shardCount = std::stoul(config.value("md.shards", "4"));
```

## Key Data Structures

### OrdersSnapshot (MBO Window)
Located at: b3-md-connector/src/core/OrdersSnapshot.hpp:1

```cpp
struct OrdersSnapshot {
    static constexpr size_t K = 256;  // Max orders per side

    uint64_t instrumentId;
    uint64_t exchangeTsNs;
    uint64_t rptSeq, channelSeq;      // OnixS sequence numbers

    uint16_t bidCountRaw, askCountRaw; // SDK raw counts
    uint16_t bidsCopied, asksCopied;   // Actually copied (non-null price)
    uint8_t bidTruncated, askTruncated; // Truncation flags

    OrderEntry bids[K], asks[K];      // {priceMantissa, qty}
};
```
- **Trivially copyable** (no heap allocation)
- Copied in OnixS callback thread (hot path)
- Filters market orders (null price) during copy

### BookSnapshot (MBP Aggregated)
Located at: b3-md-connector/src/core/BookSnapshot.hpp:1

```cpp
template <int N>
struct BookSnapshotT {
    uint64_t instrumentId, exchangeTsNs;
    uint8_t bidCount, askCount;
    Level bids[N], asks[N];  // {price, qty}
};

using BookSnapshot = BookSnapshotT<5>;  // Top 5 levels
```
- Created in worker thread (off hot path)
- Aggregates MBO orders by price level
- Trivially copyable

### SerializedEnvelope (Inter-Thread Transport)
Located at: b3-md-connector/src/publishing/SerializedEnvelope.hpp:1

```cpp
struct SerializedEnvelope {
    static constexpr size_t kMaxTopic = 128;
    static constexpr size_t kMaxBytes = 16384;  // 16KB (increased from 4KB)

    uint32_t size{0};
    uint8_t topicLen{0};
    char topic[kMaxTopic]{};     // Not null-terminated
    uint8_t bytes[kMaxBytes]{};  // Protobuf serialized WrapperMessage
};
```
- Flat struct for inter-thread transport (16KB total)
- No pointers, no heap allocation
- Used in SPSC queues between workers and concentrator

### LogEvent (Telemetry)
Located at: b3-md-connector/src/telemetry/LogEvent.hpp:1

```cpp
struct LogEvent {
    uint64_t tsNs;
    LogLevel level;        // Health, Info, Error
    Component component;   // Core, Pipeline, Worker, Mapping, Publishing, Adapter
    Code code;             // Startup, Shutdown, HealthTick, Drops, QueueSaturated...
    uint64_t instrumentId;
    uint16_t shard;
    uint64_t arg0, arg1;   // Generic counters
};
```
- Structured telemetry (56 bytes)
- Transported via SPSC queue
- Formatted off-hot-path by SpdlogLogPublisher

## Implementation Status

### ✅ Completed Features

1. **ZMQ Publishing** (ZmqPublishConcentrator.hpp)
   - Uses `MarketHub.Messaging::Publisher` (wraps ZMQ PUB socket)
   - Multipart messages: [topic frame][payload frame]
   - Round-robin fan-in from N worker shards

2. **Instrument Registry Population** (B3InstrumentRegistryListener.hpp)
   - ✅ Wired up to OnixS Handler (main.cpp:206)
   - Captures SecurityDefinition_12 messages between SequenceReset_1 pair
   - Bidirectional map: InstrumentId ↔ Symbol
   - Sets `readyAtomic=true` after second reset
   - Strict freeze: Ignores SecurityDefinition messages after ready=true (fixed list loaded once at startup)

3. **Protobuf Serialization** (MdSnapshotMapper.hpp)
   - ✅ Implemented using `WrapperMessage` + `MarketDataUpdate`
   - Serializes BookSnapshot (MBP Top 5 levels) to protobuf
   - Topic set to symbol (e.g., "PETR4")

4. **Strict Registry Gating & Symbol-Only Publishing**
   - Engine drops all updates until `registryReady=true` (MarketDataEngine.hpp:26-28)
   - Workers drop messages when symbol cannot be resolved (MdPublishWorker.hpp:204-207)
   - **No IID:* fallback**: Only real symbols are published
   - Tracks `gatedDrops` at engine level, `dropped()` at worker level

5. **On-Demand Subscriptions** (B3MdSubscriptionServer)
   - ✅ Fully implemented and started in `main.cpp`
   - Handles `MarketDataSuscriptionRequest` via MarketHub.Messaging
   - Uses `SubscriptionRegistry` to track subscriber counts per instrument
   - Calls `handler.subscribe(iid)` / `handler.unsubscribe(iid)` on OnixS
   - Listens on tcp://*:8080, responds on tcp://*:8082

### 🔧 Remaining Work

#### High Priority
1. **Exchange Timestamp Extraction**
   - OnixS `OrderBook` doesn't expose exchange timestamp directly
   - Currently using system timestamp (`nowNs`)
   - Consider extracting from `SbeMessage` in `onOrderBookChanged()`

#### Medium Priority
2. **Bid/Ask Ordering Validation**
   - OnixS docs unclear if `bids()` are ascending or descending
   - Current assumption: `bids()` ascending (best bid at end) → iterates reverse
   - Current assumption: `asks()` ascending (best ask at start) → iterates forward
   - Add runtime assertion to verify ordering in production

3. **Health Monitoring Dashboard**
   - Consume `LogEvent` stream
   - Display real-time metrics: throughput, drops, queue depth per shard
   - Alert on sustained drops or queue saturation

#### Low Priority
4. **Dynamic Shard Count**
   - Currently requires restart to change `md.shards`
   - Could support online shard scaling (complex, non-trivial)

5. **Configurable Queue Capacities**
   - Currently hardcoded: 4096 (workers), 4096 (concentrator)
   - Make configurable via `b3-md-connector.conf`

## Known Issues & Bugs

### 🔴 Critical (Fix Before Production)

_(None - all critical issues resolved)_

### 🟠 High (Correctness Issues)

_(None - all high priority issues resolved)_

### 🟡 Medium (Code Quality)

_(None - all medium priority issues resolved)_

### 🟢 Low (Documentation Mismatch)

_(None - all low priority issues resolved)_

## MarketHub Messaging Usage Patterns

**Note**: The MD connector uses MarketHub.Messaging for both publishing market data (`ZmqPublishConcentrator` uses `Publisher::SendSerialized`) and handling subscription requests (`B3MdSubscriptionServer` uses `SubscriberPublisher`). The OE connector also uses MarketHub.Messaging for order submission/responses.

### Publisher/Subscriber Pattern

```cpp
#include <clients/PublisherSubscriber.h>

using markethub::messaging::clients::PublisherSubscriber;

// Create client with unique ID
PublisherSubscriber client(
    "my-client-id",
    "tcp://localhost:5555",  // requests endpoint
    "tcp://localhost:5556"   // responses endpoint
);

// Set callback for received messages
client.SetMessageReceivedCallback([](const WrapperMessage& msg) {
    // Handle response
});

// Start (connects both pub and sub)
client.Start();

// Send message (ClientId is automatically set)
WrapperMessage request;
// ... populate request ...
client.SendMessage(std::move(request));

// Synchronous request/response with timeout
auto responses = client.SendAndWaitForResponse(request, std::chrono::seconds(5));

// Cleanup (RAII handles stop automatically)
```

### Message Structure

Protocol Buffer messages are in `libs/markethub/messaging/include/models/*.pb.h`:
- `WrapperMessage`: Top-level message wrapper
- Event types: `events.pb.h`, `events/eventTypes.h`
- Trading messages: `trading.pb.h`
- System messages: `system.pb.h`

## Code Style

- C++20 standard required
- Headers use `.hpp` extension for project code, `.h` for external/library code
- RAII pattern for resource management
- Prefer `std::unique_ptr` for ownership
- Thread safety via `std::mutex`, `std::atomic`, and `std::condition_variable`
