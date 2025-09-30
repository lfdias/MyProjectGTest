// CT7 — Skipped / Disabled tests with GoogleTest
// -----------------------------------------------
// • Skipped tests (runtime): use GTEST_SKIP() to *dynamically* skip a test or an entire
//   fixture (e.g., feature turned off, external dependency down).
// • Disabled tests (compile-time opt-out): name the test or the suite with the "DISABLED_"
//   prefix so it won't run by default (useful for flaky or known-bad tests).
//
// This file demonstrates both approaches.
// We #include the source .cpp directly (exercise style; no headers).

#include <gtest/gtest.h>
#include "../../src/Exercises/CT7_skip.cpp"

// 1) RUNTIME SKIP inside a *test body* using GTEST_SKIP().
//    If BANK_FEATURE_ON is not set, we skip; otherwise we run normal assertions.
TEST(CT7_Skip, FeatureGate_SkipsWhenFeatureOff) {
    if (!bank::FeatureAvailable()) {
        GTEST_SKIP() << "Skipping: feature is OFF (set BANK_FEATURE_ON to enable).";
    }
    // Only runs when feature is ON:
    EXPECT_EQ(bank::Sum(2, 3), 5);
}

// 2) RUNTIME SKIP in a *fixture SetUp()* to skip a whole suite when a dependency is down.
class ServiceFixture : public ::testing::Test {
protected:
    void SetUp() override {
        if (!bank::ServiceUp()) {
            GTEST_SKIP() << "Skipping suite: service is DOWN (set BANK_SERVICE_UP to run).";
        }
    }
};

TEST_F(ServiceFixture, UsesServicePath_1) {
    // Reaches here only if SetUp() didn't skip
    EXPECT_TRUE(bank::ServiceUp());
    EXPECT_EQ(bank::Sum(1, 1), 2);
}

TEST_F(ServiceFixture, UsesServicePath_2) {
    EXPECT_TRUE(bank::ServiceUp());
    EXPECT_EQ(bank::Sum(10, 5), 15);
}

// 3) DISABLED test (compile-time opt-out):
//    Prefix the test name (or suite name) with DISABLED_. It won't run unless you pass
//    --gtest_also_run_disabled_tests or filter it explicitly.
//
//    This example is intentionally wrong (2+2 != 5) to show how disabling helps
//    when you want to keep a known-bad/flaky test in the tree without breaking CI.
TEST(CT7_Disabled, DISABLED_KnownBug_SumIsNotFive) {
    EXPECT_EQ(bank::Sum(2, 2), 5); // WRONG on purpose; runs only when explicitly enabled
}

// Notes:
// • To *see* disabled tests run, use:
//       ./run_ct7_skip_disable --gtest_also_run_disabled_tests
//   or filter explicitly, e.g.:
//       ./run_ct7_skip_disable --gtest_filter="*DISABLED_*"
// • Skips appear as "SKIPPED" in output; failures do not occur for skipped tests.
