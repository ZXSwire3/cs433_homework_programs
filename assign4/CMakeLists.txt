cmake_minimum_required(VERSION 3.13)  # CMake version check
project(assign4)                      # Create project "assign4"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

# Add necessary source files to SOURCE_FILES variable
set(SOURCE_FILES buffer.cpp)

## Add executable target with source files listed in SOURCE_FILES variable
add_executable(assign4 ${SOURCE_FILES} main.cpp)