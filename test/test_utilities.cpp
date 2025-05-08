#include <gtest/gtest.h>
#include "utilities.h"

// Test for isPair function
TEST(UtilitiesTest, IsPair) {
    EXPECT_TRUE(isPair(0));    // 0 is even
    EXPECT_TRUE(isPair(2));    // 2 is even
}