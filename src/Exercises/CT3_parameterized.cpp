// CT3 — SUT (System Under Test): tiny, headerless "bank" helpers
// We keep these in a .cpp on purpose so the test can #include it directly.
//
// What we test here:
//  - MonthlyFeeFor(balance): piecewise function returning a monthly fee
//  - ApplyMonthlyInterest(balance, rate): adds simple monthly interest
//
// Both functions are intentionally simple so the focus is on HOW parameterized
// tests work, not on business complexity.

#include <stdexcept>

namespace bank {

// Returns a monthly fee based on balance (toy example).
// Throws if balance is negative (invalid input).
inline double MonthlyFeeFor(double balance) {
    if (balance < 0) throw std::invalid_argument("negative balance");
    if (balance < 1000) return 5.0;
    if (balance < 5000) return 2.5;
    return 0.0;
}

// Applies simple monthly interest and returns the new balance.
// Throws if monthlyRate is negative (invalid input).
inline double ApplyMonthlyInterest(double balance, double monthlyRate) {
    if (monthlyRate < 0) throw std::invalid_argument("rate < 0");
    return balance + balance * monthlyRate;
}

} // namespace bank
