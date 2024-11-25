
set(This ExampleTests)

#  Defines a list of source files for the test executable. In this case, there is only one source file named ExampleTests.cpp.
set(Sources
    ExampleTests.cpp
)

#  Creates an executable target named ${This} (which resolves to ExampleTests) using the specified source files (ExampleTests.cpp).
add_executable(${This} ${Sources})

# Links the test executable ${This} with the Google Test framework (gtest_main) and the Example library. 
# This ensures that the test executable has access to the testing framework and the functionality provided by the Example library.
target_link_libraries(${This} PUBLIC
    gtest_main
    Example 
)

#  Adds a test with the specified name ${This} (which resolves to ExampleTests) and command (the test executable ${This}). 
#  This sets up the test to be executed when running the test suite.
add_test( NAME ${This} COMMAND ${This} --gtest_color=yes)


