#include <gtest/gtest.h>

int testfunc();

TEST(TestOfTest, testfunc) { EXPECT_EQ(1, testfunc()); }