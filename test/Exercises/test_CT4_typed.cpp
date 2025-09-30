// CT4.0 — Typed Tests with GoogleTest
// -----------------------------------
// Goal:
//   Test the SAME behavior across MULTIPLE types using ONE test body.
//   Here we verify a templated Ledger<TContainer> with:
//     - std::vector<double>
//     - std::deque<double>
//     - std::list<double>
//
// How Typed Tests work (3 steps):
//   1) Create a *templated* test fixture:
//        template <typename T> class MyFixture : public ::testing::Test { ... };
//      - T is the TYPE parameter (here: the container type).
//   2) Register a list of concrete TYPES with TYPED_TEST_SUITE(...).
//   3) Write tests using TYPED_TEST(MyFixture, TestName).
//      - Inside those tests, you can refer to the current type as `TypeParam`
//        or use `this->` to access members declared in the fixture.
//
// Why is this useful?
//   - You avoid duplicating test logic for each type.
//   - You make sure your template behaves consistently across supported types.
//
// Note: For exercise simplicity, we #include the SUT .cpp directly.
//       In production, prefer headers + link a compiled library.

#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include <list>

// Include SUT (templated Ledger) — adjust relative path to match your repo layout
#include "../../src/Exercises/CT4_typed.cpp"

// 1) Define a templated fixture.
//    The template parameter here is the CONTAINER TYPE (e.g., std::vector<double>).
//    Our fixture doesn't need custom SetUp/TearDown; it simply holds a Ledger<T>.
template <typename TContainer>
class LedgerTypedTest : public ::testing::Test {
protected:
    using LedgerT = bank::Ledger<TContainer>;  // shorthand for readability
    LedgerT ledger;                            // fresh instance for each test (as usual with fixtures)
};

// 2) Declare which concrete TYPES we want to test.
//    All three have value_type = double and support push_back/iteration.
using MyContainerTypes = ::testing::Types<
    std::vector<double>,
    std::deque<double>,
    std::list<double>
>;

// Bind (register) those types to the typed fixture above.
// GoogleTest will create an internal suite for each type and run all TYPED_TESTs.
TYPED_TEST_SUITE(LedgerTypedTest, MyContainerTypes);

// 3) Write typed tests — they will run once per registered TYPE.
//    Inside a TYPED_TEST, `TypeParam` refers to the current container type.
//    We usually just use `this->ledger` (a Ledger<TypeParam>) and assert its behavior.

// Test A: Adding entries updates Size() and Total() consistently across types.
TYPED_TEST(LedgerTypedTest, AddUpdatesSizeAndTotal) {
    this->ledger.Add(10.0);     // container-specific push_back is called via Ledger
    this->ledger.Add(2.5);
    EXPECT_EQ(this->ledger.Size(), 2u);       // size_t comparison: use 2u literal
    EXPECT_DOUBLE_EQ(this->ledger.Total(), 12.5);
}

// Test B: Clear() resets both Size() and Total() regardless of container type.
TYPED_TEST(LedgerTypedTest, ClearResetsState) {
    this->ledger.Add(5.0);
    this->ledger.Add(-5.0);
    ASSERT_EQ(this->ledger.Size(), 2u);       // precondition: two entries present
    this->ledger.Clear();
    EXPECT_EQ(this->ledger.Size(), 0u);
    EXPECT_DOUBLE_EQ(this->ledger.Total(), 0.0);
}

// Test C: Zeros and negatives are handled consistently (sum is correct).
TYPED_TEST(LedgerTypedTest, SupportsZerosAndNegatives) {
    this->ledger.Add(0.0);
    this->ledger.Add(-3.0);
    this->ledger.Add(7.0);
    EXPECT_EQ(this->ledger.Size(), 3u);
    EXPECT_DOUBLE_EQ(this->ledger.Total(), 4.0);  // 0 - 3 + 7
}

// --------------------------
