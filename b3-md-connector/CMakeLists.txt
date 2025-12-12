cmake_minimum_required(VERSION 3.20)
project(b3-md-connector CXX)

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

    # TODO: ajustá "MarketHub.Messaging" al nombre real de la lib (.so/.a)
    target_link_libraries(markethub-messaging INTERFACE MarketHub.Messaging)

    # ---- OnixS B3 UMDF ----
    add_library(onixs-b3-umdf INTERFACE)

    target_include_directories(onixs-b3-umdf INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/UMDF/include
    )

    target_link_directories(onixs-b3-umdf INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/B3/UMDF/lib
    )

    # TODO: reemplazar OnixS.B3.UMDF por el nombre real de la lib UMDF
    # target_link_libraries(onixs-b3-umdf INTERFACE OnixS.B3.UMDF)
endif()

# ============================================================
# Ejecutable: b3-md-connector
# ============================================================

add_executable(b3-md-connector
    src/main.cpp
    src/MessagingServer.cpp
    src/MarketDataEngine.cpp
)

target_include_directories(b3-md-connector
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(b3-md-connector
    PRIVATE
        markethub-messaging
        onixs-b3-umdf
)