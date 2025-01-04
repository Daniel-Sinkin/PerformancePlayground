# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyCProject)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the source folder
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Collect all .c and .h files in the src folder
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.c")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")

# Include the src folder for header files
include_directories(${SRC_DIR})

# Add the executable target
add_executable(${PROJECT_NAME} main.c ${SOURCES})