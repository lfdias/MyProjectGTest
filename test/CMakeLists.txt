add_subdirectory(${CMAKE_SOURCE_DIR}/googletest googletest)
enable_testing()

add_executable(runTests test_my_math.cpp)
target_link_libraries(runTests gtest gmock my_math)
