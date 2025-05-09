cmake_minimum_required(VERSION 3.10)
project(TreeImplementation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Main executable (your main project)
add_executable(tree_tests ${SOURCES})

# Test sources
file(GLOB TEST_SOURCES "test/*.cpp")

# Test executable (for GTest)
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)