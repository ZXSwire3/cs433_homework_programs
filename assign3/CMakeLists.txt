cmake_minimum_required(VERSION 3.13)  # CMake version check
project(assign3)                      # Create project "assign3"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

# Add necessary source files to SOURCE_FILES variable
set(SOURCE_FILES pcb.h scheduler.h)

# Add source files for fcfs scheduler
set(FCFS_FILES
        driver_fcfs.cpp scheduler_fcfs.cpp
)

# Add source files for sjf scheduler
set(SJF_FILES
        driver_sjf.cpp scheduler_sjf.cpp
)

# Add source files for priority scheduler
set(PRIORITY_FILES
        driver_priority.cpp scheduler_priority.cpp
)

# Add source files for round robin scheduler
set(RR_FILES
        driver_rr.cpp scheduler_rr.cpp
)

# Add source files for priority round robin scheduler
set(PRIORITY_RR_FILES
        driver_priority_rr.cpp scheduler_priority_rr.cpp
)

# Copy schedule.txt to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/schedule.txt ${CMAKE_CURRENT_BINARY_DIR}/schedule.txt COPYONLY)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(assign3_fcfs ${SOURCE_FILES} ${FCFS_FILES})
add_executable(assign3_sjf ${SOURCE_FILES} ${SJF_FILES})
add_executable(assign3_priority ${SOURCE_FILES} ${PRIORITY_FILES})
add_executable(assign3_rr ${SOURCE_FILES} ${RR_FILES})
add_executable(assign3_priority_rr ${SOURCE_FILES} ${PRIORITY_RR_FILES})