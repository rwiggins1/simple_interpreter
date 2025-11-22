
cmake_minimum_required(VERSION 3.10)

# Project name
project(Simple_Interpreter CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Warning flags for g++
add_compile_options(-Wall -Wextra -pedantic)

# Debug symbols
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

include_directories(src)

# Source files
set(SOURCES
    src/main.cpp
    test/test.cpp
)

# Build executables
add_executable(interpreter src/main.cpp)
add_executable(test test/test.cpp)

# print useful info
message(STATUS "Building simple_interpreter")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
