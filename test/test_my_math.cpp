#include <gtest/gtest.h>
#include "my_math.h"
#include "../test/mocks/mock_utilities.h"

TEST(MyMathTest, AddTest) {
    MyMath math;
    MockUtilities mockUtilities;

    EXPECT_CALL(mockUtilities, isPair(testing::_)).Times(0);  // Check pair call with any value as argument 
        
    EXPECT_EQ(math.add(2, 3), 5);
    EXPECT_EQ(math.add(-1, 1), 0);
}

TEST(MyMathTest, MultiplyTest) {
    MyMath math;
    EXPECT_EQ(math.multiply(2, 3), 6);
    EXPECT_EQ(math.multiply(-1, 1), -1);
}