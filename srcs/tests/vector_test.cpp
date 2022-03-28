#include "vector.hpp"

#include "switch.hpp"

#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "testframe/testframe.hpp"
#endif

#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

class TestClass {
public:
  int* p;
  TestClass() { p = new int; }
  TestClass(int num) {
    p  = new int;
    *p = num;
  }
  TestClass(const TestClass& other) {
    p  = new int;
    *p = *(other.p);
  }
  ~TestClass() { delete p; }
  TestClass& operator=(const TestClass& other) {
    *p = *(other.p);
    return *this;
  }
};

TEST(VectorConstructorTest, DefaultConstructor) {
  LIB::vector<int> v;

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorConstructorTest, ConstructorWithAllocator) {
  std::allocator<int> alloc;
  LIB::vector<int>    v(alloc);
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.get_allocator(), alloc);
}

TEST(VectorConstructorTest, ConstructorWithSize) {
  LIB::vector<int> v(100);

  EXPECT_EQ(v.size(), 100);
  EXPECT_EQ(v.capacity(), 100);
  EXPECT_EQ(v.get_allocator(), std::allocator<int>());
}

TEST(VectorConstructorTest, ConstructorWithValue) {
  LIB::vector<int> v(1000, 55);

  EXPECT_EQ(v.size(), 1000);
  EXPECT_EQ(v.capacity(), 1000);
  EXPECT_EQ(v.get_allocator(), std::allocator<int>());
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], 55);
  }
}

TEST(VectorConstructorTest, RangeConstructor) {
  std::vector<int> s(1000);
  for (size_t i = 0; i < 1000; i++) {
    s[i] = i;
  }

  LIB::vector<int> f(s.begin(), s.end());

  EXPECT_EQ(f.size(), 1000);
  EXPECT_EQ(f.capacity(), 1000);
  EXPECT_EQ(f.get_allocator(), std::allocator<int>());
  for (size_t i = 0; i < f.size(); i++) {
    EXPECT_EQ(f[i], i);
  }
}

TEST(VectorConstructorTest, CopyConstructor) {
  LIB::vector<int> f(1000);
  for (size_t i = 0; i < 1000; i++) {
    f[i] = i;
  }
  LIB::vector<int> c(f);

  EXPECT_EQ(c.size(), 1000);
  EXPECT_EQ(c.capacity(), 1000);
  EXPECT_EQ(c.get_allocator(), std::allocator<int>());
  for (size_t i = 0; i < c.size(); i++) {
    EXPECT_EQ(c[i], i);
  }
}

TEST(VectorTest, AssignationOverload) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  // big to small
  {
    LIB::vector<int> c(100);
    c = v;
    EXPECT_EQ(c.size(), v.size());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(c[i], v[i]);
    }
  }
  // small to big
  {
    LIB::vector<int> c(10000);
    c = v;
    EXPECT_EQ(c.size(), v.size());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(c[i], v[i]);
    }
  }
}

TEST(VectorTest, GetAllocator) {
  LIB::vector<int> v;
  EXPECT_EQ(v.get_allocator(), std::allocator<int>());
}

TEST(VectorTest, AssignFunc) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }

  // big to small
  {
    v.assign(10000, 50);
    EXPECT_EQ(v.size(), 10000);
    EXPECT_EQ(v.capacity(), 10000);
    for (size_t i = 0; i < 10000; i++) {
      EXPECT_EQ(v[i], 50);
    }
  }

  // small to big
  {
    v.assign(100, 50);
    EXPECT_EQ(v.size(), 100);
    EXPECT_EQ(v.capacity(), 10000);
    for (size_t i = 0; i < 100; i++) {
      EXPECT_EQ(v[i], 50);
    }
  }
}

TEST(VectorTest, AssignFuncIter) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(42);
  }

  // big to small
  {
    LIB::vector<int> src(10000);
    for (size_t i = 0; i < 10000; i++) {
      src[i] = i;
    }
    v.assign(src.begin(), src.end());
    EXPECT_EQ(v.size(), 10000);
    for (size_t i = 0; i < 10000; i++) {
      EXPECT_EQ(v[i], i);
    }
  }
  // small to big
  {
    LIB::vector<int> src(100);
    for (size_t i = 0; i < 100; i++) {
      src[i] = i;
    }
    v.assign(src.begin(), src.end());
    EXPECT_EQ(v.size(), 100);
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(v[i], i);
    }
  }
}

TEST(VectorTest, AssignFuncInputIteratorCheck) {
  std::stringstream ss;
  ss << 1 << std::endl << 2 << std::endl << 3;
  std::istream_iterator<int> beg(ss);
  std::istream_iterator<int> last;

  LIB::vector<int> v;
  v.assign(beg, last);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  std::vector<int> tmp(5);
  for (size_t i = 0; i < 5; i++) {
    tmp[i] = i;
  }

  v.assign(tmp.begin(), tmp.end());
  int i = 0;
  for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    EXPECT_EQ(*it, i);
    i++;
  }
}

TEST(VectorTest, Destructor) {
  LIB::vector<int>* f = new LIB::vector<int>(1000);
  for (size_t i = 0; i < 1000; i++) {
    (*f)[i] = i;
  }
  delete f;
}

TEST(VectorTest, At) {
  LIB::vector<int> v(1000);
  for (size_t i = 0; i < 1000; i++) {
    v[i] = i;
  }

  for (size_t i = 0; i < 1000; i++) {
    EXPECT_EQ(v.at(i), i);
  }
  v.at(5) = 42;
  EXPECT_EQ(v.at(5), 42);
  EXPECT_THROW(v.at(v.size()), std::out_of_range);
}

TEST(VectorTest, Front) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  EXPECT_EQ(v.front(), 0);
  v.front() = 42;
  EXPECT_EQ(v.front(), 42);
}

TEST(VectorTest, Back) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  EXPECT_EQ(v.back(), 999);
  v.back() = 42;
  EXPECT_EQ(v.back(), 42);
}

TEST(VectorTest, Reserve) {
  LIB::vector<int> v;
  v.reserve(1000);
  EXPECT_EQ(v.capacity(), 1000);
  v.reserve(10000);
  EXPECT_EQ(v.capacity(), 10000);
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10000);
  EXPECT_THROW(v.reserve(v.max_size() + 1), std::length_error);
}

TEST(VectorTest, BeginAndEnd) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  LIB::vector<int>::iterator it = v.begin();

  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
  LIB::vector<int>::iterator end = v.end();
  EXPECT_EQ(it, end);
}

TEST(VectorTest, Pushback) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 100000; i++) {
    v.push_back(i);
    EXPECT_EQ(v[i], i);
    EXPECT_EQ(v.size(), i + 1);
  }
}

TEST(VectorTest, Clear) {
  LIB::vector<TestClass> v(10);
  v.clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorTest, InsertWithValue) {
  LIB::vector<int> v;
  for (int i = 0; i < 1000; i++) {
    v.insert(v.begin(), i);
    EXPECT_EQ(v[0], i);
    EXPECT_EQ(v.size(), i + 1);
  }
}

TEST(VectorTest, InsertWithCount) {
  LIB::vector<int> v;

  v.insert(v.begin(), 1000, 42);
  v.insert(v.begin() + 500, 1000, 57);
  for (size_t i = 0; i < 500; i++) {
    EXPECT_EQ(v[i], 42);
  }
  for (size_t i = 500; i < 1500; i++) {
    EXPECT_EQ(v[i], 57);
  }
  for (size_t i = 1500; i < 2000; i++) {
    EXPECT_EQ(v[i], 42);
  }
}

TEST(VectorTest, InsertWithIter) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  LIB::vector<int> input(10000);
  for (size_t i = 0; i < 10000; i++) {
    input[i] = i;
  }
  v.insert(v.begin() + 500, input.begin(), input.end());
  EXPECT_EQ(v.size(), 11000);
  for (size_t i = 0; i < 500; i++) {
    EXPECT_EQ(v[i], i);
  }
  for (size_t i = 0; i < 10000; i++) {
    EXPECT_EQ(v[i + 500], i);
  }
  for (size_t i = 0; i < 500; i++) {
    EXPECT_EQ(v[i + 10500], i + 500);
  }
}

TEST(VectorTest, EraseOne) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  LIB::vector<int>::iterator ret = v.erase(v.begin() + 50);
  EXPECT_EQ(*ret, 51);
  EXPECT_EQ(v.size(), 999);
  for (size_t i = 0; i < 999; i++) {
    if (i < 50) {
      EXPECT_EQ(v[i], i);
    } else if (i >= 50) {
      EXPECT_EQ(v[i], i + 1);
    }
  }
  ret = v.erase(v.end() - 1);
  EXPECT_EQ(ret, v.end());
  EXPECT_EQ(v.size(), 998);

  // leak check
  LIB::vector<TestClass> tv(10);
  for (size_t i = 0; i < 10; i++) {
    tv.erase(tv.begin());
  }
}

TEST(VectorTest, EraseIter) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  LIB::vector<int>::iterator ret = v.erase(v.begin() + 50, v.begin() + 60);
  EXPECT_EQ(*ret, 60);
  EXPECT_EQ(v.size(), 990);

  for (size_t i = 0; i < v.size(); i++) {
    if (i < 50) {
      EXPECT_EQ(v[i], i);
    } else if (i >= 60) {
      EXPECT_EQ(v[i], i + 10);
    }
  }

  ret = v.erase(v.begin() + 80, v.end());
  EXPECT_EQ(ret, v.end());
  EXPECT_EQ(v.size(), 80);
  for (size_t i = 0; i < v.size(); i++) {
    if (i < 50) {
      EXPECT_EQ(v[i], i);
    } else if (i >= 60) {
      EXPECT_EQ(v[i], i + 10);
    }
  }

  // leak check
  LIB::vector<TestClass> t(10);
  t.erase(t.begin(), t.begin() + 5);
  t.erase(t.begin(), t.begin() + 5);
}

TEST(VectorTest, PopBack) {
  LIB::vector<int> s;
  for (size_t i = 0; i < 1000; i++) {
    s.push_back(i);
  }
  for (size_t i = 0; i < 100; i++) {
    s.pop_back();
    EXPECT_EQ(s.size(), 1000 - (i + 1));
    for (size_t j = 0; j < s.size(); j++) {
      EXPECT_EQ(s[j], j);
    }
  }
  LIB::vector<TestClass> v(10);
  for (size_t i = 0; i < 10; i++) {
    v.pop_back();
  }
}

TEST(VectorTest, Resize) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  v.resize(100, 42);
  EXPECT_EQ(v.size(), 100);
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], i);
  }
  v.resize(0, 3);
  EXPECT_EQ(v.size(), 0);
  v.resize(200, 3);
  EXPECT_EQ(v.size(), 200);
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], 3);
  }
}

TEST(VectorTest, Swap) {
  LIB::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  LIB::vector<int> ts;
  for (size_t i = 0; i < 50; i++) {
    ts.push_back(50 - i);
  }
  v.swap(ts);
  EXPECT_EQ(v.size(), 50);
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], 50 - i);
  }
  LIB::swap(v, ts);
  EXPECT_EQ(v.size(), 1000);
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], i);
  }

  LIB::vector<int>::iterator it = v.begin();
  LIB::swap(v, ts);
  for (int i = 0; it != ts.end(); it++) {
    EXPECT_EQ(*it, i);
    i++;
  }

  EXPECT_EQ(it, ts.end());
}

TEST(VectorTest, Comparison) {
  LIB::vector<int> s;
  for (size_t i = 0; i < 1000; i++) {
    s.push_back(i);
  }
  LIB::vector<int> cs = s;
  EXPECT_EQ(cs == s, true);
  EXPECT_EQ(s == cs, true);
  EXPECT_EQ(cs != s, false);
  EXPECT_EQ(s != cs, false);
  EXPECT_EQ(cs <= s, true);
  EXPECT_EQ(s <= cs, true);
  EXPECT_EQ(cs >= s, true);
  EXPECT_EQ(s >= cs, true);
  EXPECT_EQ(cs > s, false);
  EXPECT_EQ(s > cs, false);
  EXPECT_EQ(cs < s, false);
  EXPECT_EQ(s < cs, false);
  cs.push_back(42);
  EXPECT_EQ(cs == s, false);
  EXPECT_EQ(s == cs, false);
  EXPECT_EQ(cs != s, true);
  EXPECT_EQ(s != cs, true);
  EXPECT_EQ(cs <= s, false);
  EXPECT_EQ(s <= cs, true);
  EXPECT_EQ(cs >= s, true);
  EXPECT_EQ(s >= cs, false);
  EXPECT_EQ(cs > s, true);
  EXPECT_EQ(s > cs, false);
  EXPECT_EQ(cs < s, false);
  EXPECT_EQ(s < cs, true);
}

TEST(VectorTest, Iterator) {
  LIB::vector<int> v(10);
  for (size_t i = 0; i < 10; i++) {
    v[i] = i;
  }
  LIB::vector<int>::iterator       it = v.begin();
  LIB::vector<int>::iterator       it2(it);
  LIB::vector<int>::const_iterator cit = v.begin();
  EXPECT_EQ((it == it2), true);
  EXPECT_EQ((it == cit), true);
  EXPECT_EQ((cit == it), true);
  EXPECT_EQ((it != it2), false);
  EXPECT_EQ((it != cit), false);
  EXPECT_EQ((it <= it2), true);
  EXPECT_EQ((it <= cit), true);
  EXPECT_EQ((it >= it2), true);
  EXPECT_EQ((it >= cit), true);
  EXPECT_EQ((it < it2), false);
  EXPECT_EQ((it < cit), false);
  EXPECT_EQ((it > it2), false);
  EXPECT_EQ((it > cit), false);
  cit++;
  it2++;
  EXPECT_EQ((it == it2), false);
  EXPECT_EQ((it == cit), false);
  EXPECT_EQ((it != it2), true);
  EXPECT_EQ((it != cit), true);
  EXPECT_EQ((it <= it2), true);
  EXPECT_EQ((it <= cit), true);
  EXPECT_EQ((it >= it2), false);
  EXPECT_EQ((it >= cit), false);
  EXPECT_EQ((it < it2), true);
  EXPECT_EQ((it < cit), true);
  EXPECT_EQ((it > it2), false);
  EXPECT_EQ((it > cit), false);
  cit += 9;
  it2 += 9;
  EXPECT_EQ(true, (it2 == v.end()));
  EXPECT_EQ(true, (cit == v.end()));
  EXPECT_EQ((v.end() - v.begin()), 10);
}

TEST(VectorTest, ReverseIterator) {
  LIB::vector<int> v(10);
  for (size_t i = 0; i < 10; i++) {
    v[i] = i;
  }
  LIB::vector<int>::reverse_iterator       it = v.rbegin();
  LIB::vector<int>::reverse_iterator       it2(it);
  LIB::vector<int>::const_reverse_iterator cit = v.rbegin();
  EXPECT_EQ((it == it2), true);
  EXPECT_EQ((it == cit), true);
  EXPECT_EQ((cit == it), true);
  EXPECT_EQ((it != it2), false);
  EXPECT_EQ((it != cit), false);
  EXPECT_EQ((it <= it2), true);
  EXPECT_EQ((it <= cit), true);
  EXPECT_EQ((it >= it2), true);
  EXPECT_EQ((it >= cit), true);
  EXPECT_EQ((it < it2), false);
  EXPECT_EQ((it < cit), false);
  EXPECT_EQ((it > it2), false);
  EXPECT_EQ((it > cit), false);
  cit++;
  it2++;
  EXPECT_EQ((it == it2), false);
  EXPECT_EQ((it == cit), false);
  EXPECT_EQ((it != it2), true);
  EXPECT_EQ((it != cit), true);
  EXPECT_EQ((it <= it2), true);
  EXPECT_EQ((it <= cit), true);
  EXPECT_EQ((it >= it2), false);
  EXPECT_EQ((it >= cit), false);
  EXPECT_EQ((it < it2), true);
  EXPECT_EQ((it < cit), true);
  EXPECT_EQ((it > it2), false);
  EXPECT_EQ((it > cit), false);
  cit += 9;
  it2 += 9;
  EXPECT_EQ(true, (it2 == v.rend()));
  EXPECT_EQ(true, (cit == v.rend()));
  EXPECT_EQ((v.rend() - v.rbegin()), 10);

  LIB::vector<int> tmp(100);
  for (size_t i = 0; i < 100; i++) {
    tmp.push_back(i);
  }
  LIB::vector<int>::reverse_iterator rit = tmp.rbegin();
  for (size_t i = 0; i < 100; i++) {
    EXPECT_EQ(*rit, 99 - i);
    rit++;
  }
}

TEST(VectorTest, const_iterator) {
  LIB::vector<int> s(10);
  for (size_t i = 0; i < 10; i++) {
    s[i] = i;
  }
  LIB::vector<int>::iterator       it       = s.begin();
  LIB::vector<int>::const_iterator const_it = it;

  // cannot assign to const_it;
  // *const_it = 42;

  for (size_t i = 0; i < 10; i++) {
    EXPECT_EQ(*it, *const_it);
    it++;
    const_it++;
  }
}
