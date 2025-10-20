// test_CT7_Final_Exercise_part2.cpp
// Forward declarations only (no header, no including the .cpp).
// Tests assert correct behavior. Comments are TODO-only.

#include <gtest/gtest.h>
#include <string>
#include <stdexcept>

// ---------- Forward declarations ----------
bool    InRangeExclusive(int x, int lo, int hi);

int     SumArray(const int* a, int n);
int     MinArray(const int* a, int n);
double  MeanArray(const int* a, int n);

int     GetAt(const int* a, int n, int idx);
int     CopyArray(const int* src, int* dst, int n);

std::string StringJoin2(const char* a, const char* b, const char* sep);

bool    IsValidIBAN(const std::string& iban);
double  LoanMonthlyPayment(double principal, double annual_rate, int months);

// ---------- Tests ----------

// TODO: check exclusivity of both bounds (edges must be false)
TEST(CT7_FE_P2_InRangeExclusive, LowerEdge) {
    EXPECT_FALSE(InRangeExclusive(0, 0, 10));
}
TEST(CT7_FE_P2_InRangeExclusive, UpperEdge) {
    EXPECT_FALSE(InRangeExclusive(10, 0, 10));
}
// TODO: check typical inside/outside and reversed bounds
TEST(CT7_FE_P2_InRangeExclusive, InsideOutside) {
    EXPECT_TRUE(InRangeExclusive(5, 0, 10));
    EXPECT_FALSE(InRangeExclusive(-1, 0, 10));
    EXPECT_FALSE(InRangeExclusive(11, 0, 10));
    EXPECT_FALSE(InRangeExclusive(5, 10, 0));
}

// TODO: verify empty, single, multiple; consider overflow cases later
TEST(CT7_FE_P2_SumArray, EmptySingleMultiple) {
    const int a0[] = {};
    const int a1[] = {42};
    const int a3[] = {1,2,3};
    EXPECT_EQ(SumArray(a0, 0), 0);
    EXPECT_EQ(SumArray(a1, 1), 42);
    EXPECT_EQ(SumArray(a3, 3), 6);
}
// TODO: ensure null and negative n return 0
TEST(CT7_FE_P2_SumArray, NullOrNegativeN) {
    EXPECT_EQ(SumArray(nullptr, 3), 0);
    const int a[] = {1,2,3};
    EXPECT_EQ(SumArray(a, -2), 0);
}

// TODO: confirm minimum search works and throws on invalid input
TEST(CT7_FE_P2_MinArray, FindsMinimum) {
    const int a[] = {3, 5, -1, 4, 9};
    const int b[] = {5, 7, 3};
    EXPECT_EQ(MinArray(a, 5), -1);
    EXPECT_EQ(MinArray(b, 3), 3);
}
TEST(CT7_FE_P2_MinArray, EmptyArrayPolicy) {
    const int e[] = {};
    EXPECT_THROW(MinArray(e, 0), std::invalid_argument);
    EXPECT_THROW(MinArray(nullptr, 1), std::invalid_argument);
}

// TODO: ensure average uses double division and throws on invalid input
TEST(CT7_FE_P2_MeanArray, FractionalAverage) {
    const int a[] = {1, 2};
    EXPECT_DOUBLE_EQ(MeanArray(a, 2), 1.5);
}
TEST(CT7_FE_P2_MeanArray, EmptyArrayPolicy) {
    const int e[] = {};
    EXPECT_THROW(MeanArray(e, 0), std::invalid_argument);
    EXPECT_THROW(MeanArray(nullptr, 2), std::invalid_argument);
}

// TODO: verify valid indices return element; invalid return sentinel -1
TEST(CT7_FE_P2_GetAt, InRange) {
    const int a[] = {10, 20, 30};
    EXPECT_EQ(GetAt(a, 3, 0), 10);
    EXPECT_EQ(GetAt(a, 3, 2), 30);
}
TEST(CT7_FE_P2_GetAt, OutOfRangeAndEmpty) {
    const int a[] = {10, 20};
    const int e[] = {};
    EXPECT_EQ(GetAt(a, 2, -1), -1);
    EXPECT_EQ(GetAt(a, 2, 5), -1);
    EXPECT_EQ(GetAt(e, 0, 0), -1);
    EXPECT_EQ(GetAt(nullptr, 5, 0), -1);
}

// TODO: assert full copy and correct count; also test null/zero handling
TEST(CT7_FE_P2_CopyArray, CopiesAllElements) {
    const int src[] = {1,2,3,4};
    int dst[4] = {0,0,0,0};
    ASSERT_EQ(CopyArray(src, dst, 4), 4);
    for (int i = 0; i < 4; ++i) EXPECT_EQ(dst[i], src[i]);
}
TEST(CT7_FE_P2_CopyArray, ZeroOrNull) {
    int dst[3] = {9,9,9};
    EXPECT_EQ(CopyArray(nullptr, dst, 3), 0);
    const int src[] = {1,2,3};
    EXPECT_EQ(CopyArray(src, nullptr, 3), 0);
    EXPECT_EQ(CopyArray(src, dst, 0), 0);
}

// TODO: ensure no trailing sep when one side empty; accept empty/null sep
TEST(CT7_FE_P2_StringJoin2, NoTrailingSeparator) {
    EXPECT_EQ(StringJoin2("a","b", ","), "a,b");
    EXPECT_EQ(StringJoin2("a", nullptr, ","), "a");
    EXPECT_EQ(StringJoin2(nullptr, "b", ","), "b");
    EXPECT_EQ(StringJoin2(nullptr, nullptr, ","), "");
}
TEST(CT7_FE_P2_StringJoin2, EmptyAndNullSeparator) {
    EXPECT_EQ(StringJoin2("x","y",""), "xy");
    EXPECT_EQ(StringJoin2("x","y",nullptr), "xy");
}

// TODO: basic IBAN validation: length, leading letters, alnum-only
TEST(CT7_FE_P2_IsValidIBAN, BasicValidation) {
    EXPECT_TRUE(IsValidIBAN("PT50000201231234567890154"));
    EXPECT_FALSE(IsValidIBAN("pt12"));
    EXPECT_FALSE(IsValidIBAN("123456789012345"));
    EXPECT_FALSE(IsValidIBAN("PT50-000201231234567890154"));
}

// TODO: check zero-rate case and typical monthly-rate calculation
// TODO: validate invalid months throw
TEST(CT7_FE_P2_LoanMonthlyPayment, ZeroRateAndTypical) {
    EXPECT_DOUBLE_EQ(LoanMonthlyPayment(1200.0, 0.0, 12), 100.0);
    double pmt = LoanMonthlyPayment(1000.0, 0.12, 12);
    EXPECT_NEAR(pmt, 88.848, 1e-3);
}
TEST(CT7_FE_P2_LoanMonthlyPayment, InvalidMonths) {
    EXPECT_THROW(LoanMonthlyPayment(1000.0, 0.05, 0), std::invalid_argument);
    EXPECT_THROW(LoanMonthlyPayment(1000.0, 0.05, -6), std::invalid_argument);
}
