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

// Struct for parameterized Add test
struct AddCase { int a; int b; int expected; };

// Test fixture for Add
class CT7_FE_P1_Add : public ::testing::TestWithParam<AddCase> {};

// Parameterized test definition
TEST_P(CT7_FE_P1_Add, AddsCorrectly) {
    // TODO: Add implementation
    // Use GetParam() to access the current AddCase
}

// Parameter set for Add test
INSTANTIATE_TEST_SUITE_P(
    CT7_FE_P1_, CT7_FE_P1_Add,
    ::testing::Values(
        // TODO: Add test cases like AddCase{2, 3, 5}, etc.
    )
);

// ===================== Divide =====================

// Normal division tests
TEST(CT7_FE_P1, Divide_Normal) {
    // TODO: Test regular integer division results
}

// Exception test for division by zero
TEST(CT7_FE_P1, Divide_ThrowsOnZero) {
    // TODO: Use EXPECT_THROW to verify exception when b == 0
}

// ===================== Factorial =====================

// Base and loop cases
TEST(CT7_FE_P1, Factorial_BaseCases) {
    // TODO: Test factorial(0), factorial(1)
}

// Multi-iteration case
TEST(CT7_FE_P1, Factorial_LoopCase) {
    // TODO: Test factorial(5)
}

// Negative input exception case
TEST(CT7_FE_P1, Factorial_ThrowsOnNegative) {
    // TODO: Test factorial(-1) should throw
}

// ===================== IsEven =====================

// Covers both even and odd cases
TEST(CT7_FE_P1, IsEven_Branches) {
    // TODO: Test even and odd integers, including negatives
}

// ===================== Sum =====================

// Covers empty, positive, and mixed vectors
TEST(CT7_FE_P1, Sum_Cases) {
    // TODO: Test empty vector, simple positive, and mixed values
}

// ===================== IsStrictlyBetween =====================

// Covers all branches (true, false at each limit, outside)
TEST(CT7_FE_P1, IsStrictlyBetween_AllBranches) {
    // TODO: Test x between, equal to low, equal to high, below, and above
}

// ===================== CrashIfNegative =====================

// Path where function does not abort
TEST(CT7_FE_P1, CrashIfNegative_NoAbortOnNonNegative) {
    // TODO: Use ASSERT_NO_THROW for non-negative inputs
}

// Path where function aborts (death test)
TEST(CT7_FE_P1, CrashIfNegative_AbortsOnNegative) {
    // TODO: Use ASSERT_DEATH for negative input
}
