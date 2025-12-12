cmake_minimum_required(VERSION 3.20)

# Solo configuramos GoogleTest una vez
include(FetchContent)

# Opcionales, para que no meta cosas raras
set(BUILD_GMOCK OFF CACHE BOOL "Disable gmock" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Disable gtest install" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)

FetchContent_MakeAvailable(googletest)

# Si existe el ejecutable de MD, agregamos sus tests
if (TARGET b3-md-connector)
    add_subdirectory(md)
endif()

# Si existe el ejecutable de OE, agregamos sus tests
if (TARGET b3-oe-connector)
    add_subdirectory(oe)
endif()

# Tests comunes (no dependen de un ejecutable específico)
add_subdirectory(common)