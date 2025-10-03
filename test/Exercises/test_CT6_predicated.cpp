#include <gtest/gtest.h>
#include "../../src/Exercises/CT6_predicated.cpp"  // include the implementation file

using namespace bank;

// -----------------------------
// Tests for CT6_IsPositiveAmount
// -----------------------------

// Positive numbers should return true
TEST(CT6_IsPositiveAmountTests, PositiveNumbersReturnTrue)
{
    // Normal style: simple boolean check
    EXPECT_TRUE(CT6_IsPositiveAmount(10.0));
    EXPECT_TRUE(CT6_IsPositiveAmount(0.01));

    // Predicate style: EXPECT_PRED1 gives better failure messages
    // If this fails, it will print the argument value that was tested.
    double x = 5.5;
    EXPECT_PRED1(CT6_IsPositiveAmount, x);
}

// Zero and negative numbers should return false
TEST(CT6_IsPositiveAmountTests, ZeroAndNegativeReturnFalse)
{
    // Normal style
    EXPECT_FALSE(CT6_IsPositiveAmount(0.0));
    EXPECT_FALSE(CT6_IsPositiveAmount(-1.0));

    // Predicate style can still be used for debugging
    // (but here we combine it with EXPECT_FALSE to show intent).
    double x = -2.5;
    EXPECT_FALSE(CT6_IsPositiveAmount(x));
}

/*
 Why use EXPECT_PRED1 instead of just EXPECT_TRUE?
 ------------------------------------------------
 EXPECT_TRUE(CT6_IsPositiveAmount(x)) will fail with a generic message:
    Value of: CT6_IsPositiveAmount(x)
    Actual: false

 EXPECT_PRED1(CT6_IsPositiveAmount, x) will fail with a more detailed message:
    CT6_IsPositiveAmount(x) evaluates to false, where
    x = -2.5

 This extra information (showing the actual argument values) is the main
 advantage of predicate assertions in GoogleTest.
*/
