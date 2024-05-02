cmake_minimum_required(VERSION 3.13)  # CMake version check
project(assign2)                      # Create project "assign2"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

# Add necessary source files to SOURCE_FILES variable
set(SOURCE_FILES prog.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(assign2 ${SOURCE_FILES})