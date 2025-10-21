#include <gtest/gtest.h>
#include <filesystem>
#include "../../src/Exercises/CT7_FE_part1.cpp"

using namespace mylib;
namespace fs = std::filesystem;

// 1) ASSERTS
TEST(CT7_FE_P1_BasicAsserts, Add_Works) {
    // TODO: EXPECT_EQ(Add(2, 3), 5);
}

TEST(CT7_FE_P1_BasicAsserts, Divide_ThrowsOnZero) {
    // TODO: EXPECT_THROW(Divide(10, 0), std::invalid_argument);
}

TEST(CT7_FE_P1_BasicAsserts, Factorial_Boundaries) {
    // TODO: Factorial(0)==1, Factorial(5)==120
    // TODO: Factorial(-1) throws std::invalid_argument
}

// 2) FIXTURE
class CT7_FE_P1_AccumulatorTest : public ::testing::Test {
protected:
    void SetUp() override { acc.Reset(); }
    Accumulator acc;
};

TEST_F(CT7_FE_P1_AccumulatorTest, StartsAtZero) {
    // TODO
}

TEST_F(CT7_FE_P1_AccumulatorTest, Add_AccumulatesValues) {
    // TODO
}

// 3) PARAMETERIZED
class CT7_FE_P1_IsEvenParamTest : public ::testing::TestWithParam<int> {};
TEST_P(CT7_FE_P1_IsEvenParamTest, ReturnsTrueForEvenNumbers) {
    // TODO
}
INSTANTIATE_TEST_SUITE_P(
    CT7_FE_P1_EvenNumbers, CT7_FE_P1_IsEvenParamTest,
    ::testing::Values(0, 2, 4, 100, -6)
);

class CT7_FE_P1_IsOddParamTest : public ::testing::TestWithParam<int> {};
TEST_P(CT7_FE_P1_IsOddParamTest, ReturnsFalseForOddNumbers) {
    // TODO
}
INSTANTIATE_TEST_SUITE_P(
    CT7_FE_P1_OddNumbers, CT7_FE_P1_IsOddParamTest,
    ::testing::Values(1, 3, 5, -9)
);

// 4) PREDICATE
TEST(CT7_FE_P1_PredicateTests, ValueIsBetweenExclusive) {
    // TODO: EXPECT_PRED3(IsStrictlyBetween, 5, 0, 10);
}

// 5) DEATH TESTS
TEST(CT7_FE_P1_DeathTests, AbortOnNegative) {
    // TODO: EXPECT_DEATH(CrashIfNegative(-1), "negative");
}

TEST(CT7_FE_P1_DeathTests, NoAbortOnNonNegative) {
    // TODO: EXPECT_NO_THROW(CrashIfNegative(0));
}

TEST(CT7_FE_P1_DeathTests, ExitCodeCheckExample) {
    auto child = []() { std::exit(0); };
    EXPECT_EXIT(child(), ::testing::ExitedWithCode(0), ".*");
}

// 6) SKIP
TEST(CT7_FE_P1_SkipExamples, SkipWhenConfigMissing) {
    if (!fs::exists("config.json")) {
        GTEST_SKIP() << "config.json not found — skipping test";
    }
    EXPECT_TRUE(true);
}

// 7) DISABLE
TEST(CT7_FE_P1_FeatureX, DISABLED_TODO_ImplementMe) {
    // This test will not run until the prefix is removed
}
