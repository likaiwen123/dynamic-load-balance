# Author: Kaiwen Li
# Note: This file is part of the C++ library for the dynamic load balance algorithm.

cmake_minimum_required(VERSION 3.10)
project(DLB LANGUAGES CXX VERSION 0.1.0)

# Set the build type to Release by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set the output directories for the compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set the include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set the source files
set(SOURCES
    src/main.cpp
    src/lb.cpp
    src/task/calc_pi.cpp
)

# add mpi
find_package(MPI REQUIRED)
if(MPI_FOUND)
    include_directories(${MPI_INCLUDE_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS}")
    message(STATUS "MPI found: ${MPI_CXX_COMPILE_FLAGS} ${MPI_CXX_LINK_FLAGS}")
else()
    message(FATAL_ERROR "MPI not found")
endif()

# Add the executable target
add_executable(dlb ${SOURCES})
# Set the C++ standard for the target
set_target_properties(dlb PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
# Link the MPI library
target_link_libraries(dlb ${MPI_LIBRARIES})
