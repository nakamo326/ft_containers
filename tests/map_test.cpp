
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
  std::vector<ft::pair<const int, int>> from;
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

TEST(MapTest, assignation) {
  ft::map<int, int> from;
  for (int i = 0; i < 10; i++) {
    from.insert(ft::make_pair(i, i));
  }
  ft::map<int, int> m;
  for (int i = 0; i < 5; i++) {
    from.insert(ft::make_pair(i, 42));
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
  ft::map<int, int> f;

  ft::map<int, int>::allocator_type a   = f.get_allocator();
  ft::map<int, int>::value_type*    val = a.allocate(1);
  val->second                           = 42;
  EXPECT_EQ(val->second, 42);
  a.deallocate(val, 1);
}

TEST(MapTest, arrayOperator) {
  ft::map<int, int> m;
  m[0] = 57;
  EXPECT_EQ(m[0], 57);
  EXPECT_EQ(m[42], int());
  m[0] = 42;
  EXPECT_EQ(m[0], 42);
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

TEST(MapTest, MaxSize) {
  std::map<int, int> s;
  ft::map<int, int>  f;
  EXPECT_EQ(s.max_size(), f.max_size());
}

TEST(MapTest, simpleInsert) {
  std::random_device rand;
  {
    ft::map<int, int> m;
    int               times = 10000;
    for (size_t i = 0; i < times; i++) {
      m.insert(ft::make_pair(i, i));
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
    ft::map<int, int> m;
    for (size_t i = 0; i < 10000; i++) {
      m.insert(ft::make_pair(v[i], v[i]));
      EXPECT_EQ(m.size(), i + 1);
    }
    ft::map<int, int>::iterator it = m.begin();
    for (size_t i = 0; i < 10000; i++) {
      EXPECT_EQ((*it).first, i);
      it++;
    }
  }
}

// lower_bound, upper_boundほしい
// TEST(MapTest, positionInsert) {
//   std::random_device rand;
//   {
//     tree_type            tree;
//     tree_type::size_type size  = 0;
//     int                  times = 10000;
//     for (size_t i = 0; i < times; i++) {
//       int tmp    = rand() % times;
//       int choice = rand() % 3;
//       if (choice == 0) {
//         tree.insert(tree.find(tmp), ft::make_pair(tmp, 0));
//       } else if (choice == 1) {
//         tree.insert(tree.begin(), ft::make_pair(tmp, 0));
//       } else {
//         tree.insert(tree.end(), ft::make_pair(tmp, 0));
//       }
//       EXPECT_EQ(tree.isValidTree(), true);
//     }
//   }
// }

TEST(MapTest, rangeInsert) {
  ft::map<int, int>               m;
  std::vector<ft::pair<int, int>> v(1000);
  for (size_t i = 0; i < 1000; i++) {
    v[i] = ft::make_pair(i, i);
  }
  m.insert(v.begin(), v.end());
  ft::map<int, int>::iterator it(m.begin());
  for (size_t i = 0; it != m.end(); it++) {
    EXPECT_EQ(it->first, i);
    i++;
  }
}

TEST(MapTest, Erase) {
  ft::map<int, int> m;
  int               times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(ft::make_pair(i, i));
  }
  for (size_t i = 1; i <= times; i++) {
    m.erase(i);
    EXPECT_EQ(m.size(), times - i);
    EXPECT_EQ(m.count(i), 0);
  }
}

TEST(MapTest, positionErase) {
  ft::map<int, int> m;
  int               times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(ft::make_pair(i, i));
  }
  for (size_t i = 1; i <= times; i++) {
    m.erase(m.find(i));
    EXPECT_EQ(m.size(), times - i);
    EXPECT_EQ(m.count(i), 0);
  }
}

TEST(MapTest, rangeErase) {
  ft::map<int, int> m;
  int               times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(ft::make_pair(i, i));
  }
  m.erase(m.begin(), m.end());
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, Swap) {
  ft::map<int, int> m;
  int               times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(ft::make_pair(i, i));
  }
  ft::map<int, int> n;
  for (size_t i = 1; i <= 1000; i++) {
    m.insert(ft::make_pair(i, 42));
  }
  ft::map<int, int>::iterator m_it = m.begin();
  ft::map<int, int>::iterator n_it = n.begin();
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
  ft::map<int, int> m;
  int               times = 10000;
  for (size_t i = 1; i <= times; i++) {
    m.insert(ft::make_pair(i, i));
  }
  m.clear();
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.begin(), m.end());
}

TEST(MapTest, count) {
  ft::map<int, int> m;
  EXPECT_TRUE(m.count(0) == 0);
  m.insert(ft::make_pair(0, 42));
  EXPECT_TRUE(m.count(0) == 1);
  EXPECT_TRUE(m.count(1) == 0);
}

TEST(MapTest, KeyCompare) {
  ft::map<int, int> m;

  ft::map<int, int>::key_compare kc = m.key_comp();

  EXPECT_EQ(kc(0, 1), true);
  EXPECT_EQ(kc(42, 0), false);
}

TEST(MapTest, ValueCompare) {
  ft::map<int, int> m;

  ft::map<int, int>::value_compare vc = m.value_comp();

  EXPECT_EQ(vc(ft::make_pair(0, 0), ft::make_pair(1, 0)), true);
  EXPECT_EQ(vc(ft::make_pair(42, 0), ft::make_pair(1, 0)), false);
}