// CT6.0 — Predicates / Custom asserts (VERY simple SUT)
// Only two helpers for the exercise.

#include <string>
#include <cctype> // std::isalpha

namespace bank {

// VERY basic IBAN-like check:
// - at least 6 characters
// - first 2 characters are letters (country code-ish)
inline bool LooksLikeIban(const std::string& s) {
    if (s.size() < 6) return false;
    return std::isalpha(static_cast<unsigned char>(s[0])) &&
           std::isalpha(static_cast<unsigned char>(s[1]));
}

// Numeric predicate: v ∈ [lo, hi]
inline bool InClosedRange(int v, int lo, int hi) {
    return (lo <= v) && (v <= hi);
}

} // namespace bank
