#include <gtest/gtest.h>
#include <string>


#include "../../src/Exercises/CT1_asserts.cpp" 

using bank::BankAccount;

// 1) ASSERT_TRUE — FATAL: stops this test on failure
TEST(Bank, IbanLooksValid_ASSERT_TRUE) {
    ASSERT_TRUE(BankAccount::IsValidIbanBasic("PT5000020123123456789"));
    BankAccount a("Alice", 1000.0); // only runs if ASSERT above passes
    EXPECT_EQ(a.Balance(), 1000.0);
}

// 2) EXPECT_TRUE — non-fatal
// 3) EXPECT_FALSE — non-fatal
TEST(Bank, OwnerPresent_EXPECT_TRUE_FALSE) {
    BankAccount a("Bob", 250.0);
    EXPECT_TRUE(!a.Owner().empty());   // 2) EXPECT_TRUE
    EXPECT_FALSE(a.Owner() == "");     // 3) EXPECT_FALSE
}

// 4) EXPECT_EQ — equality
// 5) EXPECT_NE — inequality
TEST(Bank, EqualityBasics_EXPECT_EQ_NE) {
    BankAccount a("Carol", 300.0);
    EXPECT_EQ(a.Balance(), 300.0);             // 4)
    EXPECT_NE(a.Owner(), std::string("Dan"));  // 5)
}

// 6) EXPECT_LT — <
// 7) EXPECT_LE — <=
// 8) EXPECT_GT — >
// 9) EXPECT_GE — >=
TEST(Bank, Fees_EXPECT_LT_LE_GT_GE) {
    EXPECT_LT(BankAccount::MonthlyFeeFor(1000.0), 5.0);   // 6)
    EXPECT_LE(BankAccount::MonthlyFeeFor(1000.0), 2.5);   // 7)
    EXPECT_GT(BankAccount::MonthlyFeeFor(6000.0), -0.1);  // 8)
    EXPECT_GE(BankAccount::MonthlyFeeFor(6000.0), 0.0);   // 9)
}

// 10) EXPECT_THROW — throws a specific exception type
TEST(Bank, WithdrawTooMuch_EXPECT_THROW) {
    BankAccount a("Eve", 100.0);
    EXPECT_THROW(a.Withdraw(200.0), std::invalid_argument); // 10)
}

// 11) EXPECT_NO_THROW — should not throw
TEST(Bank, DepositOk_EXPECT_NO_THROW) {
    BankAccount a("Fay", 100.0);
    EXPECT_NO_THROW(a.Deposit(50.0)); // 11)
    EXPECT_EQ(a.Balance(), 150.0);
}

// 12) EXPECT_ANY_THROW — throws anything
TEST(Bank, BadDeposit_EXPECT_ANY_THROW) {
    BankAccount a("Gus", 10.0);
    EXPECT_ANY_THROW(a.Deposit(0)); // 12)
}

// 13) EXPECT_NEAR — doubles with absolute tolerance
TEST(Bank, Interest_EXPECT_NEAR) {
    BankAccount a("Hana", 1000.0);
    double after = a.ApplyMonthlyInterest(0.0125); // +1.25% = 1012.5
    EXPECT_NEAR(after, 1012.5, 1e-9); // 13)
}

// 14) EXPECT_FLOAT_EQ — ULP-aware comparison for float
TEST(Bank, Half_EXPECT_FLOAT_EQ) {
    float h = BankAccount::Half(1.0f);
    EXPECT_FLOAT_EQ(h, 0.5f); // 14)
}

// 15) ASSERT_EQ — FATAL; useful as a precondition within the test
TEST(Bank, WithdrawSequence_ASSERT_EQ) {
    BankAccount a("Ivy", 200.0);
    ASSERT_EQ(a.Balance(), 200.0); // 15) ensures precondition before proceeding
    a.Withdraw(50.0);
    EXPECT_EQ(a.Balance(), 150.0);
}
