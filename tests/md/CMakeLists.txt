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
)
target_include_directories(b3_md_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../b3-md-connector/src
)

target_link_libraries(b3_md_tests
    PRIVATE            
        markethub-messaging
        onixs-b3-umdf
        spdlog::spdlog
        GTest::gtest
        GTest::gtest_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(b3_md_tests)