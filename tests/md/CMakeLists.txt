cmake_minimum_required(VERSION 3.20)
project(b3_md_tests CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
FetchContent_MakeAvailable(googletest)

find_package(spdlog REQUIRED)

# --- Dependencias compartidas (copypaste liviano del proyecto MD) ---
add_library(markethub-messaging INTERFACE)
target_include_directories(markethub-messaging INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/markethub/messaging/include
)
target_link_directories(markethub-messaging INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/markethub/messaging/lib
)
target_link_libraries(markethub-messaging INTERFACE MarketHub.Messaging)

add_library(onixs-b3-umdf INTERFACE)
target_include_directories(onixs-b3-umdf INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/B3/UMDF/include
)
target_link_directories(onixs-b3-umdf INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/B3/UMDF/lib
)

# --- Target de tests: compila directamente los .cpp de la app ---
add_executable(b3_md_tests
    test_md_core.cpp
    test_md_worker.cpp
    test_md_pipeline.cpp
    test_md_engine.cpp
    test_spdlog_log_publisher.cpp
    test_mbo_to_mbp_aggregator.cpp
    test_mbo_to_mbp_ordering_contract.cpp
    test_subscription_server.cpp
    # Include B3MdSubscriptionServer implementation
    ${CMAKE_CURRENT_SOURCE_DIR}/../../b3-md-connector/src/messaging/B3MdSubscriptionServer.cpp
)
target_include_directories(b3_md_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../b3-md-connector/src
)

target_link_libraries(b3_md_tests
    PRIVATE
        markethub-messaging
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
        onixs-b3-umdf
        spdlog::spdlog
        GTest::gtest
        GTest::gtest_main
)

# --- Messaging Library Integration Test (separate executable, not gtest) ---
add_executable(messaging_lib_integration_test
    test_messaging_lib_integration.cpp
)

target_include_directories(messaging_lib_integration_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../b3-md-connector/src
)

# Este test necesita protobuf + absl (no está en la interface básica de markethub-messaging)
find_package(fmt REQUIRED)
target_link_libraries(messaging_lib_integration_test
    PRIVATE
        markethub-messaging
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
        onixs-b3-umdf
        spdlog::spdlog
        fmt::fmt
        pthread
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(b3_md_tests)