cmake_minimum_required(VERSION 3.13)  # CMake version check
project(assign1)                      # Create project "assign1"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

# Add main.cpp file of project directory as source file
set(SOURCE_FILES readyqueue.cpp pcbtable.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(assign1_test1 ${SOURCE_FILES} test1.cpp)
add_executable(assign1_test2 ${SOURCE_FILES} test2.cpp)