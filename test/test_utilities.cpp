#include <gtest/gtest.h>
#include "utilities.h"

// Test for isPair function
TEST(UtilitiesTest, IsPair) {

    Utilities utilities_obj;

    EXPECT_TRUE(utilities_obj.isPair(0));    // 0 is even
    EXPECT_TRUE(utilities_obj.isPair(2));    // 2 is even
}