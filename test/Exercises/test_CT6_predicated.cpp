// CT6.0 — Predicates / Custom asserts (TESTS)
// We show:
// 1) EXPECT_TRUE (least expressive)
// 2) Custom assertion with ::testing::AssertionResult (rich message)
// 3) EXPECT_PRED3 for readable multi-argument predicates

#include <gtest/gtest.h>
#include <string>
#include "../../src/Exercises/CT6_predicated.cpp"

// (2) Custom assertion wrapper: returns AssertionSuccess/Failure with details.
// Use when you want a clear, domain-friendly failure message.
static ::testing::AssertionResult LooksLikeIbanWithMsg(const std::string& s) {
    if (s.size() < 6) {
        return ::testing::AssertionFailure()
               << "IBAN too short: len=" << s.size() << " (need >= 6). Value='" << s << "'";
    }
    if (!std::isalpha(static_cast<unsigned char>(s[0])) ||
        !std::isalpha(static_cast<unsigned char>(s[1]))) {
        return ::testing::AssertionFailure()
               << "First two characters must be letters. Got '"
               << (s.size() >= 2 ? s.substr(0,2) : s) << "'";
    }
    return ::testing::AssertionSuccess();
}

// 1) Plain boolean check — works, but failure message is generic.
TEST(CT6_Simple, PlainBool) {
    EXPECT_TRUE(bank::LooksLikeIban("PT1234"));  // passes
}

// 2) Custom assertion — same check, but would print a clear "why" if it failed.
TEST(CT6_Simple, CustomAssertion_WithMessage) {
    EXPECT_TRUE(LooksLikeIbanWithMsg("PT1234")); // passes; richer diagnostics on failure
}

// 3) Predicate macro — readable for multi-argument relations.
TEST(CT6_Simple, PredicateMacro_RANGE) {
    EXPECT_PRED3(bank::InClosedRange, /*v=*/5, /*lo=*/0, /*hi=*/10);
    EXPECT_PRED3(bank::InClosedRange, 0, 0, 10);   // lower bound
    EXPECT_PRED3(bank::InClosedRange, 10, 0, 10);  // upper bound
}
