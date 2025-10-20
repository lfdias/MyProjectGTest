// CT7_FE_P2_tests_full.cpp
#include <gtest/gtest.h>
#include <string>
#include <utility>
#include "mylib_buggy_novector.hpp"
using namespace mylib;

// Add — ASSERTS (BUG 1)
TEST(CT7_FE_P2_Add, Basic) {
    EXPECT_EQ(Add(2,3), 5);      // detects subtraction bug
    EXPECT_EQ(Add(0,0), 0);
}
TEST(CT7_FE_P2_Add, NegativesAndZero) {
    EXPECT_EQ(Add(-4,10), 6);
    EXPECT_EQ(Add(-7,-5), -12);
}

// Divide — ASSERT/THROW (BUG 2)
TEST(CT7_FE_P2_Divide, ThrowsOnZero) {
    EXPECT_THROW(Divide(10,0), std::invalid_argument); // expects throw not 0
}
TEST(CT7_FE_P2_Divide, IntegerDivisionExamples) {
    EXPECT_EQ(Divide(7,2), 3);
    EXPECT_EQ(Divide(-7,2), -3);
}

// Factorial — ASSERT/THROW (BUG 3)
TEST(CT7_FE_P2_Factorial, ZeroAndSmall) {
    EXPECT_EQ(Factorial(0), 1);
    EXPECT_EQ(Factorial(5), 120);
}
TEST(CT7_FE_P2_Factorial, NegativeInput) {
    EXPECT_THROW(Factorial(-1), std::invalid_argument);
}

// IsEven — ASSERTS (BUG 4)
TEST(CT7_FE_P2_IsEven, TrueForEven) {
    EXPECT_TRUE(IsEven(0));
    EXPECT_TRUE(IsEven(2));
    EXPECT_TRUE(IsEven(-4));
}
TEST(CT7_FE_P2_IsEven, FalseForOdd) {
    EXPECT_FALSE(IsEven(1));
    EXPECT_FALSE(IsEven(-3));
    EXPECT_FALSE(IsEven(101));
}

// InRangeExclusive — PREDICATE (BUG 5)
static bool between_pred(int x, int lo, int hi) { return InRangeExclusive(x, lo, hi); }
TEST(CT7_FE_P2_InRangeExclusive, Inside) {
    EXPECT_PRED3(between_pred, 5, 0, 10);
}
TEST(CT7_FE_P2_InRangeExclusive, LowerEdge) { EXPECT_FALSE(InRangeExclusive(0,0,10)); }
TEST(CT7_FE_P2_InRangeExclusive, UpperEdge) { EXPECT_FALSE(InRangeExclusive(10,0,10)); }

// CrashIfNegative — DEATH/NON-DEATH (BUG 6)
TEST(CT7_FE_P2_CrashIfNegative, DeathOnNegative) { EXPECT_DEATH(CrashIfNegative(-1), "negative"); }
TEST(CT7_FE_P2_CrashIfNegative, NoDeathOnZeroOrPositive) {
    EXPECT_NO_FATAL_FAILURE(CrashIfNegative(0));
    EXPECT_NO_FATAL_FAILURE(CrashIfNegative(7));
}

// Clamp — ASSERTS (BUG 7)
TEST(CT7_FE_P2_Clamp, BelowAndAboveBounds) {
    EXPECT_EQ(Clamp(-5,0,10), 0);
    EXPECT_EQ(Clamp(15,0,10), 10);
}
TEST(CT7_FE_P2_Clamp, InsideRangeUnchanged) { EXPECT_EQ(Clamp(7,0,10), 7); }

// Power — ASSERT/THROW (BUG 8)
TEST(CT7_FE_P2_Power, ZeroExponent) { EXPECT_EQ(Power(2,0), 1); }
TEST(CT7_FE_P2_Power, PositiveExponent) { EXPECT_EQ(Power(3,4), 81); }
TEST(CT7_FE_P2_Power, NegativeExponentPolicy) { EXPECT_THROW(Power(2,-1), std::invalid_argument); }

// GCD — ASSERTS (BUG 9)
TEST(CT7_FE_P2_GCD, CommonCases) {
    EXPECT_EQ(GCD(18,24), 6);
    EXPECT_EQ(GCD(-18,24), 6);
}
TEST(CT7_FE_P2_GCD, WithZerosAndNegatives) {
    EXPECT_EQ(GCD(0,0), 0);
    EXPECT_EQ(GCD(0,5), 5);
    EXPECT_EQ(GCD(7,0), 7);
}

// IsPrime — PARAMETERIZED (BUG 10)
class CT7_FE_P2_IsPrimeParam : public ::testing::TestWithParam<std::pair<int,bool>> {};
TEST_P(CT7_FE_P2_IsPrimeParam, Primality) {
    EXPECT_EQ(IsPrime(GetParam().first), GetParam().second);
}
INSTANTIATE_TEST_SUITE_P(
    CT7_FE_P2_IsPrimeCases, CT7_FE_P2_IsPrimeParam,
    ::testing::Values(
        std::make_pair(-1,false), std::make_pair(0,false), std::make_pair(1,false),
        std::make_pair(2,true),  std::make_pair(3,true),  std::make_pair(4,false),
        std::make_pair(17,true), std::make_pair(21,false)
    )
);

// CelsiusToFahrenheit — ASSERTS (BUG 11)
TEST(CT7_FE_P2_CelsiusToFahrenheit, KnownConversions) {
    EXPECT_DOUBLE_EQ(CelsiusToFahrenheit(0.0), 32.0);
    EXPECT_DOUBLE_EQ(CelsiusToFahrenheit(100.0), 212.0);
    EXPECT_DOUBLE_EQ(CelsiusToFahrenheit(-40.0), -40.0);
}

// SumArray — ASSERTS (BUG 12)
TEST(CT7_FE_P2_SumArray, EmptySingleMultiple) {
    const int a0[] = {};                EXPECT_EQ(SumArray(a0, 0), 0);
    const int a1[] = {42};              EXPECT_EQ(SumArray(a1, 1), 42);
    const int a3[] = {1,2,3};           EXPECT_EQ(SumArray(a3, 3), 6);
}

// MinArray — ASSERT/THROW (BUG 13)
TEST(CT7_FE_P2_MinArray, FindsMinimum) {
    const int a[] = {5,2,7,-1,9};
    EXPECT_EQ(MinArray(a, 5), -1);
    const int b[] = {3,4,5};
    EXPECT_EQ(MinArray(b, 3), 3);
}
TEST(CT7_FE_P2_MinArray, EmptyArrayPolicy) {
    const int e[] = {};
    EXPECT_THROW(MinArray(e, 0), std::invalid_argument);
}

// MeanArray — ASSERT/THROW (BUG 14)
TEST(CT7_FE_P2_MeanArray, FractionalAverage) {
    const int a[] = {1,2};
    EXPECT_DOUBLE_EQ(MeanArray(a, 2), 1.5);
}
TEST(CT7_FE_P2_MeanArray, EmptyArrayPolicy) {
    const int e[] = {};
    EXPECT_THROW(MeanArray(e, 0), std::invalid_argument);
}

// GetAt — ASSERTS (BUG 15)
TEST(CT7_FE_P2_GetAt, InRange) {
    const int a[] = {10, 20, 30};
    EXPECT_EQ(GetAt(a, 3, 0), 10);
    EXPECT_EQ(GetAt(a, 3, 2), 30);
}
TEST(CT7_FE_P2_GetAt, OutOfRange) {
    const int a[] = {10, 20};
    EXPECT_EQ(GetAt(a, 2, -1), -1);
    EXPECT_EQ(GetAt(a, 2, 5), -1);            // should not touch OOB memory
}
TEST(CT7_FE_P2_GetAt, EmptyArray) {
    const int e[] = {};
    EXPECT_EQ(GetAt(e, 0, 0), -1);            // sentinel, no UB
}

// CopyArray — ASSERTS (BUG 16)
TEST(CT7_FE_P2_CopyArray, CopiesAllElements) {
    const int src[] = {7,8,9,10};
    int dst[4] = {0,0,0,0};
    ASSERT_EQ(CopyArray(src, dst, 4), 4);
    EXPECT_EQ(dst[0], 7);
    EXPECT_EQ(dst[1], 8);
    EXPECT_EQ(dst[2], 9);
    EXPECT_EQ(dst[3], 10);                     // detects n-1 copy bug
}

// StringJoin2 — ASSERTS (BUG 17)
TEST(CT7_FE_P2_StringJoin2, NoTrailingSeparator) {
    EXPECT_EQ(StringJoin2("a","b", ","), "a,b");
    EXPECT_EQ(StringJoin2("a", nullptr, ","), "a");
    EXPECT_EQ(StringJoin2(nullptr, "b", ","), "b");
    EXPECT_EQ(StringJoin2(nullptr, nullptr, ","), "");
}

// Accumulator — FIXTURE (BUGS 18–19)
class CT7_FE_P2_AccumulatorFixture : public ::testing::Test {
protected:
    void SetUp() override { acc.Reset(); }   // should clear to 0
    Accumulator acc;
};

TEST_F(CT7_FE_P2_AccumulatorFixture, StartsAtZero) {
    EXPECT_EQ(acc.value(), 0);               // detects Reset no-op (BUG 18)
}
TEST_F(CT7_FE_P2_AccumulatorFixture, AddAccumulates) {
    acc.Add(3); 
    acc.Add(7);
    EXPECT_EQ(acc.value(), 10);              // detects subtract bug (BUG 19)
}
TEST_F(CT7_FE_P2_AccumulatorFixture, ResetClears) {
    acc.Add(5);
    acc.Reset();
    EXPECT_EQ(acc.value(), 0);               // detects Reset still no-op (BUG 18)
}


/*
==========================
 Bug Notes (mylib_buggy_novector.hpp)
 Sequential, one bug at a time — ready to paste into a .cpp as comments
==========================
*/

// BUG 1 — Add(): subtracts instead of adds (around line ~12)
/*
Where: inline int Add(int a, int b) { return a - b; }
Why: Logic error; subtraction breaks basic arithmetic properties.
Fix:
    // inline int Add(int a, int b) { return a + b; }
*/

// BUG 2 — Divide(): returns 0 on divide-by-zero (around ~14–17)
/*
Where: if (b == 0) return 0;
Why: Silent error hides invalid input; callers expect an exception.
Fix:
    // if (b == 0) throw std::invalid_argument("division by zero");
    // return a / b;
*/

// BUG 3 — Factorial(): wrong loop & negative handling (~19–25)
/*
Where: if (n < 0) return 1;  for (int i = 1; i < n; ++i) r *= i;
Why: Negative factorial should fail; loop misses multiplying by n.
Fix:
    // if (n < 0) throw std::invalid_argument("negative factorial");
    // int r = 1; for (int i = 2; i <= n; ++i) r *= i;
*/

// BUG 4 — IsEven(): returns x%2 as bool (~27)
/*
Where: inline bool IsEven(int x) { return x % 2; }
Why: Even numbers yield 0 → false; odd yields 1 → true (inverted meaning).
Fix:
    // inline bool IsEven(int x) { return (x % 2) == 0; }
*/

// BUG 5 — InRangeExclusive(): inclusive instead of exclusive (~29–31)
/*
Where: return lo <= x && x <= hi;
Why: Function name says *exclusive*; boundaries must be excluded.
Fix:
    // return lo < x && x < hi;
*/

// BUG 6 — CrashIfNegative(): aborts on x <= 0 (~33–38)
/*
Where: if (x <= 0) { ... std::abort(); }
Why: Zero should not abort; spec is strictly negative.
Fix:
    // if (x < 0) { std::cerr << "negative input not allowed\n"; std::abort(); }
*/

// BUG 7 — Clamp(): swapped boundary logic (~40–44)
/*
Where: if (x < lo) return hi; if (x > hi) return lo;
Why: Below lo should clamp to lo; above hi to hi.
Fix:
    // if (x < lo) return lo;
    // if (x > hi) return hi;
    // return x;
*/

// BUG 8 — Power(): exp==0 returns 0; no negative policy (~46–52)
/*
Where: if (exp == 0) return 0;
Why: Any base^0 == 1; define policy for negative exponents.
Fix:
    // if (exp < 0) throw std::invalid_argument("negative exponent");
    // if (exp == 0) return 1;
    // long long r = 1; for (int i = 0; i < exp; ++i) r *= base; return r;
*/

// BUG 9 — GCD(): incorrect algorithm & zero handling (~54–64)
/*
Where: if (b == 0) return a + b; ... subtractive loop early-breaks.
Why: Wrong for (a,0), negative inputs, and many cases.
Fix (Euclidean algorithm):
    // inline int GCD(int a, int b) {
    //   if (a == 0 && b == 0) return 0;
    //   a = std::abs(a); b = std::abs(b);
    //   while (b) { int t = a % b; a = b; b = t; }
    //   return a;
    // }
*/

// BUG 10 — IsPrime(): n<=1 true; even numbers always true (~66–73)
/*
Where: if (n <= 1) return true;   if (n % 2 == 0) return n == 2 ? true : true;
Why: Primes are n >= 2; even numbers > 2 are not prime.
Fix:
    // inline bool IsPrime(int n) {
    //   if (n <= 1) return false;
    //   if (n % 2 == 0) return n == 2;
    //   for (int i = 3; i * i <= n; i += 2) if (n % i == 0) return false;
    //   return true;
    // }
*/

// BUG 11 — CelsiusToFahrenheit(): integer division 9/5 (~75–77)
/*
Where: return c * (9 / 5) + 32;
Why: 9/5 == 1 (integer), scale is wrong for all inputs.
Fix:
    // return c * (9.0 / 5.0) + 32.0;
*/

// BUG 12 — SumArray(): skips first element (~81–85)
/*
Where: for (int i = 1; i < n; ++i) s += arr[i];
Why: Index starts at 1; first element is ignored.
Fix:
    // int s = 0; for (int i = 0; i < n; ++i) s += arr[i]; return s;
*/

// BUG 13 — MinArray(): bad init & empty handling (~87–91)
/*
Where: if (n <= 0) return 0;  int m = 0;
Why: Returning 0 hides error; m=0 fails on positive-only arrays.
Fix:
    // if (n <= 0) throw std::invalid_argument("empty array");
    // int m = arr[0]; for (int i = 1; i < n; ++i) if (arr[i] < m) m = arr[i]; return m;
*/

// BUG 14 — MeanArray(): returns 0 on empty; truncates to int (~93–98)
/*
Where: if (n <= 0) return 0;  return static_cast<int>(s / n);
Why: Silent empty; integer truncation loses precision.
Fix:
    // if (n <= 0) throw std::invalid_argument("empty array");
    // long long s = 0; for (int i = 0; i < n; ++i) s += arr[i];
    // return static_cast<double>(s) / static_cast<double>(n);
*/

// BUG 15 — GetAt(): still touches OOB on invalid idx (~100–106)
/*
Where: if (idx<0||idx>=n) { (void)arr[n-1]; return -1; }
Why: Accessing arr[n-1] when n==0 is UB; should not read memory on OOB.
Fix:
    // if (idx < 0 || idx >= n) return -1;
    // return arr[idx];
*/

// BUG 16 — CopyArray(): copies only n-1 elements (~108–113)
/*
Where: for (int i = 0; i < n - 1; ++i) dst[i] = src[i];
Why: Last element never copied; destination incomplete.
Fix:
    // for (int i = 0; i < n; ++i) dst[i] = src[i];
*/

// BUG 17 — StringJoin2(): trailing separator (~115–121)
/*
Where: always appends sep at the end.
Why: Joins should place separators only *between* parts.
Fix:
    // std::string out;
    // if (a) out += a;
    // if (a && b && sep) out += sep;
    // if (b) out += b;
    // return out;
*/

// BUG 18 — Accumulator::Reset(): no-op (~126)
/*
Where: void Reset() { /* no-op *\/ }
Why: State is not cleared; tests expect reset to zero.
Fix:
    // void Reset() { value_ = 0; }
*/

// BUG 19 — Accumulator::Add(): subtracts instead of adds (~127)
/*
Where: void Add(int x) { value_ -= x; }
Why: Accumulation should increase the internal value.
Fix:
    // void Add(int x) { value_ += x; }
*/

// BUG 20 — API policy: missing error signaling on invalid inputs (various)
/*
Where: Divide, Factorial, MeanArray, MinArray, Power, GetAt...
Why: Silent returns (0/-1) hide failures and complicate debugging.
Fix idea:
    // Adopt a clear policy: throw std::invalid_argument on invalid inputs (e.g., divide-by-zero,
    // negative factorial, empty arrays, negative exponent) or document sentinel return values.
*/
