#include "../src/Example.hpp" 
#include <gtest/gtest.h>  


// Fixture for the tests
class SquareTests : public ::testing::Test 
{
    protected:
        // Setup before each test
        void SetUp() override {
            // Any necessary initializations
        }

        // Cleanup after each test
        void TearDown() override {
            // Any necessary cleanups
        }
};


TEST_F(SquareTests, positiveValidValues) 
{
    ASSERT_EQ(square(5), 25);
    ASSERT_EQ(square(9), 81);
    ASSERT_EQ(square(10), 100);
    ASSERT_EQ(square(4), 16);         
}

TEST_F(SquareTests, negativeValidValues)  
{
    ASSERT_EQ(square(-10), 100);
    ASSERT_EQ(square(-9), 81);
}

TEST_F(SquareTests, invalidValues) 
{
    ASSERT_EQ(square(-20), 99999);
    ASSERT_EQ(square(-11), 99999);  
    ASSERT_EQ(square(20), 99999);
    ASSERT_EQ(square(11), 99999);
    ASSERT_EQ(square(1000000), 99999); 
    ASSERT_EQ(square(-1000000), 99999);
}























/*
// It is a class for testing
class CalculatorTesting : public ::testing::Test
{

    virtual void SetUp() override
    {
        // Pre conditions for all tests
    }

    virtual void TearDown() override
    {
        // Post conditions for all tests
    }
};
*/