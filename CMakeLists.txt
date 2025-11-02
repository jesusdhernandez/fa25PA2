cmake_minimum_required(VERSION 3.24)
project(fa25PA2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(fa25PA2
        heap.h
        main.cpp)

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/input.txt"
        COPYONLY)