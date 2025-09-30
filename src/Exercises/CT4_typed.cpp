// CT4.0 — Typed Tests (SUT: System Under Test)
// ---------------------------------------------
// This file defines a tiny templated class: Ledger<TContainer>
// The goal is to have *one* piece of logic (a "ledger" of amounts)
// that can work with different STL containers (vector, deque, list).
//
// Why template?
//   So we can verify the same behavior across multiple container types
//   without duplicating production code — perfect for GoogleTest "Typed Tests".
//
// We keep this in a .cpp on purpose (for exercise simplicity). The test file
// will #include this .cpp directly. In real projects you would use a header.

#include <numeric>       // std::accumulate
#include <type_traits>   // std::is_convertible_v

namespace bank {

// Ledger<TContainer>
// ------------------
// TContainer is expected to be a sequential container whose value_type
// can be converted to double (e.g., vector<double>, deque<double>, list<double>).
//
// Minimal API for the exercise:
//   - Add(value)      : append an amount
//   - Total() -> double : sum of all amounts
//   - Size() -> size_t  : number of entries
//   - Clear()          : remove all entries
//
// NOTE: We keep it intentionally small to focus on the *typed tests* concept.
template <class TContainer>
class Ledger {
public:
    using container_type = TContainer;
    using value_type     = typename TContainer::value_type;

    // Compile-time guard: ensure container's value_type behaves like a number
    static_assert(std::is_convertible_v<value_type, double>,
                  "Ledger<T>: value_type must be convertible to double");

    // Add an amount to the ledger
    void Add(value_type v) { items_.push_back(v); }

    // Sum all amounts and return as double
    double Total() const {
        // Start from 0.0 (double) so accumulation is done in double precision
        return std::accumulate(items_.begin(), items_.end(), 0.0);
    }

    // Number of stored entries
    std::size_t Size() const { return items_.size(); }

    // Remove all entries
    void Clear() { items_.clear(); }

private:
    container_type items_{};  // underlying storage (type chosen by tests)
};

} // namespace bank
