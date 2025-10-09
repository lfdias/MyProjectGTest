#include <gtest/gtest.h>
#include <filesystem>
#include "../../src/Exercises/CT7_Final_Exercise.cpp"

using namespace mylib;
namespace fs = std::filesystem;

// 1) ASSERTS
TEST(BasicAsserts, Add_Works) {
    // TODO: EXPECT_EQ(Add(2, 3), 5);
}

TEST(BasicAsserts, Divide_ThrowsOnZero) {
    // TODO: EXPECT_THROW(Divide(10, 0), std::invalid_argument);
}

TEST(BasicAsserts, Factorial_Boundaries) {
    // TODO: Factorial(0)==1, Factorial(5)==120
    // TODO: Factorial(-1) lança std::invalid_argument
}

// 2) FIXTURE
class AccumulatorTest : public ::testing::Test {
protected:
    void SetUp() override { acc.Reset(); }
    Accumulator acc;
};

TEST_F(AccumulatorTest, StartsAtZero) {
    // TODO
}

TEST_F(AccumulatorTest, Add_AccumulatesValues) {
    // TODO
}

// 3) PARAMETERIZED
class IsEvenParamTest : public ::testing::TestWithParam<int> {};
TEST_P(IsEvenParamTest, ReturnsTrueForEvenNumbers) {
    // TODO
}
INSTANTIATE_TEST_SUITE_P(EvenNumbers, IsEvenParamTest,
    ::testing::Values(0, 2, 4, 100, -6));

class IsOddParamTest : public ::testing::TestWithParam<int> {};
TEST_P(IsOddParamTest, ReturnsFalseForOddNumbers) {
    // TODO
}
INSTANTIATE_TEST_SUITE_P(OddNumbers, IsOddParamTest,
    ::testing::Values(1, 3, 5, -9));

// 4) PREDICATE
TEST(PredicateTests, ValueIsBetweenExclusive) {
    // TODO: EXPECT_PRED3(IsStrictlyBetween, 5, 0, 10);
}

// 5) DEATH TESTS
TEST(DeathTests, AbortOnNegative) {
    // TODO: EXPECT_DEATH(CrashIfNegative(-1), "negative");
}

TEST(DeathTests, NoAbortOnNonNegative) {
    // TODO: EXPECT_NO_THROW(CrashIfNegative(0));
}

TEST(DeathTests, ExitCodeCheckExample) {
    auto child = [](){ std::exit(0); };
    EXPECT_EXIT(child(), ::testing::ExitedWithCode(0), ".*");
}

// 6) SKIP
TEST(SkipExamples, SkipWhenConfigMissing) {
    if (!fs::exists("config.json")) {
        GTEST_SKIP() << "config.json not found — skipping test";
    }
    EXPECT_TRUE(true);
}

// 7) DISABLE
TEST(FeatureX, DISABLED_TODO_ImplementMe) {
    // Este teste não vai correr até remover o prefixo
}
