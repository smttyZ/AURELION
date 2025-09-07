cmake_minimum_required(VERSION 3.28)
project(AURELION)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Math library ---
add_library(math STATIC
        src/math/Vector3.cpp
)
target_include_directories(math PUBLIC src/math)

# --- Math tests ---
add_executable(math_tests
        tests/tVector3.cpp
)
target_link_libraries(math_tests PRIVATE math gtest_main)
include(GoogleTest)
gtest_discover_tests(math_tests)

# --- Main executable ---
add_executable(AURELION src/main.cpp)
target_link_libraries(AURELION PRIVATE math)
