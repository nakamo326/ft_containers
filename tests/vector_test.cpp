#include "vector.hpp"

#include <gtest/gtest.h>

class VectorTest : public ::testing::Test {};

TEST_F(VectorTest, DefaultConstructor) {
  ft::vector<int> v;
  EXPECT_EQ(0, v.size());
  // EXPECT_EQ(0, v.capacity());
  // EXPECT_EQ(0, v.begin() - v.end());
}
