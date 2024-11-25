#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "my_math.h"

// Mock class for MyMath
class MockMyMath : public MyMath {
public:
    MOCK_METHOD(int, add, (int a, int b), (override));
    MOCK_METHOD(int, multiply, (int a, int b), (override));
};

// Test the add method
TEST(MyMathTest, AddTest) {
    MockMyMath mock_math;
    EXPECT_CALL(mock_math, add(2, 3))
        .Times(1)
        .WillOnce(::testing::Return(5));

    EXPECT_EQ(mock_math.add(2, 3), 5);
}

// Test the multiply method
TEST(MyMathTest, MultiplyTest) {
    MockMyMath mock_math;
    EXPECT_CALL(mock_math, multiply(4, 5))
        .Times(1)
        .WillOnce(::testing::Return(20));

    EXPECT_EQ(mock_math.multiply(4, 5), 20);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}