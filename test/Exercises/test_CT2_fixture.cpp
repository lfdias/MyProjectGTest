#include <gtest/gtest.h>
#include "../../src/Exercises/CT2_fixture.cpp"  // include the combined file
#include <string>

using namespace bank;

// ----------------------------------------
// Fixture: allocate in SetUp, free in TearDown
// ----------------------------------------
class CT2_BankingFixture : public ::testing::Test
{
protected:
    Account* alice;
    Account* bob;

    void SetUp() override
    {
        // match common initial states
        alice = new Account{"Alice", 100.0};
        bob   = new Account{"Bob",     0.0};
    }

    void TearDown() override
    {
        delete alice;
        delete bob;
    }
};

// =====================================================
// Function under test: CT2_IsPositiveAmount
// =====================================================
TEST_F(CT2_BankingFixture, CT2_IsPositiveAmount_TrueAndFalseCases)
{
    EXPECT_TRUE(CT2_IsPositiveAmount(10.0));
    EXPECT_FALSE(CT2_IsPositiveAmount(0.0));
    ASSERT_TRUE(CT2_IsPositiveAmount(0.01));
}

TEST_F(CT2_BankingFixture, CT2_IsPositiveAmount_NegativeCase)
{
    EXPECT_FALSE(CT2_IsPositiveAmount(-0.01));
}

// =====================================================
// Function under test: CT2_deposit
// =====================================================
TEST_F(CT2_BankingFixture, CT2_deposit_IncreasesBalance)
{
    CT2_deposit(*alice, 50.0);
    EXPECT_EQ(alice->balance, 150.0);
}

TEST_F(CT2_BankingFixture, CT2_deposit_RejectsNonPositiveAmount)
{
    EXPECT_THROW(CT2_deposit(*alice, 0.0), std::invalid_argument);
    EXPECT_THROW(CT2_deposit(*alice, -5.0), std::invalid_argument);
}

// =====================================================
// Function under test: CT2_withdraw
// =====================================================
TEST_F(CT2_BankingFixture, CT2_withdraw_DecreasesBalance)
{
    CT2_withdraw(*alice, 20.0);
    EXPECT_EQ(alice->balance, 80.0);
}

TEST_F(CT2_BankingFixture, CT2_withdraw_RejectsNonPositiveAmount)
{
    EXPECT_THROW(CT2_withdraw(*alice, 0.0), std::invalid_argument);
    EXPECT_THROW(CT2_withdraw(*alice, -1.0), std::invalid_argument);
}

TEST_F(CT2_BankingFixture, CT2_withdraw_RejectsInsufficientFunds)
{
    EXPECT_THROW(CT2_withdraw(*alice, 120.0), std::runtime_error);
}

// =====================================================
// Function under test: CT2_transfer
// =====================================================
TEST_F(CT2_BankingFixture, CT2_transfer_MovesFundsBetweenAccounts)
{
    CT2_transfer(*alice, *bob, 40.0);
    EXPECT_EQ(alice->balance, 60.0);
    EXPECT_EQ(bob->balance, 40.0);
}

TEST_F(CT2_BankingFixture, CT2_transfer_RejectsNonPositiveAmount)
{
    EXPECT_THROW(CT2_transfer(*alice, *bob, 0.0), std::invalid_argument);
    EXPECT_THROW(CT2_transfer(*alice, *bob, -1.0), std::invalid_argument);
    EXPECT_EQ(alice->balance, 100.0);
    EXPECT_EQ(bob->balance, 0.0);
}

TEST_F(CT2_BankingFixture, CT2_transfer_RejectsInsufficientFundsAndKeepsDestUnchanged)
{
    EXPECT_THROW(CT2_transfer(*alice, *bob, 150.0), std::runtime_error);
    EXPECT_EQ(alice->balance, 100.0);
    EXPECT_EQ(bob->balance, 0.0);
}

// =====================================================
// Function under test: CT2_apply_simple_interest
// =====================================================
TEST_F(CT2_BankingFixture, CT2_apply_simple_interest_ComputesSimpleInterestNear)
{
    double v = CT2_apply_simple_interest(100.0, 0.10, 36);
    EXPECT_NEAR(v, 100.9863, 1e-3);
}

TEST_F(CT2_BankingFixture, CT2_apply_simple_interest_InvalidArgumentsThrow)
{
    EXPECT_THROW(CT2_apply_simple_interest(-100.0, 0.1, 10), std::invalid_argument);
    EXPECT_THROW(CT2_apply_simple_interest(100.0, -0.1, 10), std::invalid_argument);
    EXPECT_THROW(CT2_apply_simple_interest(100.0, 1.5, 10), std::invalid_argument);
    EXPECT_THROW(CT2_apply_simple_interest(100.0, 0.1, -5), std::invalid_argument);
}

TEST_F(CT2_BankingFixture, CT2_apply_simple_interest_BoundaryValues)
{
    EXPECT_NEAR(CT2_apply_simple_interest(0.0,   0.10, 100), 0.0,   1e-12);
    EXPECT_NEAR(CT2_apply_simple_interest(100.0, 0.00, 365), 100.0, 1e-12);
    EXPECT_NEAR(CT2_apply_simple_interest(100.0, 1.00,   0), 100.0, 1e-12);
    EXPECT_NEAR(CT2_apply_simple_interest(100.0, 1.00, 365), 200.0, 1e-9);
}
