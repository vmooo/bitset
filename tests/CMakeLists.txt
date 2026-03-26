include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(bitset_tests
        test_bitset.cpp
)

target_link_libraries(bitset_tests PRIVATE
        bitset
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(bitset_tests)
