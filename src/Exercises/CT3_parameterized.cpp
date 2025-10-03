// CT3 — SUT (System Under Test): slightly more complex bank fee helper
//
// What we test here:
//  - CT3_MonthlyFee(balance, isStudent)
//
// Rules (toy example):
//   • Negative balance → sentinel 9999.0 (invalid input).
//   • Students:
//        - balance < 1000   → 2.5
//        - balance < 5000   → 1.0
//        - balance >= 5000  → 0.0
//   • Non-students:
//        - balance < 1000   → 5.0
//        - balance < 5000   → 2.5
//        - balance >= 5000  → 0.0

#include <stdexcept>

namespace bank {

inline double CT3_MonthlyFee(double balance, bool isStudent) {
    if (balance < 0.0) {
        return 9999.0; // sentinel for invalid input
    }

    if (isStudent) {
        if (balance < 1000)  return 2.5;
        if (balance < 5000)  return 1.0;
        return 0.0;
    } else {
        if (balance < 1000)  return 5.0;
        if (balance < 5000)  return 2.5;
        return 0.0;
    }
}

} // namespace bank