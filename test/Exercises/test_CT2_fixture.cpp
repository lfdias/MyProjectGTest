// Exercise 2 — Test Fixture with GoogleTest (TEST_F)
//
// What is a Test Fixture?
// - A reusable test environment: common setup (objects/state) is prepared
//   automatically BEFORE each test and cleaned up AFTER each test.
//
// How it works:
// 1) Create a class that inherits from ::testing::Test.
// 2) Inside this class, define:
//      - SetUp()    -> runs before EACH test (prepare common state)
//      - TearDown() -> runs after EACH test (clean resources)
//      - Shared member variables for all tests to use
// 3) Write tests with TEST_F (F = uses the Fixture).
//
// For simplicity (no header), we include the SUT .cpp directly.
// Adjust the relative path if your repo layout differs.
#include <gtest/gtest.h>
#include "../../src/Exercises/CT2_fixture.cpp"  // SUT included directly

// 1) Define the FIXTURE: inherit from ::testing::Test
class BankAccountFixture : public ::testing::Test {
protected:
    // Shared member (re-created for every test via SetUp)
    bank::BankAccount* acc = nullptr;

    // 2) SetUp(): runs BEFORE each test -> provides a fresh, predictable state
    void SetUp() override {
        acc = new bank::BankAccount("Alice", 100.0);
    }

    //    TearDown(): runs AFTER each test -> clean up anything allocated in SetUp
    void TearDown() override {
        delete acc;
        acc = nullptr;
    }
};

// 3) Tests use TEST_F (they automatically get the SetUp/TearDown behavior)

// Test 1: Deposit increases the balance
TEST_F(BankAccountFixture, DepositIncreasesBalance) {
    acc->Deposit(50.0);
    EXPECT_EQ(acc->Balance(), 150.0);
}

// Test 2: Withdraw decreases the balance
TEST_F(BankAccountFixture, WithdrawDecreasesBalance) {
    acc->Withdraw(40.0);
    EXPECT_EQ(acc->Balance(), 60.0);
}

// Test 3: Each test starts from a fresh state (isolation)
// The deposit/withdraw in previous tests DOES NOT affect this one.
TEST_F(BankAccountFixture, EachTestStartsFreshState) {
    EXPECT_EQ(acc->Balance(), 100.0);
}

// Test 4: Business rule/guard example (expected error)
TEST_F(BankAccountFixture, WithdrawMoreThanBalanceThrows) {
    EXPECT_THROW(acc->Withdraw(1000.0), std::invalid_argument);
}
