// CT3 — Parameterized Tests with GoogleTest
//
// ❓ What is a parameterized test?
//    It's a way to write the *same test logic once* and run it automatically
//    over many inputs. Great for table-driven tests.
//
// 🧠 Core building blocks:
//  1) A fixture type that *inherits* from ::testing::TestWithParam<T>
//     - T is the type of "a single parameter set" you want to feed the test.
//       Examples: double, std::tuple<int,double>, a custom struct, etc.
//  2) A test body written with TEST_P (P = Parameterized), where you read the
//     current parameters via GetParam().
//  3) An instantiation with INSTANTIATE_TEST_SUITE_P(...), where you provide
//     the concrete parameter values (e.g., ::testing::Values(...)).
//
// 🧾 In this file we show two suites:
//   A) FeeParamTest
//      - Type: std::tuple<double,double>  (balance, expectedFee)
//      - We feed a table of pairs and check MonthlyFeeFor(balance) == expectedFee.
//   B) InterestInvalidParamTest
//      - Type: double  (monthlyRate)
//      - We feed some invalid (negative) rates and assert that it throws.
//
// 🔧 Why a fixture at all?
//     Even if you don't need SetUp/TearDown, TestWithParam<T> gives you the
//     plumbing for GetParam(). If you *do* need SetUp/TearDown, just override
//     them like in normal fixtures.
//
// 📁 No headers here: the test directly #includes the SUT .cpp for simplicity.
//     In a real project, prefer headers + link a library.

#include <gtest/gtest.h>
#include <tuple>      // std::tuple
#include <string>     // for nice comments / examples
#include "../../src/Exercises/CT3_parameterized.cpp"  // adjust if your tree differs

// -----------------------------------------------------------------------------
// Suite A: Fee table (balance -> expected fee)
// -----------------------------------------------------------------------------
//
// 1) Define a fixture type. We don't need extra state, so the class is empty.
//    We inherit from TestWithParam<std::tuple<double,double>> because each test
//    instance will receive **one pair**: (balance, expectedFee).
class FeeParamTest : public ::testing::TestWithParam<std::tuple<double, double>> {};

// 2) Write the test body with TEST_P (Parameterized). Inside, call GetParam() to
//    retrieve this instance's parameters. Here we use structured bindings.
TEST_P(FeeParamTest, ReturnsExpectedFee) {
    const auto [balance, expectedFee] = GetParam();  // GetParam() gives the tuple
    // EXPECT_DOUBLE_EQ is good for exact doubles that come from simple literals.
    // If your calculation has rounding/FP error, use EXPECT_NEAR instead.
    EXPECT_DOUBLE_EQ(bank::MonthlyFeeFor(balance), expectedFee);
}

// 3) Instantiate the suite with a *name*, the fixture type, and a generator of
//    parameter values. ::testing::Values(...) expands into N independent test
//    instances — one per tuple below.
//    The "FeeTable" string becomes part of the test names in the output.
INSTANTIATE_TEST_SUITE_P(
    FeeTable,                      // Instance name (prefix in test output)
    FeeParamTest,                  // Which test suite to instantiate
    ::testing::Values(             // Concrete parameter sets
        std::make_tuple(     0.0,  5.0),
        std::make_tuple(   999.99, 5.0),
        std::make_tuple(  1000.0,  2.5),
        std::make_tuple(  4999.99, 2.5),
        std::make_tuple(  5000.0,  0.0),
        std::make_tuple( 12000.0,  0.0)
    )
);
// Resulting test names look like:
//   FeeTable/ReturnsExpectedFee/0, FeeTable/ReturnsExpectedFee/1, ...

// 💡 Tips for real code:
// - If parameters are in a container, use ::testing::ValuesIn(container).
// - For multiple independent dimensions, use std::tuple or ::testing::Combine.
// - To customize how parameter values appear in test names, provide a
//   name generator (see gtest docs for custom parameter name functions).

// -----------------------------------------------------------------------------
// Suite B: Invalid interest rates should throw
// -----------------------------------------------------------------------------
//
// Here each parameter is just a double (the monthlyRate). We want all *negative*
// values to trigger an exception. So we feed a small list of negatives and write
// a single TEST_P that checks EXPECT_THROW for each.
class InterestInvalidParamTest : public ::testing::TestWithParam<double> {};

TEST_P(InterestInvalidParamTest, NegativeRateThrows) {
    const double badRate = GetParam();  // Each instance gets one rate
    EXPECT_THROW(bank::ApplyMonthlyInterest(100.0, badRate), std::invalid_argument);
}

// Instantiate with a few negative values.
// Each value below becomes its *own* test instance.
INSTANTIATE_TEST_SUITE_P(
    BadRates,                      // Instance name (prefix in test output)
    InterestInvalidParamTest,      // Which test suite to instantiate
    ::testing::Values(-0.0001, -0.01, -1.0)
);

// -----------------------------------------------------------------------------
// (Optional) Quick reference:
//
//  - TEST_P(SuiteName, TestName)      : Defines a parameterized test body.
//  - INSTANTIATE_TEST_SUITE_P(Name, SuiteName, Generator)
//                                     : Binds concrete params to that body.
//  - TestWithParam<T>                 : Base providing GetParam() of type T.
//  - GetParam()                       : Returns the params for *this* instance.
//  - ::testing::Values(a,b,c,...)     : Inline list of parameters.
//  - ::testing::ValuesIn(vec)         : Use an existing container of params.
//  - ::testing::Combine(a,b,...)      : Cartesian product for tuples.
// -----------------------------------------------------------------------------
