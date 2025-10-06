#include <gtest/gtest.h>
#include "../../src/Exercises/CT4_skip.cpp"  // agora usa CT4
#include <string>

using namespace bank;

// -----------------------------
// Function under test: CT4_IsPositiveAmount
// -----------------------------
TEST(CT4_IsPositiveAmountTests, TrueAndFalseCases)
{
    EXPECT_TRUE(CT4_IsPositiveAmount(10.0));
    EXPECT_FALSE(CT4_IsPositiveAmount(0.0));
    ASSERT_TRUE(CT4_IsPositiveAmount(0.01));
}

TEST(CT4_IsPositiveAmountTests, NegativeCase)
{
    EXPECT_FALSE(CT4_IsPositiveAmount(-0.01));
}

// Example skip test
TEST(CT4_IsPositiveAmountTests, SkipDemo)
{
    GTEST_SKIP() << "Skipping this test as a demo.";
    EXPECT_TRUE(CT4_IsPositiveAmount(123.0)); // not executed
}

// -----------------------------
// Function under test: CT4_deposit
// -----------------------------
TEST(CT4_DepositTests, IncreasesBalance)
{
    Account a{"Alice", 100.0};
    CT4_deposit(a, 50.0);
    EXPECT_EQ(a.balance, 150.0);
}

TEST(CT4_DepositTests, RejectsNonPositiveAmount)
{
    Account a{"Alice", 100.0};
    EXPECT_THROW(CT4_deposit(a, 0.0), std::invalid_argument);
    EXPECT_THROW(CT4_deposit(a, -5.0), std::invalid_argument);
}

// Skip test for deposit
TEST(CT4_DepositTests, SkipLargeDeposit)
{
    GTEST_SKIP() << "Feature for large deposits not implemented yet.";
    Account a{"Alice", 100.0};
    CT4_deposit(a, 1000000.0);
    EXPECT_EQ(a.balance, 1010100.0);
}

// -----------------------------
// Function under test: CT4_withdraw
// -----------------------------
TEST(CT4_WithdrawTests, DecreasesBalance)
{
    Account a{"Alice", 100.0};
    CT4_withdraw(a, 20.0);
    EXPECT_EQ(a.balance, 80.0);
}

TEST(CT4_WithdrawTests, RejectsNonPositiveAmount)
{
    Account a{"Alice", 100.0};
    EXPECT_THROW(CT4_withdraw(a, 0.0), std::invalid_argument);
}

TEST(CT4_WithdrawTests, RejectsInsufficientFunds)
{
    Account a{"Alice", 10.0};
    EXPECT_THROW(CT4_withdraw(a, 20.0), std::runtime_error);
}

// -----------------------------
// Function under test: CT4_transfer
// -----------------------------
TEST(CT4_TransferTests, MovesFundsBetweenAccounts)
{
    Account a{"Alice", 100.0};
    Account b{"Bob",   0.0};
    CT4_transfer(a, b, 40.0);
    EXPECT_EQ(a.balance, 60.0);
    EXPECT_EQ(b.balance, 40.0);
}

TEST(CT4_TransferTests, RejectsNonPositiveAmount)
{
    Account a{"Alice", 100.0};
    Account b{"Bob",   0.0};
    EXPECT_THROW(CT4_transfer(a, b, 0.0), std::invalid_argument);
    EXPECT_THROW(CT4_transfer(a, b, -1.0), std::invalid_argument);
    EXPECT_EQ(a.balance, 100.0);
    EXPECT_EQ(b.balance, 0.0);
}

TEST(CT4_TransferTests, RejectsInsufficientFundsAndKeepsDestUnchanged)
{
    Account a{"Alice", 30.0};
    Account b{"Bob",   10.0};
    EXPECT_THROW(CT4_transfer(a, b, 50.0), std::runtime_error);
    EXPECT_EQ(a.balance, 30.0);
    EXPECT_EQ(b.balance, 10.0);
}

// Skip test for transfer
TEST(CT4_TransferTests, SkipFutureCurrencyConversion)
{
    GTEST_SKIP() << "Skipping until currency conversion is supported.";
}

// -----------------------------
// Function under test: CT4_apply_simple_interest
// -----------------------------
TEST(CT4_InterestTests, ComputesSimpleInterestNear)
{
    double v = CT4_apply_simple_interest(100.0, 0.10, 36);
    EXPECT_NEAR(v, 100.9863, 1e-3);
}

TEST(CT4_InterestTests, InvalidArgumentsThrow)
{
    EXPECT_THROW(CT4_apply_simple_interest(-100.0, 0.1, 10), std::invalid_argument);
    EXPECT_THROW(CT4_apply_simple_interest(100.0, -0.1, 10), std::invalid_argument);
    EXPECT_THROW(CT4_apply_simple_interest(100.0, 1.5, 10), std::invalid_argument);
    EXPECT_THROW(CT4_apply_simple_interest(100.0, 0.1, -5), std::invalid_argument);
}

TEST(CT4_InterestTests, BoundaryValues)
{
    EXPECT_NEAR(CT4_apply_simple_interest(0.0,   0.10, 100), 0.0,   1e-12);
    EXPECT_NEAR(CT4_apply_simple_interest(100.0, 0.00, 365), 100.0, 1e-12);
    EXPECT_NEAR(CT4_apply_simple_interest(100.0, 1.00,   0), 100.0, 1e-12);
    EXPECT_NEAR(CT4_apply_simple_interest(100.0, 1.00, 365), 200.0, 1e-9);
}

// -----------------------------
// Type/struct-focused checks: Account (owner string)
// -----------------------------
TEST(CT4_AccountOwnerTests, CaseInsensitiveNameChecks)
{
    Account a{"ALICE", 0.0};
    EXPECT_STRCASEEQ(a.owner.c_str(), "alice");
    EXPECT_STRCASENE(a.owner.c_str(), "bob");
}

// Skip test for owner metadata
TEST(CT4_AccountOwnerTests, SkipMetadataNotImplemented)
{
    GTEST_SKIP() << "Skipping owner metadata feature (not implemented).";
}
