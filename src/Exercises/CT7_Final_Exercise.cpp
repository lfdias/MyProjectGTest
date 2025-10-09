#pragma once
#include <vector>
#include <stdexcept>
#include <cstdlib>   // std::abort
#include <iostream>  // std::cerr

namespace mylib {

// Simple add
inline int Add(int a, int b) { return a + b; }

// Divide and throw on zero
inline int Divide(int a, int b) {
    if (b == 0) throw std::invalid_argument("division by zero");
    return a / b;
}

// Factorial (n >= 0). Throws if n < 0.
inline int Factorial(int n) {
    if (n < 0) throw std::invalid_argument("negative factorial");
    int r = 1;
    for (int i = 2; i <= n; ++i) r *= i;
    return r;
}

// Parity
inline bool IsEven(int x) { return (x % 2) == 0; }

// Sum a vector
inline int Sum(const std::vector<int>& v) {
    int s = 0; for (int x : v) s += x; return s;
}

// Predicate for EXPECT_PRED3 / ASSERT_PRED3
inline bool IsStrictlyBetween(int x, int low, int high) {
    return low < x && x < high;
}

// Death-test function: aborts if x < 0
inline void CrashIfNegative(int x) {
    if (x < 0) {
        std::cerr << "negative input not allowed" << std::endl;
        // LCOV_EXCL_START
        std::abort();
        // LCOV_EXCL_STOP
    }
}

// Simple class for fixtures
class Accumulator {
public:
    void Reset() { value_ = 0; }
    void Add(int x) { value_ += x; }
    int value() const { return value_; }
private:
    int value_ = 0;
};

} // namespace mylib
