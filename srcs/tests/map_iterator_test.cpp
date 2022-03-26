#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "testframe/testframe.hpp"
#endif

#include "map.hpp"

TEST(MapIteratorTest, Iterator) {
  ft::map<int, int> m;

  m.insert(ft::make_pair(7, 7));
  m.insert(ft::make_pair(1, 1));
  m.insert(ft::make_pair(3, 3));
  m.insert(ft::make_pair(2, 2));
  m.insert(ft::make_pair(4, 4));
  m.insert(ft::make_pair(6, 6));
  m.insert(ft::make_pair(5, 5));

  ft::map<int, int>::iterator it = m.begin();
  EXPECT_EQ((*it).second, 1);
  EXPECT_EQ(it->second, 1);
  (*it).second = 42;
  EXPECT_EQ((*it).second, 42);
  EXPECT_EQ(it->second, 42);
  it->second = 57;
  EXPECT_EQ((*it).second, 57);
  EXPECT_EQ(it->second, 57);
  ++it;
  EXPECT_EQ((*it).second, 2);
  EXPECT_EQ(it->second, 2);
  it++;
  EXPECT_EQ((*it).second, 3);
  EXPECT_EQ(it->second, 3);
  --it;
  EXPECT_EQ((*it).second, 2);
  EXPECT_EQ(it->second, 2);
  it--;
  for (int i = 1; it != m.end(); it++) {
    EXPECT_EQ(it->first, i);
    i++;
  }
}

TEST(MapIteratorTest, ConstIterator) {
  ft::map<int, int> m;

  m.insert(ft::make_pair(7, 7));
  m.insert(ft::make_pair(1, 1));
  m.insert(ft::make_pair(3, 3));
  m.insert(ft::make_pair(2, 2));
  m.insert(ft::make_pair(4, 4));
  m.insert(ft::make_pair(6, 6));
  m.insert(ft::make_pair(5, 5));

  ft::map<int, int>::const_iterator it = m.begin();
  EXPECT_EQ((*it).second, 1);
  EXPECT_EQ(it->second, 1);
  ++it;
  EXPECT_EQ((*it).second, 2);
  EXPECT_EQ(it->second, 2);
  it++;
  EXPECT_EQ((*it).second, 3);
  EXPECT_EQ(it->second, 3);
  --it;
  EXPECT_EQ((*it).second, 2);
  EXPECT_EQ(it->second, 2);
  it--;
  for (int i = 1; it != m.end(); it++) {
    EXPECT_EQ(it->first, i);
    i++;
  }
}

TEST(MapIteratorTest, ReverseIterator) {
  ft::map<int, int> m;

  m.insert(ft::make_pair(7, 7));
  m.insert(ft::make_pair(1, 1));
  m.insert(ft::make_pair(3, 3));
  m.insert(ft::make_pair(2, 2));
  m.insert(ft::make_pair(4, 4));
  m.insert(ft::make_pair(6, 6));
  m.insert(ft::make_pair(5, 5));

  ft::map<int, int>::reverse_iterator rit(m.rbegin());

  EXPECT_EQ((*rit).second, 7);
  EXPECT_EQ(rit->second, 7);
  (*rit).second = 42;
  EXPECT_EQ((*rit).second, 42);
  EXPECT_EQ(rit->second, 42);
  rit->second = 57;
  EXPECT_EQ((*rit).second, 57);
  EXPECT_EQ(rit->second, 57);
  ++rit;
  EXPECT_EQ((*rit).second, 6);
  EXPECT_EQ(rit->second, 6);
  rit++;
  EXPECT_EQ((*rit).second, 5);
  EXPECT_EQ(rit->second, 5);
  --rit;
  EXPECT_EQ((*rit).second, 6);
  EXPECT_EQ(rit->second, 6);
  rit--;
  for (int i = 7; rit != m.rend(); rit++) {
    EXPECT_EQ(rit->first, i);
    i--;
  }
}

TEST(MapIteratorTest, ConstReverseIterator) {
  ft::map<int, int> m;

  m.insert(ft::make_pair(7, 7));
  m.insert(ft::make_pair(1, 1));
  m.insert(ft::make_pair(3, 3));
  m.insert(ft::make_pair(2, 2));
  m.insert(ft::make_pair(4, 4));
  m.insert(ft::make_pair(6, 6));
  m.insert(ft::make_pair(5, 5));

  ft::map<int, int>::const_reverse_iterator rit(m.rbegin());

  EXPECT_EQ((*rit).second, 7);
  EXPECT_EQ(rit->second, 7);
  ++rit;
  EXPECT_EQ((*rit).second, 6);
  EXPECT_EQ(rit->second, 6);
  rit++;
  EXPECT_EQ((*rit).second, 5);
  EXPECT_EQ(rit->second, 5);
  --rit;
  EXPECT_EQ((*rit).second, 6);
  EXPECT_EQ(rit->second, 6);
  rit--;
  for (int i = 7; rit != m.rend(); rit++) {
    EXPECT_EQ(rit->first, i);
    i--;
  }
}
