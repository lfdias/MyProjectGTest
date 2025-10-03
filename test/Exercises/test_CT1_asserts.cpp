#include <gtest/gtest.h>
#include "../../src/Exercises/CT1_asserts.cpp"  // include the single combined file
#include <string>

using namespace bank;

// -----------------------------
// Function under test: CT1_IsPositiveAmount
// -----------------------------
TEST(CT1_IsPositiveAmountTests, TrueAndFalseCases)
{
    EXPECT_TRUE(CT1_IsPositiveAmount(10.0));
    EXPECT_FALSE(CT1_IsPositiveAmount(0.0));
    ASSERT_TRUE(CT1_IsPositiveAmount(0.01));
}

TEST(CT1_IsPositiveAmountTests, NegativeCase)
{
    EXPECT_FALSE(CT1_IsPositiveAmount(-0.01));
}

// -----------------------------
// Function under test: CT1_deposit
// -----------------------------
TEST(CT1_DepositTests, IncreasesBalance)
{
    Account a{"Alice", 100.0};
    CT1_deposit(a, 50.0);
    EXPECT_EQ(a.balance, 150.0);
}

TEST(CT1_DepositTests, RejectsNonPositiveAmount)
{
    Account a{"Alice", 100.0};
    EXPECT_THROW(CT1_deposit(a, 0.0), std::invalid_argument);
    EXPECT_THROW(CT1_deposit(a, -5.0), std::invalid_argument);
}

// -----------------------------
// Function under test: CT1_withdraw
// -----------------------------
TEST(CT1_WithdrawTests, DecreasesBalance)
{
    Account a{"Alice", 100.0};
    CT1_withdraw(a, 20.0);
    EXPECT_EQ(a.balance, 80.0);
}

TEST(CT1_WithdrawTests, RejectsNonPositiveAmount)
{
    Account a{"Alice", 100.0};
    EXPECT_THROW(CT1_withdraw(a, 0.0), std::invalid_argument);
}

TEST(CT1_WithdrawTests, RejectsInsufficientFunds)
{
    Account a{"Alice", 10.0};
    EXPECT_THROW(CT1_withdraw(a, 20.0), std::runtime_error);
}

// -----------------------------
// Function under test: CT1_transfer
// -----------------------------
TEST(CT1_TransferTests, MovesFundsBetweenAccounts)
{
    Account a{"Alice", 100.0};
    Account b{"Bob",   0.0};
    CT1_transfer(a, b, 40.0);
    EXPECT_EQ(a.balance, 60.0);
    EXPECT_EQ(b.balance, 40.0);
}

TEST(CT1_TransferTests, RejectsNonPositiveAmount)
{
    Account a{"Alice", 100.0};
    Account b{"Bob",   0.0};
    EXPECT_THROW(CT1_transfer(a, b, 0.0), std::invalid_argument);
    EXPECT_THROW(CT1_transfer(a, b, -1.0), std::invalid_argument);
    EXPECT_EQ(a.balance, 100.0);
    EXPECT_EQ(b.balance, 0.0);
}

TEST(CT1_TransferTests, RejectsInsufficientFundsAndKeepsDestUnchanged)
{
    Account a{"Alice", 30.0};
    Account b{"Bob",   10.0};
    EXPECT_THROW(CT1_transfer(a, b, 50.0), std::runtime_error);
    EXPECT_EQ(a.balance, 30.0);
    EXPECT_EQ(b.balance, 10.0);
}

// -----------------------------
// Function under test: CT1_apply_simple_interest
// -----------------------------
TEST(CT1_InterestTests, ComputesSimpleInterestNear)
{
    double v = CT1_apply_simple_interest(100.0, 0.10, 36);
    EXPECT_NEAR(v, 100.9863, 1e-3);
}

TEST(CT1_InterestTests, InvalidArgumentsThrow)
{
    EXPECT_THROW(CT1_apply_simple_interest(-100.0, 0.1, 10), std::invalid_argument);
    EXPECT_THROW(CT1_apply_simple_interest(100.0, -0.1, 10), std::invalid_argument);
    EXPECT_THROW(CT1_apply_simple_interest(100.0, 1.5, 10), std::invalid_argument);
    EXPECT_THROW(CT1_apply_simple_interest(100.0, 0.1, -5), std::invalid_argument);
}

TEST(CT1_InterestTests, BoundaryValues)
{
    EXPECT_NEAR(CT1_apply_simple_interest(0.0,   0.10, 100), 0.0,   1e-12);
    EXPECT_NEAR(CT1_apply_simple_interest(100.0, 0.00, 365), 100.0, 1e-12);
    EXPECT_NEAR(CT1_apply_simple_interest(100.0, 1.00,   0), 100.0, 1e-12);
    EXPECT_NEAR(CT1_apply_simple_interest(100.0, 1.00, 365), 200.0, 1e-9);
}

// -----------------------------
// Type/struct-focused checks: Account (owner string)
// -----------------------------
TEST(CT1_AccountOwnerTests, CaseInsensitiveNameChecks)
{
    Account a{"ALICE", 0.0};
    EXPECT_STRCASEEQ(a.owner.c_str(), "alice");
    EXPECT_STRCASENE(a.owner.c_str(), "bob");
}
