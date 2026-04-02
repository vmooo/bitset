cmake_minimum_required(VERSION 4.1)
project(bitset)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

add_library(bitset STATIC
        src/bitset.cpp
        include/bitset.h
)

target_include_directories(bitset PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_executable(bitset_main
        src/main.cpp
)

target_link_libraries(bitset_main PRIVATE bitset)

enable_testing()
add_subdirectory(tests)