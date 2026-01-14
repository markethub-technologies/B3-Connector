cmake_minimum_required(VERSION 3.20)
project(b3-oe-connector CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# ============================================================
# Dependencias compartidas (solo si este es el proyecto raíz)
# ============================================================
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    # ---- MarketHub.Messaging ----
    add_library(markethub-messaging INTERFACE)

    target_include_directories(markethub-messaging INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/markethub/messaging/include
    )

    target_link_directories(markethub-messaging INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/markethub/messaging/lib
        /usr/local/lib
    )

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

    # ---- OnixS B3 BOE ----
    add_library(onixs-b3-boe INTERFACE)

    target_include_directories(onixs-b3-boe INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/BOE/include
    )

    target_link_libraries(onixs-b3-boe INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/BOE/lib/libonixs-b3-boe.so
    )

    # ---- b3-common (shared components: InstrumentRegistry, etc.) ----
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../b3-common" "${CMAKE_BINARY_DIR}/b3-common")
endif()

# ============================================================
# Executable: b3-oe-connector
# ============================================================

add_executable(b3-oe-connector
    src/main.cpp

    # Runtime wiring
    src/AppRuntime.cpp

    # BOE (session + callbacks)
    src/boe/BoeSessionListener.cpp
    src/boe/BoeSessionManager.cpp
    src/boe/BoeSessionSender.cpp

    # Orders (server + handler + translator)
    src/orders/server/OrderMessagingServer.cpp
    src/orders/core/OrderTranslator.cpp
    src/orders/core/OrderCommandHandler.cpp

    # Events (consumer loop)
    src/events/core/OrderEventProcessingLoop.cpp
)

target_include_directories(b3-oe-connector PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(b3-oe-connector PRIVATE
    spdlog::spdlog
    fmt::fmt
    markethub-messaging
    onixs-b3-boe
    b3-common
    pthread
    zmq
)

# ============================================================
# Runtime: que encuentre .so locales sin LD_LIBRARY_PATH (dev)
# ============================================================
set_target_properties(b3-oe-connector PROPERTIES
    BUILD_RPATH
        "${CMAKE_CURRENT_SOURCE_DIR}/../libs/markethub/messaging/lib;
         ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/BOE/lib"
)
