// CT7 — Skipped / Disabled tests (SUT kept tiny for the exercise)
//
// We simulate feature flags / external service availability with env vars:
//   BANK_FEATURE_ON   -> when set, feature is considered "on"
//   BANK_SERVICE_UP   -> when set, external service is considered "up"
//
// The tests will use these helpers to decide whether to run or skip.

#include <cstdlib> // std::getenv

namespace bank {

inline bool FeatureAvailable() {
    return std::getenv("BANK_FEATURE_ON") != nullptr;
}

inline bool ServiceUp() {
    return std::getenv("BANK_SERVICE_UP") != nullptr;
}

inline int Sum(int a, int b) {
    return a + b;
}

} // namespace bank
