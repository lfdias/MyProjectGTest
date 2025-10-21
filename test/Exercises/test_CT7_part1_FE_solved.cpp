#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

// --- Function prototypes (from the file under test) ---
int Add(int a, int b);
int Divide(int a, int b);
int Factorial(int n);
bool IsEven(int x);
int Sum(const std::vector<int>& v);
bool IsStrictlyBetween(int x, int low, int high);
void CrashIfNegative(int x);

// ===================== Add (PARAMETERIZED) =====================
struct AddCase { int a; int b; int expected; };

class CT7_FE_P1_Add : public ::testing::TestWithParam<AddCase> {};
TEST_P(CT7_FE_P1_Add, AddsCorrectly) {
    const AddCase& c = GetParam();
    EXPECT_EQ(Add(c.a, c.b), c.expected);
}

INSTANTIATE_TEST_SUITE_P(
    CT7_FE_P1_, CT7_FE_P1_Add,
    ::testing::Values(
        AddCase{  2,  3,   5},
        AddCase{ -2,  3,   1},
        AddCase{ -5, -7, -12},
        AddCase{  0,  0,   0}
    )
);

// ===================== Divide (normal + exception) =====================
TEST(CT7_FE_P1, Divide_Normal) {
    EXPECT_EQ(Divide(10, 2), 5);
    EXPECT_EQ(Divide(7, 3), 2);   // truncated integer division
}

TEST(CT7_FE_P1, Divide_ThrowsOnZero) {
    EXPECT_THROW(Divide(1, 0), std::invalid_argument); // branch: b == 0
}

// ===================== Factorial (base, loop, exception) =====================
TEST(CT7_FE_P1, Factorial_BaseCases) {
    EXPECT_EQ(Factorial(0), 1); // no loop iterations
    EXPECT_EQ(Factorial(1), 1); // minimal loop case
}

TEST(CT7_FE_P1, Factorial_LoopCase) {
    EXPECT_EQ(Factorial(5), 120); // multiple iterations
}

TEST(CT7_FE_P1, Factorial_ThrowsOnNegative) {
    EXPECT_THROW(Factorial(-1), std::invalid_argument); // branch: n < 0
}

// ===================== IsEven =====================
TEST(CT7_FE_P1, IsEven_Branches) {
    EXPECT_TRUE(IsEven(0));
    EXPECT_TRUE(IsEven(2));
    EXPECT_FALSE(IsEven(3));
    EXPECT_FALSE(IsEven(-3));
}

// ===================== Sum =====================
TEST(CT7_FE_P1, Sum_Cases) {
    EXPECT_EQ(Sum({}), 0);                    // empty vector (no loop)
    EXPECT_EQ(Sum({1, 2, 3}), 6);             // positive values
    EXPECT_EQ(Sum({-1, 2, -3, 4}), 2);        // mixed signs
}

// ===================== IsStrictlyBetween =====================
// To get branch coverage of 'low < x && x < high', we need cases for:
// - both true
// - first false (x <= low)
// - second false (x >= high)
TEST(CT7_FE_P1, IsStrictlyBetween_AllBranches) {
    EXPECT_TRUE(IsStrictlyBetween(5, 1, 10));   // true
    EXPECT_FALSE(IsStrictlyBetween(1, 1, 10));  // x == low
    EXPECT_FALSE(IsStrictlyBetween(0, 1, 10));  // x < low
    EXPECT_FALSE(IsStrictlyBetween(10, 1, 10)); // x == high
    EXPECT_FALSE(IsStrictlyBetween(11, 1, 10)); // x > high
}

// ===================== CrashIfNegative =====================
TEST(CT7_FE_P1, CrashIfNegative_NoAbortOnNonNegative) {
    ASSERT_NO_THROW(CrashIfNegative(0));   // does not enter if
    ASSERT_NO_THROW(CrashIfNegative(42));  // does not enter if
}

TEST(CT7_FE_P1, CrashIfNegative_AbortsOnNegative) {
    ASSERT_DEATH({ CrashIfNegative(-1); }, "negative input not allowed");
}
