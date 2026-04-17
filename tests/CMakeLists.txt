include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(tests
    dynamicarray_tests.cpp
    linkedlist_tests.cpp
 "arr_sequence_tests.cpp" "list_seq_tests.cpp" "builder_tests.cpp")

target_link_libraries(tests
    PRIVATE
    seq_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)