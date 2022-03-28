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

/*
TEST(VectorTest, Pushback) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 100000; i++) {
    s.push_back(i);
    f.push_back(i);
    EXPECT_EQ(s[i], f[i]);
    EXPECT_EQ(s.size(), f.size());
    EXPECT_EQ(s.capacity(), f.capacity());
  }
}

TEST(VectorTest, Clear) {
  std::vector<TestClass> s(10);
  ft::vector<TestClass>  f(10);
  s.clear();
  f.clear();
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
}

TEST(VectorTest, InsertWithValue) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  std::vector<int> ts;
  ft::vector<int>  tf;
  for (int i = 0; i < 1000; i++) {
    ts.insert(ts.begin(), i);
    tf.insert(tf.begin(), i);
    EXPECT_EQ(ts[0], i);
    EXPECT_EQ(tf[0], i);
    EXPECT_EQ(ts.size(), tf.size());
    EXPECT_EQ(ts.capacity(), tf.capacity());
  }
}

TEST(VectorTest, InsertWithCount) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  s.insert(s.begin(), 1000, 42);
  f.insert(f.begin(), 1000, 42);
  s.insert(s.begin() + 5, 4000, 57);
  f.insert(f.begin() + 5, 4000, 57);
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
}

TEST(VectorTest, InsertWithIter) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  std::vector<int> input(10000);
  for (size_t i = 0; i < 10000; i++) {
    input[i] = i;
  }
  s.insert(s.begin() + 500, input.begin(), input.end());
  f.insert(f.begin() + 500, input.begin(), input.end());
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
}

TEST(VectorTest, EraseOne) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  std::vector<int>::iterator sret = s.erase(s.begin() + 50);
  ft::vector<int>::iterator  fret = f.erase(f.begin() + 50);
  EXPECT_EQ(*sret, *fret);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
  sret = s.erase(s.end() - 1);
  fret = f.erase(f.end() - 1);
  EXPECT_EQ(sret, s.end());
  EXPECT_EQ(fret, f.end());
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
  // leak check
  ft::vector<TestClass> v(10);
  for (size_t i = 0; i < 10; i++) {
    v.erase(v.begin());
  }
}

TEST(VectorTest, EraseIter) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  std::vector<int>::iterator sret = s.erase(s.begin() + 50, s.begin() + 60);
  ft::vector<int>::iterator  fret = f.erase(f.begin() + 50, f.begin() + 60);
  EXPECT_EQ(*sret, *fret);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
  sret = s.erase(s.begin() + 80, s.end());
  fret = f.erase(f.begin() + 80, f.end());
  EXPECT_EQ(sret, s.end());
  EXPECT_EQ(fret, f.end());
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
  // leak check
  ft::vector<TestClass> v(10);
  v.erase(v.begin(), v.begin() + 5);
  v.erase(v.begin(), v.begin() + 5);
}

TEST(VectorTest, PopBack) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  for (size_t i = 0; i < 100; i++) {
    s.pop_back();
    f.pop_back();
    EXPECT_EQ(s.size(), f.size());
    EXPECT_EQ(s.capacity(), f.capacity());
    for (size_t j = 0; j < s.size(); j++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }
  ft::vector<TestClass> v(10);
  for (size_t i = 0; i < 10; i++) {
    v.pop_back();
  }
}

TEST(VectorTest, Resize) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  s.resize(100, 42);
  f.resize(100, 42);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
  s.resize(0, 3);
  f.resize(0, 3);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
  s.resize(200, 3);
  f.resize(200, 3);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
}

TEST(VectorTest, Swap) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  std::vector<int> ts(50);
  ft::vector<int>  tf(50);
  for (size_t i = 0; i < 50; i++) {
    s[i] = 50 - i;
    f[i] = 50 - i;
  }
  s.swap(ts);
  f.swap(tf);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
  std::swap(s, ts);
  ft::swap(f, tf);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
  // FIXME: check with iterator
  ft::vector<int>::iterator f_it  = f.begin();
  ft::vector<int>::iterator tf_it = tf.begin();
  ft::swap(f, tf);
  std::swap(s, ts);
  std::vector<int>::iterator s_it  = s.begin();
  std::vector<int>::iterator ts_it = ts.begin();

  for (; f_it != tf.end(); f_it++) {
    EXPECT_EQ(*ts_it, *f_it);
    ts_it++;
  }
  EXPECT_EQ(ts_it, ts.end());
  for (; tf_it != f.end(); tf_it++) {
    EXPECT_EQ(*s_it, *tf_it);
    s_it++;
  }
  EXPECT_EQ(s_it, s.end());
}

TEST(VectorTest, Comparison) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  ft::vector<int>  cf = f;
  std::vector<int> cs = s;
  EXPECT_EQ(cf, f);
  EXPECT_EQ(f, cf);
  EXPECT_EQ(cs == s, cf == f);
  EXPECT_EQ(s == cs, f == cf);
  EXPECT_EQ(cs != s, cf != f);
  EXPECT_EQ(s != cs, f != cf);
  EXPECT_EQ(cs <= s, cf <= f);
  EXPECT_EQ(s <= cs, f <= cf);
  EXPECT_EQ(cs >= s, cf >= f);
  EXPECT_EQ(s >= cs, f >= cf);
  EXPECT_EQ(cs > s, cf > f);
  EXPECT_EQ(s > cs, f > cf);
  EXPECT_EQ(cs < s, cf < f);
  EXPECT_EQ(s < cs, f < cf);
  cf.push_back(42);
  cs.push_back(42);
  EXPECT_EQ(cs == s, cf == f);
  EXPECT_EQ(s == cs, f == cf);
  EXPECT_EQ(cs != s, cf != f);
  EXPECT_EQ(s != cs, f != cf);
  EXPECT_EQ(cs <= s, cf <= f);
  EXPECT_EQ(s <= cs, f <= cf);
  EXPECT_EQ(cs >= s, cf >= f);
  EXPECT_EQ(s >= cs, f >= cf);
  EXPECT_EQ(cs > s, cf > f);
  EXPECT_EQ(s > cs, f > cf);
  EXPECT_EQ(cs < s, cf < f);
  EXPECT_EQ(s < cs, f < cf);
}
*/
