cmake_minimum_required(VERSION 3.13)  # CMake version check
project(assign5)                      # Create project "assign5"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

set(SOURCE_FILES pagetable.cpp replacement.cpp fifo_replacement.cpp lifo_replacement.cpp lru_replacement.cpp)

# Copy small_refs.txt to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/small_refs.txt ${CMAKE_CURRENT_BINARY_DIR}/small_refs.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/large_refs.txt ${CMAKE_CURRENT_BINARY_DIR}/large_refs.txt COPYONLY)


# Add executable target with source files listed in SOURCE_FILES variable
add_executable(assign5_1024_32 main.cpp ${SOURCE_FILES})
add_executable(assign5_2048_16 main.cpp ${SOURCE_FILES})
