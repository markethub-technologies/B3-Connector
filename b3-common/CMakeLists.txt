cmake_minimum_required(VERSION 3.20)
project(b3-common VERSION 1.0.0 LANGUAGES CXX)

# Header-only library for shared B3 components
add_library(b3-common INTERFACE)

target_include_directories(b3-common INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(b3-common INTERFACE cxx_std_20)
