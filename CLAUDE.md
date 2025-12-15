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
│       ├── main.cpp
│       ├── MarketDataEngine.{hpp,cpp}
│       └── MessagingServer.{hpp,cpp}
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

### Architectural Patterns

- **Engine + MessagingServer**: Both connectors follow a pattern where an Engine class handles protocol-specific logic and a MessagingServer handles ZMQ communication
- **RAII**: Publishers and Subscribers use RAII pattern with automatic resource cleanup
- **Thread-safe messaging**: All messaging classes use thread-safe queues with mutex/condition variables
- **Slow joiner mitigation**: Publishers have configurable startup delay (default 1.5s) to prevent ZMQ slow joiner problem

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

## MarketHub Messaging Usage Patterns

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
