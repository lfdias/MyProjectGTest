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

    src/Exercises/CT1_asserts.cpp
    src/Exercises/CT2_fixture.cpp
    src/Exercises/CT3_parameterized.cpp 
    src/Exercises/CT4_skip.cpp
    src/Exercises/CT5_death.cpp 
    src/Exercises/CT6_predicated.cpp
    src/Exercises/CT7_Final_Exercise.cpp 
)

set(TEST_FILES
    test/test_my_math.cpp
    test/main_test_runner.cpp
    test/test_utilities.cpp

    test/Exercises/test_CT1_asserts.cpp
    test/Exercises/test_CT2_fixture.cpp
    test/Exercises/test_CT3_parameterized.cpp  
    test/Exercises/test_CT4_skip.cpp
    test/Exercises/test_CT5_death.cpp
    test/Exercises/test_CT6_predicated.cpp
    test/Exercises/test_CT7_Final_Exercise.cpp 
 
)

# Add all files to the executable
add_executable(run_tests ${SOURCE_FILES} ${TEST_FILES})

# Link Google Test and pthread
target_link_libraries(run_tests gtest gmock pthread)

# Enable coverage flags for GCC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")

# Link coverage libraries
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
