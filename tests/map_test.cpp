#include "map.hpp"

#include <gtest/gtest.h>

#include <random>

TEST(MapTest, constructor) {
  ft::map<int, int> m;

  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, simpleInsert) {
  std::random_device rand;
  {
    ft::map<int, int> m;
    int               times = 10000;
    for (size_t i = 0; i < times; i++) {
      m.insert(ft::make_pair(i, i));
      EXPECT_EQ(m.size(), i + 1);
      // check m[i] == i
    }
  }
  {
    ft::map<int, int> m;
    int               times = 10000;
    for (size_t i = 0; i < times; i++) {
      int tmp = rand() % times;
      m.insert(ft::make_pair(tmp, i));
      EXPECT_EQ(m.size(), i + 1);
      // check m[i] == i
    }
  }
}
