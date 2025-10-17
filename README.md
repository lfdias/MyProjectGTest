✅ From the project root (~/MyProjectGTest)

# 1) Clean up old builds and coverage files
cd ~/MyProjectGTest
rm -rf build GTest/build external/googletest/build
find . -name '*.gcda' -o -name '*.gcno' -delete

# 2) Configure and build with GCC 11.4
CC=/usr/bin/gcc-11 CXX=/usr/bin/g++-11 \
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j

# 3) Run tests
./build/run_tests
./build/run_tests --gtest_filter=CT2*

# 4) Generate HTML branch coverage report
gcovr -r . build \
  --exclude 'test/.*' \
  --filter 'src/.*' \
  --html --html-details --branches \
  --gcov-executable /usr/bin/gcov-11 \
  -o coverage_report.html



✅ From inside build/ (~/MyProjectGTest/build)

# 1) Clean up old coverage files in repo (only needed once from root)
 cd ~/MyProjectGTest
 find . -name '*.gcda' -o -name '*.gcno' -delete

# 2) Configure project (note: .. points back to root with CMakeLists.txt)
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc-11 -DCMAKE_CXX_COMPILER=/usr/bin/g++-11

# 3) Build
make -j

# 4) Run tests
./run_tests

# 5) Generate HTML branch coverage report
gcovr -r .. . \
  --exclude '../test/.*' \
  --filter '../src/.*' \
  --html --html-details --branches \
  --gcov-executable /usr/bin/gcov-11 \
  -o coverage_report.html



# 6) Slides commands   


########################################
##             SLIDE                  ##
########################################


cmake --version

g++ --version

git --version


########################################
##             SLIDE                  ##
########################################


cd ~

mkdir MyProjectGTest

ls


########################################
##             SLIDE                  ##
########################################


cd MyProjectGTest

mkdir src include test build external


########################################
##             SLIDE                  ##
########################################


#include <iostream>

int main()
{
	std::cout << "\n\n Code is running! \n\n" << std::endl;
	return 0;
}


########################################
##             SLIDE                  ##
########################################


cd MyProjectGTest 

g++ -o main src/main.cpp

./main


########################################
##             SLIDE                  ##
########################################


#ifndef MY_MATH_H

#define MY_MATH_H

class MyMath 
{
    public:

    ~MyMath() = default;

    int add(int a, int b);

    int multiply(int a, int b);
};

#endif // MY_MATH_H


########################################
##             SLIDE                  ##
########################################


#include "my_math.h"

int MyMath::add(int a, int b) 
{
	return a + b;
}

int MyMath::multiply(int a, int b) 
{
	return a * b;
}


########################################
##             SLIDE                  ##
########################################


#include <iostream>

#include "../include/my_math.h"

int main() 
{
    MyMath math; // Instance of the MyMath class​

    int a = 3;
    int b = 4;

    std::cout << "Sum: " << math.add(a, b) << std::endl;
    return 0;
}


g++ -I./include -o my_math src/my_math.cpp src/main.cpp

./my_math


########################################
##             SLIDE                  ##
########################################


cd external 

git clone https://github.com/google/googletest.git


########################################
##             SLIDE                  ##
########################################


#include <gtest/gtest.h>

// Main function for Google Test​
int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


#include <gtest/gtest.h>
#include "../include/my_math.h"

TEST(MyMathTest, MultiplyTest) 
{
	MyMath math;
	EXPECT_EQ(math.multiply(2, 3), 6);
	EXPECT_EQ(math.multiply(-1, 1), -1);
}


########################################
##             SLIDE                  ##
########################################


# Minimum version of CMake required​
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard​
project(MyMathProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header directories​
include_directories(include)

# Add Google Test​
add_subdirectory(external/googletest)

# Clear separation between source files of the project and test files​
set(SOURCE_FILES 
src/my_math.cpp)

set(TEST_FILES
test/test_my_math.cpp
test/main_test_runner.cpp)

# Add all files to the executable​
add_executable(run_tests ${SOURCE_FILES} ${TEST_FILES})

# Link Google Test and pthread​
target_link_libraries(run_tests gtest gmock pthread)


########################################
##             SLIDE                  ##
########################################


cd ~/MyProjectGTest/build

cmake ..

make 


########################################
##             SLIDE                  ##
########################################


./run_tests


########################################
##             SLIDE                  ##
########################################


#ifndef UTILITIES_H

#define UTILITIES_

class Utilities {

    public:
    virtual ~Utilities(); // Destructor​
    virtual bool isPair(int number) const; // Checks if a number is even
};

#endif // UTILITIES_H




#include "utilities.h"

Utilities::~Utilities() {}

bool Utilities::isPair(int number) const 
{ 
    return number % 2 == 0; // Returns true if the number is even​
}




#include <gtest/gtest.h>

#include "utilities.h"

// Test for isPair function​
TEST(UtilitiesTest, IsPair) 
{
    Utilities utilities_obj;

    EXPECT_TRUE(utilities_obj.isPair(0)); // 0 is even​
    EXPECT_TRUE(utilities_obj.isPair(2)); // 2 is even​
    EXPECT_FALSE(utilities_obj.isPair(1)); // 1 is odd​
    EXPECT_FALSE(utilities_obj.isPair(-1)); // -1 is odd​
}


########################################
##             SLIDE                  ##
########################################


# Minimum version of CMake required​
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard​
project(MyMathProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header directories​
include_directories(include)

# Add Google Test​
add_subdirectory(external/googletest)

# Clear separation between source files of the project and test files​
set(SOURCE_FILES 
src/my_math.cpp
src/utilities.cpp)

set(TEST_FILES
test/test_my_math.cpp
test/main_test_runner.cpp
test/test_utilities.cpp)

# Add all files to the executable​
add_executable(run_tests ${SOURCE_FILES} ${TEST_FILES})

# Link Google Test and pthread​
target_link_libraries(run_tests gtest gmock pthread)


########################################
##             SLIDE                  ##
########################################


cd ~/MyProjectGTest/build

cmake ..

make 

./run_tests

########################################
##             SLIDE                  ##
########################################


#ifndef MOCK_UTILITIES_H
#define MOCK_UTILITIES_H
 
#include "utilities.h"
#include <gmock/gmock.h>
 
class MockUtilities : public Utilities 
{
    public:

        MOCK_METHOD(bool, isPair, (int number), (const));  
};


#endif // MOCK_UTILITIES_H​



########################################
##             SLIDE                  ##
########################################

#include <gtest/gtest.h>
#include "my_math.h"
#include "../test/mocks/mock_utilities.h"


TEST(MyMathTest, AddTest) {

    MyMath math;
    MockUtilities mockUtilities;

    EXPECT_CALL(mockUtilities, isPair(testing::_)).Times(0);  // Check pair call with any value as argument ​
    EXPECT_EQ(math.add(2, 3), 5);
    EXPECT_EQ(math.add(-1, 1), 0);
}


TEST(MyMathTest, MultiplyTest) 
{
    MyMath math;
    EXPECT_EQ(math.multiply(2, 3), 6);
    EXPECT_EQ(math.multiply(-1, 1), -1);
}


########################################
##             SLIDE                  ##
########################################


cd ~/MyProjectGTest/build

cmake ..

make

./run_tests 


########################################
##             SLIDE                  ##
########################################


# Minimum version of CMake required​
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard​
project(MyMathProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header directories​
include_directories(include)

# Add Google Test​
add_subdirectory(external/googletest)

# Clear separation between source files of the project and test files​
set(SOURCE_FILES 
src/my_math.cpp
src/utilities.cpp)

set(TEST_FILES
test/test_my_math.cpp
test/main_test_runner.cpp
test/test_utilities.cpp)

# Add all files to the executable​
add_executable(run_tests ${SOURCE_FILES} ${TEST_FILES})

# Link Google Test and pthread​
target_link_libraries(run_tests gtest gmock pthread)

# Enable coverage flags for GCC​
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")

# Link coverage libraries​
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")


########################################
##             SLIDE                  ##
########################################


cd ~/MyProjectGTest/

gcovr -r . --object-directory build --filter 'src/.*' --html --html-details --branches -o coverage_report.html --verbose

firefox coverage_report.html












# 7) Final exercise solution  



#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "../../src/Exercises/CT7_Final_Exercise.cpp"

using namespace mylib;
namespace fs = std::filesystem;

// 1) ASSERTS
TEST(BasicAsserts, Add_Works) {
    EXPECT_EQ(Add(2, 3), 5);
    EXPECT_EQ(Add(-4, 4), 0);
}

TEST(BasicAsserts, Divide_ThrowsOnZero) {
    EXPECT_THROW(Divide(10, 0), std::invalid_argument);
}

TEST(BasicAsserts, Divide_NormalCases) {
    EXPECT_EQ(Divide(9, 3), 3);
    EXPECT_EQ(Divide(-8, 2), -4);
}

TEST(BasicAsserts, Factorial_Boundaries) {
    EXPECT_EQ(Factorial(0), 1);
    EXPECT_EQ(Factorial(5), 120);
    EXPECT_THROW(Factorial(-1), std::invalid_argument);
}

// 2) FIXTURE
class AccumulatorTest : public ::testing::Test {
protected:
    void SetUp() override { acc.Reset(); }
    Accumulator acc;
};

TEST_F(AccumulatorTest, StartsAtZero) {
    EXPECT_EQ(acc.value(), 0);
}

TEST_F(AccumulatorTest, Add_AccumulatesValues) {
    acc.Add(5);
    acc.Add(7);
    EXPECT_EQ(acc.value(), 12);
    acc.Reset();
    EXPECT_EQ(acc.value(), 0);
}

// 3) PARAMETERIZED
class IsEvenParamTest : public ::testing::TestWithParam<int> {};
TEST_P(IsEvenParamTest, ReturnsTrueForEvenNumbers) {
    EXPECT_TRUE(IsEven(GetParam()));
}
INSTANTIATE_TEST_SUITE_P(EvenNumbers, IsEvenParamTest,
    ::testing::Values(0, 2, 4, 100, -6));

class IsOddParamTest : public ::testing::TestWithParam<int> {};
TEST_P(IsOddParamTest, ReturnsFalseForOddNumbers) {
    EXPECT_FALSE(IsEven(GetParam()));
}
INSTANTIATE_TEST_SUITE_P(OddNumbers, IsOddParamTest,
    ::testing::Values(1, 3, 5, -9));

// 4) PREDICATE
TEST(PredicateTests, ValueIsBetweenExclusive_PassAndFail) {
    EXPECT_PRED3(IsStrictlyBetween, 5, 0, 10);
    EXPECT_FALSE(IsStrictlyBetween(10, 0, 10));
}

// 5) DEATH TESTS
TEST(DeathTests, AbortOnNegative) {
    EXPECT_DEATH(CrashIfNegative(-1), "negative");
}

TEST(DeathTests, NoAbortOnNonNegative) {
    EXPECT_NO_THROW(CrashIfNegative(0));
    EXPECT_NO_THROW(CrashIfNegative(42));
}

TEST(DeathTests, ExitCodeCheckExample) {
    auto child = [](){ std::exit(0); };
    EXPECT_EXIT(child(), ::testing::ExitedWithCode(0), ".*");
}

// 6) SKIP
TEST(SkipExamples, SkipWhenConfigMissing_OrProceed) {
    const char* fname = "config.json";
    {
        std::ofstream ofs(fname);
        ofs << "{ \"ok\": true }";
    }
    if (!fs::exists(fname)) {
        GTEST_SKIP() << "config.json not found — skipping test";
    }
    EXPECT_TRUE(fs::exists(fname));
    fs::remove(fname);
}

// 7) DISABLE
TEST(FeatureX, DISABLED_TODO_ImplementMe) {
    EXPECT_TRUE(false) << "Remove DISABLED_ when implementing";
}

// Extra: Sum coverage
TEST(ExtraCoverage, SumVector) {
    EXPECT_EQ(Sum(std::vector<int>{}), 0);
    EXPECT_EQ(Sum(std::vector<int>{1,2,3}), 6);
}




