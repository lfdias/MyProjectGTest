#include <gtest/gtest.h>
#include "../../src/Exercises/CT6_predicated.cpp"  // include the implementation file

using namespace bank;

// -----------------------------
// Tests for CT6_IsPositiveAmount
// -----------------------------

// Positive numbers should return true
TEST(CT6_IsPositiveAmountTests, PositiveNumbersReturnTrue)
{
    EXPECT_TRUE(CT6_IsPositiveAmount(10.0));
    EXPECT_TRUE(CT6_IsPositiveAmount(0.01));

    // Predicate style (better failure messages if it fails)
    double x = 5.5;
    EXPECT_PRED1(CT6_IsPositiveAmount, x);
}

// Zero should return false
TEST(CT6_IsPositiveAmountTests, ZeroReturnsFalse)
{
    EXPECT_FALSE(CT6_IsPositiveAmount(0.0));
}

// Negative numbers should return false
TEST(CT6_IsPositiveAmountTests, NegativeNumbersReturnFalse)
{
    EXPECT_FALSE(CT6_IsPositiveAmount(-1.0));
    EXPECT_FALSE(CT6_IsPositiveAmount(-100.5));
}
