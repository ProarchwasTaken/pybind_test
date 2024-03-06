cmake_minimum_required(VERSION 3.10)
project("test_module")

set(EXECUTABLE_OUTPUT_PATH "../")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(".extern/pybind11")

pybind11_add_module("test_module" main.cpp)
target_compile_options("test_module" PRIVATE "-static-libgcc" "-static-libstdc++")
