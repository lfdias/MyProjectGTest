cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add directories
include_directories(include)
add_subdirectory(test)

# Source files
add_library(my_math src/my_math.cpp)
