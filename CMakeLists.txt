# Sets the minimum required version of CMake needed to build the project. In this case, CMake version 3.13 or higher is required.
cmake_minimum_required(VERSION 3.13)

# Defines a variable named This and assigns it the value Example. This variable will be used to refer to the project later in the file.
set(This Example)

# Declares the project using the value of the This variable. 
# Additionally, it specifies that the project includes C and C++ code (C and C++ are the programming languages used in the project).
project(${This} C CXX)


set(CMAKE_C_STANDARD 99)                    # Sets the C standard to be used for compiling C code. In this case, it is set to C99.
set(CMAKE_CXX_STANDARD 11)                  # Sets the C++ standard to be used for compiling C++ code. In this case, it is set to C++11.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)     # Enables position-independent code compilation. This is useful when compiling code that will be dynamically linked (e.g., when creating a shared library).

#  Enables the testing system in the project. This allows adding and running unit tests.
enable_testing() 

#  Adds a subdirectory named "googletest" and "test" to the project. 
#  This implies that there should exist another CMakeLists.txt file in that directory defining how to build the "googletest" and "test" project.
add_subdirectory(googletest)
add_subdirectory(test)
add_subdirectory(src)

