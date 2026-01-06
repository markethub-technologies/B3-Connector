# B3 Market Data Connector - End-to-End Simulator

## Overview

The simulator is a complete end-to-end testing tool that runs the entire B3 market data pipeline without requiring a real B3 connection. It uses synthetic market data generation to test the full stack from securities list loading through market data publishing.

## What It Tests

✅ **InstrumentRegistry** - Loads securities and maps InstrumentId ↔ Symbol
✅ **B3InstrumentRegistryListener** - Processes SecurityDefinition messages
✅ **MarketDataEngine** - Receives OrderBook updates
✅ **MdPublishPipeline** - Sharded pipeline with FIFO ordering guarantees
✅ **MdPublishWorkers** - MBO→MBP aggregation and protobuf serialization
✅ **ZmqPublishConcentrator** - Fan-in publishing to single ZMQ endpoint
✅ **B3MdSubscriptionServer** - On-demand subscription handling
✅ **Full Protocol** - MarketHub.Messaging protobuf messages end-to-end

## Architecture

```
┌─────────────────────────────────────────────────────────┐
│ b3-md-connector-simulator                               │
├─────────────────────────────────────────────────────────┤
│  FakeOnixsHandler                                       │
│    ├─ Loads securities.json                             │
│    ├─ Triggers SecurityList (populates registry)        │
│    └─ Generates synthetic OrderBook updates (100ms)     │
│           ▼                                              │
│  [PRODUCTION CODE - UNMODIFIED]                         │
│    ├─ MarketDataEngine                                  │
│    ├─ MdPublishPipeline (4 workers)                     │
│    ├─ ZmqPublishConcentrator                            │
│    └─ B3MdSubscriptionServer                            │
└─────────────────────────────────────────────────────────┘
           │
           ▼
    tcp://localhost:8080 (subscriptions)
    tcp://localhost:8081 (market data)
    tcp://localhost:8082 (responses)
```

## Building

**Inside the b3-md-connector devcontainer:**

```bash
# Configure (if not already done)
cmake -S b3-md-connector -B build/md -G Ninja

# Build simulator and client
cmake --build build/md --target b3-md-connector-simulator
cmake --build build/md --target test-client
```

## Running

### Terminal 1: Start the Simulator

```bash
cd /workspaces/MarketHub.B3Connector
./build/md/b3-md-connector-simulator
```

You should see:
```
╔════════════════════════════════════════════════════════════╗
║  B3 Market Data Connector - End-to-End Simulator          ║
╚════════════════════════════════════════════════════════════╝

[simulator] Configuration:
  - Shards: 4
  - Subscription endpoint: tcp://*:8080 (requests)
  - Subscription response: tcp://*:8082 (responses)
  - Market data publishing: tcp://*:8081
  - Securities file: b3-md-connector/src/testsupport/securities.json

[simulator] Setting up market data pipeline...
[simulator]   ✓ ZMQ Publisher started on tcp://*:8081
[simulator]   ✓ Pipeline started with 4 workers
[simulator]   ✓ Subscription server started

[FakeHandler] Loaded security: 1 -> PETR4
[FakeHandler] Loaded security: 2 -> VALE3
[FakeHandler] Loaded security: 3 -> ITUB4
[FakeHandler] Loaded security: 4 -> BBDC4
[FakeHandler] Loaded security: 5 -> ABEV3
[FakeHandler] Loaded security: 6 -> B3SA3
[FakeHandler] Loaded security: 7 -> WEGE3
[FakeHandler] Loaded security: 8 -> RENT3
[FakeHandler] Total securities loaded: 8

[simulator]   ✓ Registry ready!

╔════════════════════════════════════════════════════════════╗
║  SIMULATOR RUNNING                                         ║
╚════════════════════════════════════════════════════════════╝

  Connect clients to:
    - Subscribe: tcp://localhost:8080 (MarketDataSuscriptionRequest)
    - Responses: tcp://localhost:8082 (MarketDataSubscriptionResponse)
    - Data:      tcp://localhost:8081 (MarketDataUpdate)

  Press Ctrl+C to stop...
```

### Terminal 2: Run the Test Client

```bash
cd /workspaces/MarketHub.B3Connector
./build/md/test-client PETR4 VALE3 ITUB4
```

You should see market data streaming:
```
╔════════════════════════════════════════════════════════════╗
║  B3 Market Data Test Client (C++)                         ║
╚════════════════════════════════════════════════════════════╝

Subscribing to symbols: PETR4, VALE3, ITUB4

[client] Connecting to subscription server...
[client] Subscribing to: PETR4
[client] Subscribing to: VALE3
[client] Subscribing to: ITUB4

[client] Connecting to market data stream...
[client] Subscribed to market data topic: PETR4
[client] Subscribed to market data topic: VALE3
[client] Subscribed to market data topic: ITUB4

╔════════════════════════════════════════════════════════════╗
║  LISTENING FOR MARKET DATA                                 ║
╚════════════════════════════════════════════════════════════╝

Press Ctrl+C to stop...

[PETR4] Bid=10900.00 (3 levels) | Ask=11100.00 (3 levels) | Count=1
[VALE3] Bid=11900.00 (3 levels) | Ask=12100.00 (3 levels) | Count=1
[ITUB4] Bid=12900.00 (3 levels) | Ask=13100.00 (3 levels) | Count=1
[PETR4] Bid=10910.00 (3 levels) | Ask=11110.00 (3 levels) | Count=2
[VALE3] Bid=11910.00 (3 levels) | Ask=12110.00 (3 levels) | Count=2
...
```

**Price Format:**
- Prices are converted from B3 mantissa format (4 decimals) to readable decimal format
- Internal: `priceMantissa = 109000000` (int64)
- Protobuf: `price = 10900.00` (double)
- Conversion happens in `MdSnapshotMapper` with negligible overhead (~0.1%)

## Configuration

### Securities File

Edit `b3-md-connector/src/testsupport/securities.json` to add/remove securities:

```json
[
  {"securityId": 1, "symbol": "PETR4"},
  {"securityId": 2, "symbol": "VALE3"},
  {"securityId": 3, "symbol": "ITUB4"}
]
```

### Update Frequency

Modify `FakeOnixsHandler::startUpdateLoop()` call in `simulator_main.cpp`:

```cpp
// Change from 100ms to 500ms
fakeHandler.startUpdateLoop(std::chrono::milliseconds(500));
```

### Worker Shards

Change `const int shards = 4;` in `simulator_main.cpp` to test with different concurrency levels.

## What Gets Tested

1. **Security List Loading**: Verifies InstrumentRegistry population
2. **Subscription Handling**: Tests on-demand subscription via MarketDataSuscriptionRequest
3. **Market Data Flow**: OrderBook → Engine → Pipeline → Workers → Concentrator → ZMQ
4. **FIFO Ordering**: Each symbol's updates maintain strict ordering
5. **Protobuf Serialization**: Full WrapperMessage → MarketDataUpdate serialization
6. **Topic Filtering**: ZMQ topic-based filtering works correctly
7. **Sharding**: Hash-based sharding maintains per-instrument FIFO

## Troubleshooting

### Simulator doesn't start

**Error**: `Cannot open b3-md-connector/src/testsupport/securities.json`

**Fix**: Run from repository root: `/workspaces/MarketHub.B3Connector` (not from inside `b3-md-connector/`)

### Client receives no data

**Check**:
1. Simulator is running and shows "Registry ready!"
2. Client subscribed to symbols that exist in `securities.json`
3. Ports 8080, 8081, 8082 are not in use by other processes

### Worker stats and Health Monitoring

The simulator emits structured telemetry via spdlog every 5 seconds. Logs are automatically decoded for readability:

**Worker Health Ticks:**
```
[2026-01-06 18:25:00.123] [info] [worker] code=health_tick shard=0 qsize=0 enq=98 pub=98
[2026-01-06 18:25:00.124] [info] [worker] code=health_tick shard=1 qsize=0 enq=98 pub=98
[2026-01-06 18:25:00.125] [info] [worker] code=health_tick shard=2 qsize=0 enq=100 pub=100
[2026-01-06 18:25:00.126] [info] [worker] code=health_tick shard=3 qsize=0 enq=98 pub=98
```

**Meaning:**
- `qsize=0`: Queue is empty (no backpressure) ✅
- `enq=98`: Received 98 messages from pipeline in last 5s
- `pub=98`: Published 98 messages to concentrator in last 5s

**Concentrator Health Tick:**
```
[2026-01-06 18:25:00.127] [info] [publishing] code=health_tick iid=0 shard=0 arg0=0 arg1=8592
```

**Meaning:**
- `arg0=0`: 0 messages dropped ✅
- `arg1=8592`: 8592 messages published via ZMQ in last 5s (~1718 msg/s)

**Queue Saturation (if it happens):**
```
[info] [worker] code=queue_saturated shard=2 qsize=4096 delta_drops=50 total_drops=150
```

**Backpressure Strategy:**
If you see drops under high load, this is expected behavior. The pipeline protects against memory exhaustion:
- Queue full → drops newest message + increments counter
- NEVER blocks OnixS callback (would miss multicast packets)
- Increase shards or decrease update frequency if drops are sustained

## Advanced Usage

### Custom Client

You can write your own client using MarketHub.Messaging:

```cpp
#include <clients/Subscriber.h>
#include <models/messages.pb.h>

using markethub::messaging::clients::Subscriber;

Subscriber client("tcp://localhost:8081");

client.SetMessageReceivedCallback([](const WrapperMessage& msg) {
  if (msg.has_market_data_update()) {
    const auto& update = msg.market_data_update();
    // Process market data...
  }
});

client.Subscribe("PETR4");
client.Start();
```

### Load Testing

Run multiple clients in parallel:

```bash
# Terminal 2
./build/md/test-client PETR4 VALE3 &

# Terminal 3
./build/md/test-client ITUB4 BBDC4 &

# Terminal 4
./build/md/test-client ABEV3 B3SA3 &
```

Monitor simulator stats to see throughput and drops under load.

## Files

- `src/simulator_main.cpp` - Simulator executable main
- `src/testsupport/FakeOnixsHandler.hpp` - Synthetic market data generator
- `src/testsupport/securities.json` - Securities configuration
- `src/testsupport/test_client_main.cpp` - Test client executable
- `SIMULATOR.md` - This file

## Differences from Production

✅ **Same Code**: All production components (Engine, Pipeline, Workers, Concentrator, Subscription Server) run unmodified

❌ **Fake Handler**: Uses `FakeOnixsHandler` instead of OnixS UMDF Handler

❌ **Synthetic Data**: Generates random OrderBook updates instead of real B3 feed

❌ **No Network**: No UDP multicast, no B3 connectivity required

❌ **Always Generates Data**: `FakeOnixsHandler` generates updates for ALL instruments continuously, ignoring subscribe/unsubscribe calls (simplification for testing)

### ZMQ PUB/SUB Behavior

**Important**: The connector **always publishes** market data via ZMQ, even when no clients are subscribed. This is **by design** and expected behavior:

1. **ZMQ PUB Socket**: Fire-and-forget pattern
   - Publisher sends messages continuously
   - ZMQ internally discards messages if no subscribers are connected
   - No performance impact on hot path

2. **Subscription Server**: Handles **logical** subscriptions
   - Clients send `MarketDataSuscriptionRequest` to port 8080
   - Server calls `handler.subscribe(instrumentId)` for OnixS
   - In production: OnixS requests data from B3 multicast feed
   - In simulator: `FakeOnixsHandler` ignores these calls (always generates data)

3. **Client-Side Filtering**: ZMQ topic-based filtering
   - Client calls `Subscribe("PETR4")` on data socket (port 8081)
   - ZMQ only delivers messages with topic matching "PETR4"
   - Other symbols are filtered at ZMQ layer, never reach application

**Why This Design?**
- ✅ High performance: No subscriber checks in hot path
- ✅ Decoupling: Publisher independent of subscriber state
- ✅ Scalability: New clients can connect/disconnect without affecting publisher
- ✅ Standard ZMQ pattern: Widely used in financial systems

## Next Steps

After successful simulator testing:

1. Verify with real B3 environment using `b3-md-connector` (main executable)
2. Configure OnixS license and connectivity in `b3-md-connector.conf`
3. Point to production B3 channel and interfaces
4. Monitor production metrics vs simulator baselines
