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

# 4) Generate HTML branch coverage report
gcovr -r . build \
  --exclude 'test/.*' \
  --filter 'src/.*' \
  --html --html-details --branches \
  --gcov-executable /usr/bin/gcov-11 \
  -o coverage_report.html








✅ From inside build/ (~/MyProjectGTest/build)
# 1) Clean up old coverage files in repo (only needed once from root)
# cd ~/MyProjectGTest
# find . -name '*.gcda' -o -name '*.gcno' -delete

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
















## Final exercise solution ## 



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
