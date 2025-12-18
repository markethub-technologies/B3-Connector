cmake_minimum_required(VERSION 3.20)
project(b3-md-connector CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# ============================================================
# MarketHub.Messaging (headers + .so local)
# ============================================================

add_library(markethub-messaging INTERFACE)

target_include_directories(markethub-messaging INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/markethub/messaging/include"
)

target_link_directories(markethub-messaging INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/markethub/messaging/lib"
    /usr/local/lib
)

# Link por nombre de lib (-lMarketHub.Messaging) -> busca libMarketHub.Messaging.so
# Protobuf 28.3 and its dependencies (Abseil) installed in /usr/local from precompiled cache
target_link_libraries(markethub-messaging INTERFACE
    MarketHub.Messaging
    protobuf
    absl_log_internal_message
    absl_log_internal_check_op
    absl_log_internal_nullguard
    absl_strings
    absl_str_format_internal
    absl_base
    absl_raw_logging_internal
    absl_synchronization
    absl_time
    absl_hash
)

# ============================================================
# OnixS UMDF (headers + libs locales)
# ============================================================

add_library(onixs-b3-umdf INTERFACE)

target_include_directories(onixs-b3-umdf INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/UMDF/include"
)

target_link_libraries(onixs-b3-umdf INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/UMDF/lib/libonixs-b3umdfh.so"
)

# ============================================================
# Executable
# ============================================================

add_executable(b3-md-connector
    src/main.cpp
)

target_include_directories(b3-md-connector PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(b3-md-connector PRIVATE
    spdlog::spdlog
    fmt::fmt
    markethub-messaging
    onixs-b3-umdf
    pthread
    zmq
)

# ============================================================
# Runtime: que encuentre .so locales sin LD_LIBRARY_PATH (dev)
# ============================================================

set_target_properties(b3-md-connector PROPERTIES
    BUILD_RPATH
        "${CMAKE_CURRENT_SOURCE_DIR}/../libs/markethub/messaging/lib;
         ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/UMDF/lib"
)
