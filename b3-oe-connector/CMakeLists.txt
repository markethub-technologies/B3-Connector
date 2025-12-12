cmake_minimum_required(VERSION 3.20)
project(b3-oe-connector CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    )

    # TODO: ajustá "MarketHub.Messaging" al nombre real de la lib
    target_link_libraries(markethub-messaging INTERFACE MarketHub.Messaging)

    # ---- OnixS B3 BOE ----
    add_library(onixs-b3-boe INTERFACE)

    target_include_directories(onixs-b3-boe INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/BOE/include
    )

    target_link_directories(onixs-b3-boe INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/BOE/lib
    )

    # TODO: reemplazar OnixS.B3.BOE por el nombre real de la lib BOE
    # target_link_libraries(onixs-b3-boe INTERFACE OnixS.B3.BOE)
endif()

# ============================================================
# Ejecutable: b3-oe-connector
# ============================================================

add_executable(b3-oe-connector
    src/main.cpp
    src/OrderMessagingServer.cpp
    src/OrderEngine.cpp
)

target_include_directories(b3-oe-connector
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(b3-oe-connector
    PRIVATE
        markethub-messaging
        onixs-b3-boe
)