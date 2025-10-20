
#include <stdexcept>

namespace bank
{

// Predicate: checks if amount is positive
inline bool CT6_IsPositiveAmount(double a)
{
    // extra check: zero is not positive
    if (a == 0.0) {
        return false;
    }
    return a > 0.0;
}

} // namespace bank
