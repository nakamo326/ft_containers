
#include "map.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <random>
#include <typeinfo>
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
    EXPECT_EQ(*it, from.at(i * 2));
    it++;
  }
}

TEST(MapTest, copyConstructor) {
  ft::map<int, int> from;
  for (int i = 0; i < 10; i++) {
    from.insert(ft::make_pair(i, i));
  }
  ft::map<int, int> m(from);

  ft::map<int, int>::iterator it   = m.begin();
  ft::map<int, int>::iterator f_it = from.begin();
  EXPECT_EQ(m.size(), 10);
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(*it, *f_it);
    it++;
    f_it++;
  }
}

TEST(MapTest, MaxSize) {
  std::map<int, int> s;
  ft::map<int, int>  f;
  EXPECT_EQ(s.max_size(), f.max_size());
}

TEST(MapTest, empty) {
  ft::map<int, int> m;
  EXPECT_EQ(m.empty(), true);
  m.insert(ft::make_pair(0, 0));
  EXPECT_EQ(m.empty(), false);
}

TEST(MapTest, size) {
  ft::map<int, int> m;
  EXPECT_EQ(m.size(), 0);
  for (size_t i = 1; i <= 1000; i++) {
    m.insert(ft::make_pair(i, i));
    EXPECT_EQ(m.size(), i);
  }
  for (size_t i = 1; i <= 1000; i++) {
    m.erase(i);
    EXPECT_EQ(m.size(), 1000 - i);
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

TEST(MapTest, count) {
  ft::map<int, int> m;
  EXPECT_TRUE(m.count(0) == 0);
  m.insert(ft::make_pair(0, 42));
  EXPECT_TRUE(m.count(0) == 1);
  EXPECT_TRUE(m.count(1) == 0);
}