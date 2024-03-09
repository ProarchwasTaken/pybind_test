cmake_minimum_required(VERSION 3.10)
project("test_module")

set(EXECUTABLE_OUTPUT_PATH "../")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(".extern/pybind11")

pybind11_add_module("test_module" main.cpp)
# Turns out that the missing library/DLL was libwinpthread-1.dll 
# All I had to do was statically link it and the module imports fine
# without the need of os.add_dll_directory!
target_link_libraries("test_module" PRIVATE -static -lpthread -static-libgcc -static-libstdc++)
