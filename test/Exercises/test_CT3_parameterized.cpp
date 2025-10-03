#include <gtest/gtest.h>
#include "../../src/Exercises/CT3_parameterized.cpp"

using namespace bank;

// ============================================================================
// Parameter type: holds input balance, student flag, and expected fee
// ============================================================================
struct FeeCase {
    double balance;
    bool isStudent;
    double expected;
};

// Parameterized fixture
class CT3_MonthlyFee_Param : public ::testing::TestWithParam<FeeCase> {};

// Single test body
TEST_P(CT3_MonthlyFee_Param, ReturnsExpectedFee) {
    const FeeCase& p = GetParam();
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(p.balance, p.isStudent), p.expected);
}

// Instantiate with all coverage cases
INSTANTIATE_TEST_SUITE_P(
    CT3_MonthlyFee_Cases,
    CT3_MonthlyFee_Param,
    ::testing::Values(
        // Invalid input
        FeeCase{-1.0, false, 9999.0},
        FeeCase{-1.0, true,  9999.0},

        // Non-students
        FeeCase{ 0.0,   false, 5.0},
        FeeCase{999.9,  false, 5.0},
        FeeCase{1000.0, false, 2.5},
        FeeCase{4999.9, false, 2.5},
        FeeCase{5000.0, false, 0.0},

        // Students
        FeeCase{ 0.0,   true, 2.5},
        FeeCase{999.9,  true, 2.5},
        FeeCase{1000.0, true, 1.0},
        FeeCase{4999.9, true, 1.0},
        FeeCase{5000.0, true, 0.0}
    )
);


// -----------------------------------------------------------------------------
// Notes:
//
// • Because the test includes the .cpp directly, do NOT also add that source
//   file to your CMake target's SOURCE_FILES, or you'll get multiple definition.
// • If you later change the negative-balance behavior to throw instead of using
//   a sentinel, you can split the parameterization into two suites:
//     - Valid cases with EXPECT_DOUBLE_EQ / EXPECT_NEAR.
//     - Invalid cases with EXPECT_THROW.
// -----------------------------------------------------------------------------


/* SAME TEST WITHOUT PARAMETERIZED 


// test/Exercises/test_CT3_no_parameterized.cpp
#include <gtest/gtest.h>
#include "../../src/Exercises/CT3_parameterized.cpp"  // includes CT3_MonthlyFee

using namespace bank;

// -----------------------------
// Invalid input (negative balance)
// -----------------------------
TEST(CT3_MonthlyFee_Tests, NegativeBalance_NonStudent_ReturnsSentinel)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(-1.0, false), 9999.0);
}

TEST(CT3_MonthlyFee_Tests, NegativeBalance_Student_ReturnsSentinel)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(-1.0, true), 9999.0);
}

// -----------------------------
// Non-student cases
// Rules:
//   balance < 1000   -> 5.0
//   balance < 5000   -> 2.5
//   balance >= 5000  -> 0.0
// -----------------------------
TEST(CT3_MonthlyFee_Tests, NonStudent_LowBalance_Zero)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(0.0, false), 5.0);
}

TEST(CT3_MonthlyFee_Tests, NonStudent_LowBalance_JustBelow1000)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(999.9, false), 5.0);
}

TEST(CT3_MonthlyFee_Tests, NonStudent_MidBalance_LowerBound1000)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(1000.0, false), 2.5);
}

TEST(CT3_MonthlyFee_Tests, NonStudent_MidBalance_JustBelow5000)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(4999.9, false), 2.5);
}

TEST(CT3_MonthlyFee_Tests, NonStudent_HighBalance_AtLeast5000)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(5000.0, false), 0.0);
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(10000.0, false), 0.0);
}

// -----------------------------
// Student cases
// Rules:
//   balance < 1000   -> 2.5
//   balance < 5000   -> 1.0
//   balance >= 5000  -> 0.0
// -----------------------------
TEST(CT3_MonthlyFee_Tests, Student_LowBalance_Zero)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(0.0, true), 2.5);
}

TEST(CT3_MonthlyFee_Tests, Student_LowBalance_JustBelow1000)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(999.9, true), 2.5);
}

TEST(CT3_MonthlyFee_Tests, Student_MidBalance_LowerBound1000)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(1000.0, true), 1.0);
}

TEST(CT3_MonthlyFee_Tests, Student_MidBalance_JustBelow5000)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(4999.9, true), 1.0);
}

TEST(CT3_MonthlyFee_Tests, Student_HighBalance_AtLeast5000)
{
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(5000.0, true), 0.0);
    EXPECT_DOUBLE_EQ(CT3_MonthlyFee(10000.0, true), 0.0);
}



*/