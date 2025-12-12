cmake_minimum_required(VERSION 3.20)
project(b3_oe_tests CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================
# GoogleTest via FetchContent
# ==========================
include(FetchContent)

# Opcionales para no instalar gtest ni gmock
set(BUILD_GMOCK OFF CACHE BOOL "Disable gmock" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Disable gtest install" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)

FetchContent_MakeAvailable(googletest)

# ==========================
# Dependencias compartidas
# ==========================

# MarketHub.Messaging
add_library(markethub-messaging INTERFACE)

target_include_directories(markethub-messaging INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/markethub/messaging/include
)

target_link_directories(markethub-messaging INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/markethub/messaging/lib
)

# TODO: ajustá "MarketHub.Messaging" al nombre real de la lib si es distinto
target_link_libraries(markethub-messaging INTERFACE MarketHub.Messaging)


# OnixS B3 BOE
add_library(onixs-b3-boe INTERFACE)

target_include_directories(onixs-b3-boe INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/B3/BOE/include
)

target_link_directories(onixs-b3-boe INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/B3/BOE/lib
)

# TODO: linkear la lib real de BOE si hace falta (nombre depende de OnixS)
# target_link_libraries(onixs-b3-boe INTERFACE OnixS.B3.BOE)


# ==========================
# Ejecutable de tests OE
# ==========================

add_executable(b3_oe_tests
    test_OrderEngine.cpp
    ../../b3-oe-connector/src/OrderEngine.cpp
    ../../b3-oe-connector/src/OrderMessagingServer.cpp
)

target_include_directories(b3_oe_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../b3-oe-connector/src
)

target_link_libraries(b3_oe_tests
    PRIVATE
        gtest_main
        markethub-messaging
        onixs-b3-boe
)

enable_testing()

add_test(NAME b3_oe_tests COMMAND b3_oe_tests)