// CT7_FE_P2_tests_by_function.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <utility>

#include "mylib_buggy.hpp"
using namespace mylib;

// ===============================
// Add
// ===============================
TEST(CT7_FE_P2_Add, Basic) { TODO; }
TEST(CT7_FE_P2_Add, NegativesAndZero) { TODO; }

// ===============================
// Divide
// ===============================
TEST(CT7_FE_P2_Divide, ThrowsOnZero) { TODO; }
TEST(CT7_FE_P2_Divide, IntegerDivisionExamples) { TODO; }

// ===============================
// Factorial
// ===============================
TEST(CT7_FE_P2_Factorial, ZeroAndSmall) { TODO; }
TEST(CT7_FE_P2_Factorial, NegativeInput) { TODO; }

// ===============================
// IsEven
// ===============================
TEST(CT7_FE_P2_IsEven, TrueForEven) { TODO; }
TEST(CT7_FE_P2_IsEven, FalseForOdd) { TODO; }

// ===============================
// Sum
// ===============================
TEST(CT7_FE_P2_Sum, EmptySingleMultiple) { TODO; }
TEST(CT7_FE_P2_Sum, LargeValues) { TODO; }

// ===============================
// IsStrictlyBetween
// ===============================
bool CT7_FE_P2_BetweenPred(int x, int lo, int hi) { return IsStrictlyBetween(x, lo, hi); }
TEST(CT7_FE_P2_IsStrictlyBetween, Inside) { TODO; }
TEST(CT7_FE_P2_IsStrictlyBetween, LowerEdge) { TODO; }
TEST(CT7_FE_P2_IsStrictlyBetween, UpperEdge) { TODO; }

// ===============================
// CrashIfNegative
// ===============================
TEST(CT7_FE_P2_CrashIfNegative, DeathOnNegative) { TODO; }
TEST(CT7_FE_P2_CrashIfNegative, NoDeathOnZeroOrPositive) { TODO; }

// ===============================
// Accumulator
// ===============================
class CT7_FE_P2_AccumulatorFixture : public ::testing::Test {
protected:
    void SetUp() override { acc.Reset(); }
    Accumulator acc;
};
TEST_F(CT7_FE_P2_AccumulatorFixture, StartsAtZero) { TODO; }
TEST_F(CT7_FE_P2_AccumulatorFixture, AddAccumulates) { TODO; }
TEST_F(CT7_FE_P2_AccumulatorFixture, ResetClears) { TODO; }

// ===============================
// Mean
// ===============================
TEST(CT7_FE_P2_Mean, FractionalAverage) { TODO; }
TEST(CT7_FE_P2_Mean, EmptyContainerPolicy) { TODO; }

// ===============================
// Min
// ===============================
TEST(CT7_FE_P2_Min, FindsMinimum) { TODO; }
TEST(CT7_FE_P2_Min, EmptyContainerPolicy) { TODO; }

// ===============================
// Clamp
// ===============================
TEST(CT7_FE_P2_Clamp, BelowAndAboveBounds) { TODO; }
TEST(CT7_FE_P2_Clamp, InsideRangeUnchanged) { TODO; }

// ===============================
// Power
// ===============================
TEST(CT7_FE_P2_Power, ZeroExponent) { TODO; }
TEST(CT7_FE_P2_Power, PositiveExponent) { TODO; }
TEST(CT7_FE_P2_Power, NegativeExponentPolicy) { TODO; }

// ===============================
// GCD
// ===============================
TEST(CT7_FE_P2_GCD, CommonCases) { TODO; }
TEST(CT7_FE_P2_GCD, WithZerosAndNegatives) { TODO; }

// ===============================
// IsPrime
// ===============================
class CT7_FE_P2_IsPrimeParam : public ::testing::TestWithParam<std::pair<int,bool>> {};
TEST_P(CT7_FE_P2_IsPrimeParam, Primality) { TODO; }
INSTANTIATE_TEST_SUITE_P(
    CT7_FE_P2_IsPrimeCases,
    CT7_FE_P2_IsPrimeParam,
    ::testing::Values(
        std::make_pair(-1,false), std::make_pair(0,false), std::make_pair(1,false),
        std::make_pair(2,true),  std::make_pair(3,true),  std::make_pair(4,false),
        std::make_pair(17,true), std::make_pair(21,false)
    )
);

// ===============================
// JoinStrings
// ===============================
TEST(CT7_FE_P2_JoinStrings, BasicAndEmpty) { TODO; }

// ===============================
// SafeIndex
// ===============================
TEST(CT7_FE_P2_SafeIndex, InRangeAndOutOfRange) { TODO; }
TEST(CT7_FE_P2_SafeIndex, EmptyVectorOutOfRange) { TODO; }

// ===============================
// CelsiusToFahrenheit
// ===============================
TEST(CT7_FE_P2_CelsiusToFahrenheit, KnownConversions) { TODO; }

// ===============================
// Median
// ===============================
TEST(CT7_FE_P2_Median, OddSized) { TODO; }
TEST(CT7_FE_P2_Median, EvenSized) { TODO; }
TEST(CT7_FE_P2_Median, EmptyPolicy) { TODO; }
