# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(MyMathProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header directories
include_directories(include)

# Add Google Test
add_subdirectory(external/googletest)

# Clear separation between source files of the project and test files
set(SOURCE_FILES
    src/my_math.cpp
    src/utilities.cpp
)

set(TEST_FILES
    test/test_my_math.cpp
    test/main_test_runner.cpp
    test/test_utilities.cpp
)

# Add all files to the executable
add_executable(run_tests ${SOURCE_FILES} ${TEST_FILES})

# Link Google Test and pthread
target_link_libraries(run_tests gtest gmock pthread)
