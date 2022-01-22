#include "vector.hpp"

#include <gtest/gtest.h>

class VectorTest : public ::testing::Test {};

TEST_F(VectorTest, DefaultConstructor) {
  ft::vector<int>  f;
  std::vector<int> s;
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.data(), f.data());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}
