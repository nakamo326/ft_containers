
#include "map.hpp"

#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "pair.hpp"

TEST(MapTest, constructor) {
  ft::map<int, int> m;

  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, rangeConstructor) {
  std::vector<ft::pair<const int, int> > from;
  for (int i = 0; i < 10; i++) {
    from.push_back(ft::make_pair(i, i));
    from.push_back(ft::make_pair(i, i));
  }
  ft::map<int, int> m(from.begin(), from.end());

  ft::map<int, int>::iterator it = m.begin();
  EXPECT_EQ(m.size(), 10);
  for (int i = 0; i < 10; i++) {
    // EXPECT_EQ(*it, from.at(i * 2));
    // it++;
  }
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
