
#include "map.hpp"

#include "pair.hpp"
#include "switch.hpp"

#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "testframe/testframe.hpp"
#endif

#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

TEST(MapTest, constructor) {
  LIB::map<int, int> m;

  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, rangeConstructor) {
  std::vector<LIB::pair<const int, int> > from;
  for (int i = 0; i < 10; i++) {
    from.push_back(LIB::make_pair(i, i));
    from.push_back(LIB::make_pair(i, i));
  }
  LIB::map<int, int> m(from.begin(), from.end());

  LIB::map<int, int>::iterator it = m.begin();
  EXPECT_EQ(m.size(), 10);
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(*it, from.at(i * 2));
    it++;
  }
}

TEST(MapTest, copyConstructor) {
  LIB::map<int, int> from;
  for (int i = 0; i < 10; i++) {
    from.insert(LIB::make_pair(i, i));
  }
  LIB::map<int, int> m(from);

  LIB::map<int, int>::iterator it   = m.begin();
  LIB::map<int, int>::iterator f_it = from.begin();
  EXPECT_EQ(m.size(), 10);
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(*it, *f_it);
    it++;
    f_it++;
  }
}

TEST(MapTest, assignation) {
  LIB::map<int, int> from;
  for (int i = 0; i < 10; i++) {
    from.insert(LIB::make_pair(i, i));
  }
  LIB::map<int, int> m;
  for (int i = 0; i < 5; i++) {
    from.insert(LIB::make_pair(i, 42));
  }

  m = from;

  EXPECT_EQ(m.size(), from.size());
  for (size_t i = 0; i < 10; i++) {
    EXPECT_EQ(from[i], m[i]);
  }
  m[42] = 42;
  EXPECT_NE(from[42], m[42]);
}

TEST(MapTest, GetAllocator) {
  LIB::map<int, int> f;

  LIB::map<int, int>::allocator_type a   = f.get_allocator();
  LIB::map<int, int>::value_type*    val = a.allocate(1);
  val->second                            = 42;
  EXPECT_EQ(val->second, 42);
  a.deallocate(val, 1);
}

TEST(MapTest, arrayOperator) {
  LIB::map<int, int> m;
  m[0] = 57;
  EXPECT_EQ(m[0], 57);
  EXPECT_EQ(m[42], int());
  m[0] = 42;
  EXPECT_EQ(m[0], 42);
}

TEST(MapTest, empty) {
  LIB::map<int, int> m;
  EXPECT_EQ(m.empty(), true);
  m.insert(LIB::make_pair(0, 0));
  EXPECT_EQ(m.empty(), false);
}

TEST(MapTest, size) {
  LIB::map<int, int> m;
  EXPECT_EQ(m.size(), 0);
  for (size_t i = 1; i <= 1000; i++) {
    m.insert(LIB::make_pair(i, i));
    EXPECT_EQ(m.size(), i);
  }
  for (size_t i = 1; i <= 1000; i++) {
    m.erase(i);
    EXPECT_EQ(m.size(), 1000 - i);
  }
}

TEST(MapTest, simpleInsert) {
  std::srand(time(NULL));
  {
    LIB::map<int, int> m;
    int                times = 10000;
    for (size_t i = 0; i < times; i++) {
      m.insert(LIB::make_pair(i, i));
      EXPECT_EQ(m.size(), i + 1);
      EXPECT_EQ(m[i], i);
    }
  }
  {
    std::vector<int> v(10000);
    for (size_t i = 0; i < 10000; i++) {
      v[i] = i;
    }
    for (size_t i = 10000; i > 1; --i) {
      size_t a = i - 1;
      size_t b = rand() % i;
      std::swap(v[a], v[b]);
    }
    LIB::map<int, int> m;
    for (size_t i = 0; i < 10000; i++) {
      m.insert(LIB::make_pair(v[i], v[i]));
      EXPECT_EQ(m.size(), i + 1);
    }
    LIB::map<int, int>::iterator it = m.begin();
    for (size_t i = 0; i < 10000; i++) {
      EXPECT_EQ((*it).first, i);
      it++;
    }
  }
}

TEST(MapTest, positionInsert) {
  std::srand(time(NULL));
  LIB::map<int, int> m;
  int                times = 10000;
  std::vector<int>   v(times);
  for (size_t i = 0; i < times; i++) {
    v[i] = i;
  }
  for (size_t i = times; i > 1; --i) {
    size_t a = i - 1;
    size_t b = rand() % i;
    std::swap(v[a], v[b]);
  }

  for (size_t i = 0; i < times; i++) {
    int choice = rand() % 4;
    if (choice == 0) {
      m.insert(m.begin(), LIB::make_pair(v[i], v[i]));
    } else if (choice == 1) {
      m.insert(m.end(), LIB::make_pair(v[i], v[i]));
    } else if (choice == 2) {
      m.insert(m.upper_bound(v[i]), LIB::make_pair(v[i], v[i]));
    } else if (choice == 3) {
      m.insert(m.lower_bound(v[i]), LIB::make_pair(v[i], v[i]));
    }
  }

  LIB::map<int, int>::iterator it  = m.begin();
  int                          num = it->first;
  it++;
  for (; it != m.end(); it++) {
    EXPECT_EQ(num < (it->first), true);
  }
}

TEST(MapTest, rangeInsert) {
  LIB::map<int, int>                m;
  std::vector<LIB::pair<int, int> > v(1000);
  for (size_t i = 0; i < 1000; i++) {
    v[i] = LIB::make_pair(i, i);
  }
  m.insert(v.begin(), v.end());
  LIB::map<int, int>::iterator it(m.begin());
  for (size_t i = 0; it != m.end(); it++) {
    EXPECT_EQ(it->first, i);
    i++;
  }
}

TEST(MapTest, Erase) {
  LIB::map<int, int> m;
  int                times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(LIB::make_pair(i, i));
  }
  for (size_t i = 1; i <= times; i++) {
    m.erase(i);
    EXPECT_EQ(m.size(), times - i);
    EXPECT_EQ(m.count(i), 0);
  }
}

TEST(MapTest, positionErase) {
  LIB::map<int, int> m;
  int                times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(LIB::make_pair(i, i));
  }
  for (size_t i = 1; i <= times; i++) {
    m.erase(m.find(i));
    EXPECT_EQ(m.size(), times - i);
    EXPECT_EQ(m.count(i), 0);
  }
}

TEST(MapTest, rangeErase) {
  LIB::map<int, int> m;
  int                times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(LIB::make_pair(i, i));
  }
  m.erase(m.begin(), m.end());
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, Swap) {
  LIB::map<int, int> m;
  int                times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(LIB::make_pair(i, i));
  }
  LIB::map<int, int> n;
  for (size_t i = 1; i <= 1000; i++) {
    n.insert(LIB::make_pair(i, 42));
  }
  LIB::map<int, int>::iterator m_it = m.begin();
  LIB::map<int, int>::iterator n_it = n.begin();
  n.swap(m);
  EXPECT_EQ(n.size(), times);
  for (int i = 1; m_it != n.end(); m_it++) {
    EXPECT_EQ(m_it->first, i);
    EXPECT_EQ(m_it->second, i);
    i++;
  }
  for (int i = 1; n_it != m.end(); n_it++) {
    EXPECT_EQ(n_it->first, i);
    EXPECT_EQ(n_it->second, 42);
    i++;
  }
}

TEST(MapTest, Clear) {
  LIB::map<int, int> m;
  int                times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(LIB::make_pair(i, i));
  }
  m.clear();
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, count) {
  LIB::map<int, int> m;
  EXPECT_TRUE(m.count(0) == 0);
  m.insert(LIB::make_pair(0, 42));
  EXPECT_TRUE(m.count(0) == 1);
  m.insert(LIB::make_pair(0, 42));
  EXPECT_TRUE(m.count(0) == 1);
  EXPECT_TRUE(m.count(1) == 0);
}

TEST(MapTest, find) {
  LIB::map<int, int> m;
  m.insert(LIB::make_pair(1, 42));
  m.insert(LIB::make_pair(3, 42));
  m.insert(LIB::make_pair(2, 42));

  EXPECT_EQ(m.find(0), m.end());
  EXPECT_NE(m.find(1), m.end());
  EXPECT_EQ(m.find(1)->second, 42);
  EXPECT_NE(m.find(2), m.end());
  EXPECT_EQ(m.find(2)->second, 42);
  EXPECT_NE(m.find(3), m.end());
  EXPECT_EQ(m.find(3)->second, 42);
  EXPECT_EQ(m.find(4), m.end());

  LIB::map<int, int>::const_iterator cit = m.find(1);
  // cannot assign
  // cit->second = 57;
}

TEST(MapTest, equalRange) {
  LIB::map<int, int> m;
  m.insert(LIB::make_pair(1, 1));
  m.insert(LIB::make_pair(3, 3));
  m.insert(LIB::make_pair(2, 2));
  m.insert(LIB::make_pair(0, 0));
  m.insert(LIB::make_pair(6, 6));

  EXPECT_EQ(m.lower_bound(-1), m.equal_range(-1).first);
  EXPECT_EQ(m.upper_bound(-1), m.equal_range(-1).second);
  EXPECT_EQ(m.lower_bound(2), m.equal_range(2).first);
  EXPECT_EQ(m.upper_bound(2), m.equal_range(2).second);
  EXPECT_EQ(m.lower_bound(3), m.equal_range(3).first);
  EXPECT_EQ(m.upper_bound(3), m.equal_range(3).second);
  EXPECT_EQ(m.lower_bound(5), m.equal_range(5).first);
  EXPECT_EQ(m.upper_bound(5), m.equal_range(5).second);
  EXPECT_EQ(m.lower_bound(8), m.equal_range(8).first);
  EXPECT_EQ(m.upper_bound(8), m.equal_range(8).second);
}

TEST(MapTest, lowerBound) {
  LIB::map<int, int> m;
  m.insert(LIB::make_pair(1, 1));
  m.insert(LIB::make_pair(3, 3));
  m.insert(LIB::make_pair(2, 2));
  m.insert(LIB::make_pair(0, 0));
  m.insert(LIB::make_pair(6, 6));

  EXPECT_EQ(m.lower_bound(2)->second, 2);
  EXPECT_EQ(m.lower_bound(3)->second, 3);
  EXPECT_EQ(m.lower_bound(10), m.end());
}

TEST(MapTest, upperBound) {
  LIB::map<int, int> m;
  m.insert(LIB::make_pair(1, 1));
  m.insert(LIB::make_pair(3, 3));
  m.insert(LIB::make_pair(2, 2));
  m.insert(LIB::make_pair(0, 0));
  m.insert(LIB::make_pair(6, 6));

  EXPECT_EQ(m.upper_bound(2)->second, 3);
  EXPECT_EQ(m.upper_bound(3)->second, 6);
  EXPECT_EQ(m.upper_bound(10), m.end());
}

TEST(MapTest, KeyCompare) {
  LIB::map<int, int> m;

  LIB::map<int, int>::key_compare kc = m.key_comp();

  EXPECT_EQ(kc(0, 1), true);
  EXPECT_EQ(kc(42, 0), false);
}

TEST(MapTest, ValueCompare) {
  LIB::map<int, int> m;

  LIB::map<int, int>::value_compare vc = m.value_comp();

  EXPECT_EQ(vc(LIB::make_pair(0, 0), LIB::make_pair(1, 0)), true);
  EXPECT_EQ(vc(LIB::make_pair(42, 0), LIB::make_pair(1, 0)), false);
}

TEST(MapTest, ComparisonOperators) {
  LIB::map<int, int> m;
  m.insert(LIB::make_pair(0, 0));
  m.insert(LIB::make_pair(1, 1));
  m.insert(LIB::make_pair(2, 2));
  m.insert(LIB::make_pair(3, 3));

  LIB::map<int, int> c(m);

  EXPECT_EQ(m == c, true);
  EXPECT_EQ(m != c, false);
  EXPECT_EQ(m < c, false);
  EXPECT_EQ(m > c, false);
  EXPECT_EQ(m <= c, true);
  EXPECT_EQ(m >= c, true);

  m[3] = -10;
  EXPECT_EQ(m == c, false);
  EXPECT_EQ(m != c, true);
  EXPECT_EQ(m < c, true);
  EXPECT_EQ(m > c, false);
  EXPECT_EQ(m <= c, true);
  EXPECT_EQ(m >= c, false);

  m[3] = 3;
  c.insert(LIB::make_pair(4, 4));
  EXPECT_EQ(m == c, false);
  EXPECT_EQ(m != c, true);
  EXPECT_EQ(m < c, true);
  EXPECT_EQ(m > c, false);
  EXPECT_EQ(m <= c, true);
  EXPECT_EQ(m >= c, false);

  m.insert(LIB::make_pair(4, 42));
  EXPECT_EQ(m == c, false);
  EXPECT_EQ(m != c, true);
  EXPECT_EQ(m < c, false);
  EXPECT_EQ(m > c, true);
  EXPECT_EQ(m <= c, false);
  EXPECT_EQ(m >= c, true);

  m[4] = 4;
  c[2] = 42;
  EXPECT_EQ(m == c, false);
  EXPECT_EQ(m != c, true);
  EXPECT_EQ(m < c, true);
  EXPECT_EQ(m > c, false);
  EXPECT_EQ(m <= c, true);
  EXPECT_EQ(m >= c, false);
}

TEST(MapIteratorTest, Iterator) {
  LIB::map<int, int> m;

  m.insert(LIB::make_pair(7, 7));
  m.insert(LIB::make_pair(1, 1));
  m.insert(LIB::make_pair(3, 3));
  m.insert(LIB::make_pair(2, 2));
  m.insert(LIB::make_pair(4, 4));
  m.insert(LIB::make_pair(6, 6));
  m.insert(LIB::make_pair(5, 5));

  LIB::map<int, int>::iterator it = m.begin();
  EXPECT_EQ((*it).second, 1);
  EXPECT_EQ(it->second, 1);
  (*it).second = 42;
  EXPECT_EQ((*it).second, 42);
  EXPECT_EQ(it->second, 42);
  it->second = 57;
  EXPECT_EQ((*it).second, 57);
  EXPECT_EQ(it->second, 57);
  ++it;
  m.insert(LIB::make_pair(8, 8));
  EXPECT_EQ((*it).second, 2);
  EXPECT_EQ(it->second, 2);
  it++;
  m.erase(7);
  EXPECT_EQ((*it).second, 3);
  EXPECT_EQ(it->second, 3);
  --it;
  EXPECT_EQ((*it).second, 2);
  EXPECT_EQ(it->second, 2);
  it--;
  m.insert(LIB::make_pair(7, 7));
  for (int i = 1; it != m.end(); it++) {
    EXPECT_EQ(it->first, i);
    i++;
  }
}

TEST(MapIteratorTest, ConstIterator) {
  LIB::map<int, int> m;

  m.insert(LIB::make_pair(7, 7));
  m.insert(LIB::make_pair(1, 1));
  m.insert(LIB::make_pair(3, 3));
  m.insert(LIB::make_pair(2, 2));
  m.insert(LIB::make_pair(4, 4));
  m.insert(LIB::make_pair(6, 6));
  m.insert(LIB::make_pair(5, 5));

  LIB::map<int, int>::const_iterator it = m.begin();
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
  LIB::map<int, int> m;

  m.insert(LIB::make_pair(7, 7));
  m.insert(LIB::make_pair(1, 1));
  m.insert(LIB::make_pair(3, 3));
  m.insert(LIB::make_pair(2, 2));
  m.insert(LIB::make_pair(4, 4));
  m.insert(LIB::make_pair(6, 6));
  m.insert(LIB::make_pair(5, 5));

  LIB::map<int, int>::reverse_iterator rit(m.rbegin());

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
  LIB::map<int, int> m;

  m.insert(LIB::make_pair(7, 7));
  m.insert(LIB::make_pair(1, 1));
  m.insert(LIB::make_pair(3, 3));
  m.insert(LIB::make_pair(2, 2));
  m.insert(LIB::make_pair(4, 4));
  m.insert(LIB::make_pair(6, 6));
  m.insert(LIB::make_pair(5, 5));

  LIB::map<int, int>::const_reverse_iterator rit(m.rbegin());

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
