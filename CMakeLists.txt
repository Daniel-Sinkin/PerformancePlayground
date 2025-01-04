cmake_minimum_required(VERSION 3.10)

project(PerformancePlayground)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Define the source directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Collect all source (.c) and header (.h) files
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.c")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")

# Include the src directory for header files
include_directories(${SRC_DIR})

# Define the executable target
add_executable(ppg.o main.c ${SOURCES})