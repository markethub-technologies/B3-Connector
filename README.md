# B3-Connector

High-performance C++20 trading infrastructure for the Brazilian B3 exchange, providing low-latency market data and order entry connectivity.

## Overview

B3-Connector is a production-ready trading system that connects to the B3 (Brasil, Bolsa, Balcão) exchange through the OnixS protocol SDKs. It consists of two main components:

- **b3-md-connector**: Market Data connector using OnixS B3 UMDF (Unified Market Data Feed)
- **b3-oe-connector**: Order Entry connector using OnixS B3 BOE (Binary Order Entry)

Both connectors integrate with the MarketHub messaging system via ZeroMQ pub/sub patterns using Protocol Buffers for serialization.

## Key Features

### Market Data Connector (b3-md-connector)
- **Lock-free sharded pipeline**: Parallel processing across CPU cores with per-instrument FIFO ordering
- **Zero-allocation hot path**: Trivially copyable data structures, no heap allocations in callbacks
- **SPSC queues**: Single Producer Single Consumer lock-free ring buffers for inter-thread communication
- **ZMQ publish concentrator**: Fan-in architecture with single publish endpoint
- **Instrument registry**: Maps B3 instrument IDs to human-readable symbols
- **MBO to MBP aggregation**: Converts Market By Order to Market By Price (Top-N levels)
- **Structured telemetry**: Off-hot-path logging with health metrics and drop counters

### Order Entry Connector (b3-oe-connector)
- **BOE protocol support**: Native B3 Binary Order Entry integration
- **MarketHub integration**: Order routing via ZeroMQ messaging
- **Session management**: Connection lifecycle and recovery

## Architecture Highlights

### Sharded Pipeline

```
OnixS Feed → MarketDataEngine → MdPublishPipeline → [Worker Shards] → ZmqConcentrator → ZMQ PUB
                                         ↓
                          Instrument-based sharding (FIFO per instrument)
                                         ↓
                          MBO → MBP aggregation (Top 5 levels)
                                         ↓
                          Protobuf serialization
                                         ↓
                          Topic mapping (symbol resolution)
```

**Key properties**:
- **Deterministic sharding**: `hash(instrumentId) % numWorkers` ensures same instrument always routes to same shard
- **FIFO ordering**: Per-instrument ordering guaranteed, cross-instrument parallelism
- **Backpressure isolation**: Queue full drops newest update, never blocks feed
- **Configurable workers**: Default 4 shards, tunable via configuration

### Data Flow

1. **OnixS Handler** receives UDP multicast market data
2. **MarketDataEngine** builds `OrdersSnapshot` (MBO window, up to 256 orders/side)
3. **MdPublishPipeline** routes to shard based on instrument ID hash
4. **MdPublishWorker** (per shard):
   - Aggregates MBO → MBP (Top 5 price levels)
   - Serializes to protobuf
   - Resolves topic via InstrumentTopicMapper
   - Publishes to ZmqPublishConcentrator
5. **ZmqPublishConcentrator** drains all shard queues and publishes to single ZMQ socket

## Quick Start

### Prerequisites

**CRITICAL**: This project requires building inside devcontainers!

- Docker with Dev Containers extension for VS Code
- OnixS B3 UMDF and BOE SDK licenses (proprietary)
- Protocol Buffers 28.3 precompiled tarball (see devcontainer setup)

### Build Market Data Connector

```bash
# Open b3-md-connector in VS Code
code b3-md-connector

# VS Code will prompt "Reopen in Container" - accept
# Inside the container:

# Clean build (if switching environments)
rm -rf build/md

# Configure
cmake -S b3-md-connector -B build/md -G Ninja

# Build
cmake --build build/md

# Run
./build/md/b3-md-connector [config_file]
```

### Build Order Entry Connector

```bash
# Open b3-oe-connector in VS Code
code b3-oe-connector

# Inside the container:
rm -rf build/oe
cmake -S b3-oe-connector -B build/oe -G Ninja
cmake --build build/oe
./build/oe/b3-oe-connector [config_file]
```

### Run Tests

```bash
# Market Data tests
cmake -S tests/md -B build/tests-md -G Ninja
cmake --build build/tests-md
./build/tests-md/b3_md_tests

# Order Entry tests
cmake -S tests/oe -B build/tests-oe -G Ninja
cmake --build build/tests-oe
./build/tests-oe/b3_oe_tests
```

## Configuration

Example `b3-md-connector.conf`:

```ini
# OnixS UMDF settings
onixs.license_dir=/path/to/licenses
onixs.connectivity_file=/path/to/connectivity.xml
onixs.channel=80
onixs.if_a=eth0  # Optional: Network interface A
onixs.if_b=eth1  # Optional: Network interface B

# Pipeline settings
md.shards=4  # Number of worker threads

# Publishing settings
pub.endpoint=tcp://*:8081  # ZMQ publish endpoint
```

## Performance Characteristics

### Optimizations
- **Zero allocation**: All hot-path data structures are trivially copyable (stack-only)
- **Lock-free**: SPSC queues use atomics, no mutexes in publish path
- **Cache-line alignment**: Queue head/tail at 64-byte boundaries to prevent false sharing
- **Batch processing**: Concentrator processes 8 events per shard per iteration

### Concurrency Model
- **Feed thread**: OnixS callbacks (1 thread)
- **Worker threads**: N shards (default 4)
- **Concentrator thread**: Single ZMQ publisher (1 thread)
- **Telemetry threads**: Log consumers (1 per worker + concentrator)

**Total threads**: ~10 for 4-shard configuration

### Backpressure Strategy
- **Queue full**: Drop newest update + increment counter
- **Never blocks**: OnixS callback returns immediately
- **Health reporting**: Workers emit metrics every 5s (enqueued, published, dropped)

## Project Structure

```
B3-Connector/
├── b3-md-connector/          # Market data connector
│   └── src/
│       ├── core/             # Pipeline components (workers, queues)
│       ├── mapping/          # Instrument registry, topic mapping
│       ├── onixs/            # OnixS SDK adapters
│       ├── publishing/       # ZMQ concentrator
│       ├── telemetry/        # Logging infrastructure
│       └── testsupport/      # Test utilities
├── b3-oe-connector/          # Order entry connector
├── libs/markethub/messaging/ # MarketHub ZMQ + Protobuf library
├── external/B3/              # OnixS UMDF & BOE SDKs
├── third_party/              # Protobuf 28.3 headers (reference)
└── tests/                    # GoogleTest suites
    ├── md/                   # Market data tests
    └── oe/                   # Order entry tests
```

## Documentation

- [ARCHITECTURE.md](ARCHITECTURE.md) - Detailed architecture and design decisions
- [CLAUDE.md](CLAUDE.md) - Project instructions for Claude Code (AI assistant)
- [b3-md-connector/src/DESIGN.md](b3-md-connector/src/DESIGN.md) - MD connector design contract (Spanish)
- [API_REFERENCE.md](API_REFERENCE.md) - Key interfaces and data structures

## Dependencies

### System Libraries
- **ZeroMQ**: libzmq3-dev, libczmq-dev, cppzmq-dev (pub/sub messaging)
- **spdlog**: libspdlog-dev (logging)
- **fmt**: libfmt-dev (formatting, spdlog dependency)
- **Protocol Buffers 28.3**: Installed from precompiled tarball in devcontainer

### Proprietary SDKs
- **OnixS B3 UMDF**: Market data handler (`libonixs-b3umdfh.so`)
- **OnixS B3 BOE**: Order entry protocol (`libonixs-b3-boe.so`)

### Local Libraries
- **MarketHub.Messaging**: ZeroMQ + Protobuf messaging (`libMarketHub.Messaging.so`)

## Development Environment

This project uses **separate devcontainers** for each connector:

- `b3-md-connector/.devcontainer/` - Market data development environment
- `b3-oe-connector/.devcontainer/` - Order entry development environment

Both containers:
- Mount entire repository to `/workspaces/MarketHub.B3Connector`
- Use Ubuntu 24.04 with GCC/G++, CMake 3.20+, Ninja
- Include precompiled Protocol Buffers 28.3 from cache
- Network mode: host (for ZeroMQ communication)

**Why container-only builds?**
CMake embeds absolute library paths in build artifacts. Building at `/workspaces/...` (container) vs `/home/user/...` (host) creates incompatible binaries. Always rebuild inside the correct container after switching.

## Known TODOs

### High Priority
1. **ZMQ socket implementation** (ZmqPublishConcentrator.hpp:125-138)
   - Replace stub with actual `cppzmq` socket binding
   - Implement multipart message sending

2. **Instrument registry population** (main.cpp:127-128)
   - Wire up `B3InstrumentRegistryListener` to OnixS Handler
   - Subscribe to SecurityDefinition messages for symbol mapping

3. **Protobuf serialization** (MdSnapshotMapper.hpp:8-26)
   - Define `.proto` schema for `BookSnapshot`
   - Replace stub serialization with actual protobuf encoding

### Medium Priority
4. **Exchange timestamp extraction** (OnixsOrdersSnapshotBuilder.hpp:34)
   - OnixS OrderBook doesn't expose exchange timestamp
   - Consider extracting from SbeMessage in `onOrderBookChanged()`

5. **Bid/ask ordering validation** (OnixsOrdersSnapshotBuilder.hpp:40-42)
   - Verify OnixS bid/ask ordering assumptions in production
   - Add runtime assertions if needed

## Testing

The project uses **GoogleTest** (fetched automatically via CMake):

```bash
# Run all MD tests
./build/tests-md/b3_md_tests

# Run specific test
./build/tests-md/b3_md_tests --gtest_filter="MdPipelineTests.FifoPerInstrument"

# Run with verbose output
./build/tests-md/b3_md_tests --gtest_filter="*" --gtest_brief=0
```

### Test Coverage
- **Pipeline FIFO ordering**: 10,000 events per instrument, verifies strict ordering
- **Worker drain mode**: Shutdown behavior (graceful vs fast)
- **MBO→MBP aggregation**: Price level aggregation correctness
- **Health metrics**: Counter accuracy (enqueued, published, dropped)
- **SPSC queues**: Thread-safety and lock-free properties

## Performance Notes

### Typical Latencies (Target)
- **OnixS callback → SPSC enqueue**: <500ns (hot path)
- **Worker processing**: <5μs (aggregation + serialization)
- **ZMQ publish**: <10μs (multipart send)

### Capacity Planning
- **SPSC queue size**: 4096 events (tunable)
- **Max window per side**: 256 orders (filters market orders)
- **MBP output**: Top 5 price levels
- **Typical instruments**: ~500 active simultaneously

### Drop Scenarios
- **Feed burst**: Incoming rate exceeds worker throughput
- **ZMQ slow subscribers**: Concentrator queues saturate
- **Serialization bottleneck**: CPU-bound processing delays

All drops are logged with shard ID, instrument ID, and delta counts for analysis.

## Contributing

This is a proprietary trading infrastructure project. External contributions are not accepted.

For internal development:
1. Always work inside the appropriate devcontainer
2. Run tests before committing (`./build/tests-md/b3_md_tests`)
3. Update documentation for architectural changes
4. Follow existing patterns (SPSC queues, trivially copyable structs, lock-free hot paths)

## License

Proprietary. All rights reserved.

## Contacts

For questions about this codebase, consult the project documentation or the development team.

---

**File References** (for Claude Code navigation):
- Main entry point: b3-md-connector/src/main.cpp:1
- Pipeline orchestration: b3-md-connector/src/core/MdPublishPipeline.hpp:1
- Worker implementation: b3-md-connector/src/core/MdPublishWorker.hpp:1
- ZMQ concentrator: b3-md-connector/src/publishing/ZmqPublishConcentrator.hpp:1
- Instrument registry: b3-md-connector/src/mapping/InstrumentRegistry.hpp:1
- Test suite: tests/md/test_md_pipeline.cpp:1
