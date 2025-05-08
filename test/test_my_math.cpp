#include <gtest/gtest.h>
#include "my_math.h"

TEST(MyMathTest, AddTest) {
    MyMath math;
    EXPECT_EQ(math.add(2, 3), 5);
    EXPECT_EQ(math.add(-1, 1), 0);
}

TEST(MyMathTest, MultiplyTest) {
    MyMath math;
    EXPECT_EQ(math.multiply(2, 3), 6);
    EXPECT_EQ(math.multiply(-1, 1), -1);
}


