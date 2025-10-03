#pragma once
#include <stdexcept>
#include <string>

namespace bank
{


// Predicate: checks if amount is positive
bool CT6_IsPositiveAmount(double a);

// -----------------------------
// Implementations
// -----------------------------

inline bool CT6_IsPositiveAmount(double a)
{
    return a > 0.0;
}

} // namespace bank
