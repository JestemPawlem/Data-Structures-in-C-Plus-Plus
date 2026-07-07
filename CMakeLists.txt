cmake_minimum_required(VERSION 3.10)

project(DataStructures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------- main app --------
add_executable(my_app
    src/main.cpp
 "tests/test_utils/tracker.h")

target_include_directories(my_app PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# -------- GoogleTest --------
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# Windows fix (MSVC runtime)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# -------- tests --------
enable_testing()

add_executable(tests
    "tests/test_my_vector.cpp"
    "tests/test_utils/tracker.h"
)

target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)