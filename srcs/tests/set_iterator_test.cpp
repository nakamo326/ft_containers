
#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "testframe/testframe.hpp"
#endif

#include "set.hpp"

TEST(SetIteratorTest, Iterator) {
  ft::set<int> m;

  m.insert(7);
  m.insert(1);
  m.insert(3);
  m.insert(2);
  m.insert(4);
  m.insert(6);
  m.insert(5);

  ft::set<int>::iterator it = m.begin();
  EXPECT_EQ((*it), 1);
  *it = 42;
  EXPECT_EQ((*it), 42);
  *it = 57;
  EXPECT_EQ((*it), 57);
  *it = 1;
  ++it;
  EXPECT_EQ((*it), 2);
  it++;
  EXPECT_EQ((*it), 3);
  --it;
  EXPECT_EQ((*it), 2);
  it--;
  for (int i = 1; it != m.end(); it++) {
    EXPECT_EQ(*it, i);
    i++;
  }
}

TEST(SetIteratorTest, ConstIterator) {
  ft::set<int> m;

  m.insert(7);
  m.insert(1);
  m.insert(3);
  m.insert(2);
  m.insert(4);
  m.insert(6);
  m.insert(5);

  ft::set<int>::const_iterator it = m.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  it++;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  it--;
  for (int i = 1; it != m.end(); it++) {
    EXPECT_EQ(*it, i);
    i++;
  }
}

TEST(SetIteratorTest, ReverseIterator) {
  ft::set<int> m;

  m.insert(7);
  m.insert(1);
  m.insert(3);
  m.insert(2);
  m.insert(4);
  m.insert(6);
  m.insert(5);

  ft::set<int>::reverse_iterator rit(m.rbegin());

  EXPECT_EQ(*rit, 7);
  *rit = 42;
  EXPECT_EQ(*rit, 42);
  *rit = 7;
  ++rit;
  EXPECT_EQ(*rit, 6);
  rit++;
  EXPECT_EQ(*rit, 5);
  --rit;
  EXPECT_EQ(*rit, 6);
  rit--;
  for (int i = 7; rit != m.rend(); rit++) {
    EXPECT_EQ(*rit, i);
    i--;
  }
}

TEST(SetIteratorTest, ConstReverseIterator) {
  ft::set<int> m;

  m.insert(7);
  m.insert(1);
  m.insert(3);
  m.insert(2);
  m.insert(4);
  m.insert(6);
  m.insert(5);

  ft::set<int>::const_reverse_iterator rit(m.rbegin());

  EXPECT_EQ(*rit, 7);
  ++rit;
  EXPECT_EQ(*rit, 6);
  rit++;
  EXPECT_EQ(*rit, 5);
  --rit;
  EXPECT_EQ(*rit, 6);
  rit--;
  for (int i = 7; rit != m.rend(); rit++) {
    EXPECT_EQ(*rit, i);
    i--;
  }
}
