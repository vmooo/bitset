cmake_minimum_required(VERSION 4.1)
project(bitset)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(bitset
        bitset.cpp
        bitset.h
        main.cpp)
