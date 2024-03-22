cmake_minimum_required(VERSION 3.13)  # CMake version check
project(assign3)                      # Create project "assign2"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

set(SOURCE_FILES pcb.h scheduler.h)

set(FCFS_FILES
        driver_fcfs.cpp scheduler_fcfs.h scheduler_fcfs.cpp
)

set(SJF_FILES
        driver_sjf.cpp scheduler_sjf.h scheduler_sjf.cpp
)

set(PRIORITY_FILES
        driver_priority.cpp scheduler_priority.h scheduler_priority.cpp
)

set(RR_FILES
        driver_rr.cpp scheduler_rr.h scheduler_rr.cpp
)

set(PRIORITY_RR_FILES
        driver_priority_rr.cpp scheduler_priority_rr.h scheduler_priority_rr.cpp
)

# Copy schedule.txt to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/schedule.txt ${CMAKE_CURRENT_BINARY_DIR}/schedule.txt COPYONLY)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(assign3_fcfs ${SOURCE_FILES} ${FCFS_FILES})
add_executable(assign3_sjf ${SOURCE_FILES} ${SJF_FILES})
add_executable(assign3_priority ${SOURCE_FILES} ${PRIORITY_FILES})
add_executable(assign3_rr ${SOURCE_FILES} ${RR_FILES})
add_executable(assign3_priority_rr ${SOURCE_FILES} ${PRIORITY_RR_FILES})