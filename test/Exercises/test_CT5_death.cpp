#include <gtest/gtest.h>
#include "../../src/Exercises/CT5_death.cpp"

using namespace bank;



// -----------------------------
// Tests for CT5_Deposit
// -----------------------------

// Deposit must fail (abort) if amount is zero or negative
TEST(CT5_Deposit, DeathOnZeroOrNegative) {
    Account a{100.0};
    ASSERT_DEATH(CT5_Deposit(a, 0.0), "deposit amount <= 0");
    ASSERT_DEATH(CT5_Deposit(a, -1.0), "deposit amount <= 0");
}

// Deposit must succeed if amount is positive
TEST(CT5_Deposit, Success) {
    Account a{0.0};
    CT5_Deposit(a, 50.0);
    EXPECT_DOUBLE_EQ(a.balance, 50.0);
}

// -----------------------------
// Tests for CT5_Withdraw
// -----------------------------

// Withdraw must fail (abort) if amount is zero or negative
TEST(CT5_Withdraw, DeathOnZeroOrNegative) {
    Account a{100.0};
    ASSERT_DEATH(CT5_Withdraw(a, 0.0), "withdraw amount <= 0");
    ASSERT_DEATH(CT5_Withdraw(a, -1.0), "withdraw amount <= 0");
}

// Withdraw must fail (abort) if amount is greater than balance
TEST(CT5_Withdraw, DeathOnInsufficientFunds) {
    Account a{50.0};
    ASSERT_DEATH(CT5_Withdraw(a, 60.0), "insufficient funds");
}

// Withdraw must succeed if amount is valid
TEST(CT5_Withdraw, Success) {
    Account a{100.0};
    CT5_Withdraw(a, 40.0);
    EXPECT_DOUBLE_EQ(a.balance, 60.0);
}
