#include "vector.hpp"

#include <gtest/gtest.h>

TEST(VectorTest, DefaultConstructor) {
  std::vector<int> s;
  ft::vector<int>  f;
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.data(), f.data());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}

TEST(VectorTest, At) {
  std::vector<int> s(10);
  ft::vector<int>  f(10);

  s[5] = 10;
  f[5] = 10;
  EXPECT_EQ(s.at(0), f.at(0));
  EXPECT_EQ(s.at(5), f.at(5));
  EXPECT_THROW(s.at(20), std::out_of_range);
  EXPECT_THROW(f.at(20), std::out_of_range);
}

TEST(VectorTest, BeginAndEnd) {
  ft::vector<int>           f(10);
  ft::vector<int>::iterator it = f.begin();

  f[0]                         = 21;
  f[9]                         = 42;
  EXPECT_EQ(f[0], *(f.begin()));
  EXPECT_EQ(f[9], *(--(f.end())));
  for (size_t i = 0; i < 10; i++) {
    it++;
  }
  EXPECT_EQ(it, f.end());
}

TEST(VectorTest, IteratorConstructor) {
  ft::vector<int> f(10);
  for (size_t i = 0; i < 10; i++) {
    f[i] = i;
  }
  ft::vector<int>::iterator       it = f.begin();
  ft::vector<int>::iterator       it2(it);
  ft::vector<int>::const_iterator cit = f.begin();
  EXPECT_EQ(true, (it == it2));
  EXPECT_EQ(true, (it == cit));
  EXPECT_EQ(true, (cit == it));
  EXPECT_EQ(false, (it != it2));
  EXPECT_EQ(false, (it != cit));
  EXPECT_EQ(true, (it <= it2));
  EXPECT_EQ(true, (it <= cit));
  EXPECT_EQ(true, (it >= it2));
  EXPECT_EQ(true, (it >= cit));
  EXPECT_EQ(false, (it < it2));
  EXPECT_EQ(false, (it < cit));
  EXPECT_EQ(false, (it > it2));
  EXPECT_EQ(false, (it > cit));
  cit++;
  it2++;
  EXPECT_EQ(false, (it == it2));
  EXPECT_EQ(false, (it == cit));
  EXPECT_EQ(true, (it != it2));
  EXPECT_EQ(true, (it != cit));
  EXPECT_EQ(true, (it <= it2));
  EXPECT_EQ(true, (it <= cit));
  EXPECT_EQ(false, (it >= it2));
  EXPECT_EQ(false, (it >= cit));
  EXPECT_EQ(true, (it < it2));
  EXPECT_EQ(true, (it < cit));
  EXPECT_EQ(false, (it > it2));
  EXPECT_EQ(false, (it > cit));
}