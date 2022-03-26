
#include "set.hpp"

#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "testframe/testframe.hpp"
#endif

#include <limits>
#include <random>
#include <typeinfo>
#include <vector>

#include "pair.hpp"

TEST(SetTest, constructor) {
  ft::set<int> m;

  EXPECT_EQ(m.size(), 0);
}

TEST(SetTest, rangeConstructor) {
  std::vector<int> from;
  for (int i = 0; i < 10; i++) {
    from.push_back(i);
    from.push_back(i);
  }
  ft::set<int> m(from.begin(), from.end());

  ft::set<int>::iterator it = m.begin();
  EXPECT_EQ(m.size(), 10);
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(*it, from.at(i * 2));
    it++;
  }
}

TEST(SetTest, copyConstructor) {
  ft::set<int> from;
  for (int i = 0; i < 10; i++) {
    from.insert(i);
  }
  ft::set<int> m(from);

  ft::set<int>::iterator it   = m.begin();
  ft::set<int>::iterator f_it = from.begin();
  EXPECT_EQ(m.size(), 10);
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(*it, *f_it);
    it++;
    f_it++;
  }
}

TEST(SetTest, assignation) {
  ft::set<int> from;
  for (int i = 0; i < 10; i++) {
    from.insert(i);
  }
  ft::set<int> m;
  for (int i = 0; i < 5; i++) {
    from.insert(4);
  }

  m = from;

  EXPECT_EQ(m == from, true);
}

TEST(SetTest, GetAllocator) {
  ft::set<int> f;

  ft::set<int>::allocator_type a   = f.get_allocator();
  ft::set<int>::value_type*    val = a.allocate(1);
  *val                             = 42;
  EXPECT_EQ(*val, 42);
  a.deallocate(val, 1);
}

TEST(SetTest, empty) {
  ft::set<int> m;
  EXPECT_EQ(m.empty(), true);
  m.insert(0);
  EXPECT_EQ(m.empty(), false);
}

TEST(SetTest, size) {
  ft::set<int> m;
  EXPECT_EQ(m.size(), 0);
  for (size_t i = 1; i <= 1000; i++) {
    m.insert(i);
    EXPECT_EQ(m.size(), i);
  }
  for (size_t i = 1; i <= 1000; i++) {
    m.erase(i);
    EXPECT_EQ(m.size(), 1000 - i);
  }
}

TEST(SetTest, MaxSize) {
  std::set<int> s;
  ft::set<int>  f;
  EXPECT_EQ(s.max_size(), f.max_size());
}

TEST(SetTest, simpleInsert) {
  std::random_device rand;
  {
    ft::set<int> m;
    int          times = 10000;
    for (size_t i = 0; i < times; i++) {
      m.insert(i);
      EXPECT_EQ(m.size(), i + 1);
      EXPECT_EQ(m.count(i), true);
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
    ft::set<int> m;
    for (size_t i = 0; i < 10000; i++) {
      m.insert(v[i]);
      EXPECT_EQ(m.size(), i + 1);
    }
    ft::set<int>::iterator it = m.begin();
    for (size_t i = 0; i < 10000; i++) {
      EXPECT_EQ(*it, i);
      it++;
    }
  }
}

TEST(SetTest, positionInsert) {
  std::random_device rand;
  ft::set<int>       m;
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
      m.insert(m.begin(), v[i]);
    } else if (choice == 1) {
      m.insert(m.end(), v[i]);
    } else if (choice == 2) {
      m.insert(m.upper_bound(v[i]), v[i]);
    } else if (choice == 3) {
      m.insert(m.lower_bound(v[i]), v[i]);
    }
  }

  ft::set<int>::iterator it  = m.begin();
  int                    num = *it;
  it++;
  for (; it != m.end(); it++) {
    EXPECT_EQ(num < *it, true);
  }
}

TEST(SetTest, rangeInsert) {
  ft::set<int>     m;
  std::vector<int> v(1000);
  for (size_t i = 0; i < 1000; i++) {
    v[i] = i;
  }
  m.insert(v.begin(), v.end());
  ft::set<int>::iterator it(m.begin());
  for (size_t i = 0; it != m.end(); it++) {
    EXPECT_EQ(*it, i);
    i++;
  }
}

TEST(SetTest, Erase) {
  ft::set<int> m;
  int          times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(i);
  }
  for (size_t i = 1; i <= times; i++) {
    m.erase(i);
    EXPECT_EQ(m.size(), times - i);
    EXPECT_EQ(m.count(i), 0);
  }
}

TEST(SetTest, positionErase) {
  ft::set<int> m;
  int          times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(i);
  }
  for (size_t i = 1; i <= times; i++) {
    m.erase(m.find(i));
    EXPECT_EQ(m.size(), times - i);
    EXPECT_EQ(m.count(i), 0);
  }
}

TEST(SetTest, rangeErase) {
  ft::set<int> m;
  int          times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(i);
  }
  m.erase(m.begin(), m.end());
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(SetTest, Swap) {
  ft::set<int> m;
  int          times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(i);
  }
  ft::set<int> n;
  for (size_t i = 1; i <= 1000; i++) {
    m.insert(4);
  }
  ft::set<int>::iterator m_it = m.begin();
  ft::set<int>::iterator n_it = n.begin();
  n.swap(m);
  EXPECT_EQ(n.size(), times);
  for (int i = 1; m_it != n.end(); m_it++) {
    EXPECT_EQ(*m_it, i);
    EXPECT_EQ(*m_it, i);
    i++;
  }
  for (int i = 1; n_it != m.end(); n_it++) {
    EXPECT_EQ(*n_it, i);
    EXPECT_EQ(*n_it, 42);
    i++;
  }
}

TEST(SetTest, Clear) {
  ft::set<int> m;
  int          times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(i);
  }
  m.clear();
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(SetTest, count) {
  ft::set<int> m;
  EXPECT_TRUE(m.count(0) == 0);
  m.insert(0);
  EXPECT_TRUE(m.count(0) == 1);
  m.insert(0);
  EXPECT_TRUE(m.count(0) == 1);
  EXPECT_TRUE(m.count(1) == 0);
}

TEST(SetTest, find) {
  ft::set<int> m;
  m.insert(1);
  m.insert(3);
  m.insert(2);
  ft::set<int>::iterator it = m.begin();

  EXPECT_EQ(m.find(0), m.end());
  EXPECT_NE(m.find(1), m.end());
  EXPECT_EQ(m.find(1), it++);
  EXPECT_NE(m.find(2), m.end());
  EXPECT_EQ(m.find(2), it++);
  EXPECT_NE(m.find(3), m.end());
  EXPECT_EQ(m.find(3), it);
  EXPECT_EQ(m.find(4), m.end());

  ft::set<int>::const_iterator cit = m.find(1);
  // cannot assign
  // cit->second = 57;
}

TEST(SetTest, equalRange) {
  ft::set<int> m;
  m.insert(1);
  m.insert(3);
  m.insert(2);
  m.insert(0);
  m.insert(6);

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

TEST(SetTest, lowerBound) {
  ft::set<int> m;
  m.insert(1);
  m.insert(3);
  m.insert(2);
  m.insert(0);
  m.insert(6);

  EXPECT_EQ(m.lower_bound(2), m.find(2));
  EXPECT_EQ(m.lower_bound(3), m.find(3));
  EXPECT_EQ(m.lower_bound(10), m.end());
}

TEST(SetTest, upperBound) {
  ft::set<int> m;
  m.insert(1);
  m.insert(3);
  m.insert(2);
  m.insert(0);
  m.insert(6);

  EXPECT_EQ(m.upper_bound(2), m.find(3));
  EXPECT_EQ(m.upper_bound(3), m.find(6));
  EXPECT_EQ(m.upper_bound(10), m.end());
}

TEST(SetTest, KeyCompare) {
  ft::set<int> m;

  ft::set<int>::key_compare kc = m.key_comp();

  EXPECT_EQ(kc(0, 1), true);
  EXPECT_EQ(kc(42, 0), false);
}

TEST(SetTest, ValueCompare) {
  ft::set<int> m;

  ft::set<int>::value_compare vc = m.value_comp();

  EXPECT_EQ(vc(0, 1), true);
  EXPECT_EQ(vc(42, 1), false);
}

TEST(SetTest, ComparisonOperators) {
  ft::set<int> m;
  m.insert(0);
  m.insert(1);
  m.insert(2);
  m.insert(3);

  ft::set<int> c(m);

  EXPECT_EQ(m == c, true);
  EXPECT_EQ(m != c, false);
  EXPECT_EQ(m < c, false);
  EXPECT_EQ(m > c, false);
  EXPECT_EQ(m <= c, true);
  EXPECT_EQ(m >= c, true);

  c.insert(4);
  EXPECT_EQ(m == c, false);
  EXPECT_EQ(m != c, true);
  EXPECT_EQ(m < c, true);
  EXPECT_EQ(m > c, false);
  EXPECT_EQ(m <= c, true);
  EXPECT_EQ(m >= c, false);

  m.insert(4);
  EXPECT_EQ(m == c, true);
  EXPECT_EQ(m != c, false);
  EXPECT_EQ(m < c, false);
  EXPECT_EQ(m > c, false);
  EXPECT_EQ(m <= c, true);
  EXPECT_EQ(m >= c, true);
}