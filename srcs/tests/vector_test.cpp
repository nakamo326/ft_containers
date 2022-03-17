#include "vector.hpp"

#include <gtest/gtest.h>

#include <typeinfo>
#include <vector>

class TestClass {
public:
  int* p;
  TestClass() {
    // std::cout << __func__ << std::endl;
    p = new int;
  }
  TestClass(int num) {
    // std::cout << __func__ << std::endl;
    p  = new int;
    *p = num;
  }
  TestClass(const TestClass& other) {
    // std::cout << __func__ << std::endl;
    p  = new int;
    *p = *(other.p);
  }
  ~TestClass() {
    // std::cout << __func__ << std::endl;

    delete p;
  }
  TestClass& operator=(const TestClass& other) {
    // std::cout << __func__ << std::endl;
    *p = *(other.p);
    return *this;
  }
};

TEST(VectorHelperTest, vallocate) {
  ft::vector<int> v;
  // EXPECT_THROW(v.vallocate(v.max_size()), std::bad_alloc);
  EXPECT_THROW(v.vallocate(v.max_size() + 1), std::length_error);
  v.vallocate(100);
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 100);
}

TEST(VectorHelperTest, vdeallocate) {
  ft::vector<int> v;
  v.vallocate(100);
  v.vdeallocate();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  v.vdeallocate();
}

TEST(VectorConstructorTest, DefaultConstructor) {
  std::vector<int> s;
  ft::vector<int>  f;
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}

TEST(VectorConstructorTest, ConstructorWithAllocator) {
  std::allocator<int> alloc;
  std::vector<int>    s(alloc);
  ft::vector<int>     f(alloc);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}

TEST(VectorConstructorTest, ConstructorWithSize) {
  std::vector<int> s(100);
  ft::vector<int>  f(100);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}

TEST(VectorConstructorTest, ConstructorWithValue) {
  std::vector<int> s(1000, 55);
  ft::vector<int>  f(1000, 55);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
  for (size_t i = 0; i < 1000; i++) {
    EXPECT_EQ(s[i], f[i]);
  }
}

TEST(VectorConstructorTest, RangeConstructor) {
  std::vector<int> s(1000);
  for (size_t i = 0; i < 1000; i++) {
    s[i] = i;
  }
  ft::vector<int> f(s.begin(), s.end());
  EXPECT_EQ(f.max_size(), s.max_size());
  EXPECT_EQ(f.get_allocator(), s.get_allocator());
  for (size_t i = 0; i < 1000; i++) {
    EXPECT_EQ(f[i], s[i]);
  }
}

TEST(VectorConstructorTest, CopyConstructor) {
  ft::vector<int> f(1000);
  for (size_t i = 0; i < 1000; i++) {
    f[i] = i;
  }
  ft::vector<int> c(f);
  EXPECT_EQ(f.size(), c.size());
  EXPECT_EQ(f.max_size(), c.max_size());
  EXPECT_EQ(f.capacity(), c.capacity());
  EXPECT_EQ(f.get_allocator(), c.get_allocator());
  for (size_t i = 0; i < 1000; i++) {
    EXPECT_EQ(f[i], c[i]);
  }
}

TEST(VectorTest, AssignationOverload) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  // big to small
  {
    ft::vector<int>  cf(100);
    std::vector<int> cs(100);
    cf = f;
    cs = s;
    EXPECT_EQ(s.size(), f.size());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(cf[i], cs[i]);
    }
  }
  // small to big
  {
    ft::vector<int>  cf(10000);
    std::vector<int> cs(10000);
    cf = f;
    cs = s;
    EXPECT_EQ(s.size(), f.size());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(cf[i], cs[i]);
    }
  }
}

TEST(VectorTest, GetAllocator) {
  std::vector<int> s;
  ft::vector<int>  f;
  EXPECT_EQ(typeid(s.get_allocator()).name(), typeid(f.get_allocator()).name());
}

TEST(VectorTest, AssignFunc) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  // big to small
  {
    s.assign(10000, 50);
    f.assign(10000, 50);
    EXPECT_EQ(s.size(), f.size());
    for (size_t i = 0; i < 10000; i++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }

  // small to big
  {
    s.assign(100, 50);
    f.assign(100, 50);
    EXPECT_EQ(s.size(), f.size());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }
}

TEST(VectorTest, AssignFuncIter) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  // big to small
  {
    std::vector<int> src(10000);
    for (size_t i = 0; i < 10000; i++) {
      src[i] = i;
    }
    s.assign(src.begin(), src.end());
    f.assign(src.begin(), src.end());
    EXPECT_EQ(s.size(), f.size());
    for (size_t i = 0; i < 10000; i++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }
  // small to big
  {
    std::vector<int> src(100);
    for (size_t i = 0; i < 100; i++) {
      src[i] = i;
    }
    s.assign(src.begin(), src.end());
    f.assign(src.begin(), src.end());
    EXPECT_EQ(s.size(), f.size());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }
}

// TEST(VectorTest, AssignFuncInputIteratorCheck) {
//   std::stringstream ss;
//   ss << 1 << std::endl << 2 << std::endl << 3;
//   std::istream_iterator<int> beg(ss);
//   std::istream_iterator<int> last;

//   ft::vector<int> v;
//   v.assign(beg, last);
//   EXPECT_EQ(v[0], 1);
//   EXPECT_EQ(v[1], 2);
//   EXPECT_EQ(v[2], 3);

//   std::vector<int> tmp(5);
//   for (size_t i = 0; i < 5; i++) {
//     tmp[i] = i;
//   }

//   v.assign(tmp.begin(), tmp.end());
//   int i = 0;
//   for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//     EXPECT_EQ(*it, i);
//     i++;
//   }
// }

TEST(VectorTest, Destructor) {
  ft::vector<int>* f = new ft::vector<int>(1000);
  for (size_t i = 0; i < 1000; i++) {
    (*f)[i] = i;
  }
  delete f;
}

TEST(VectorTest, At) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  s[5] = 10;
  f[5] = 10;
  EXPECT_EQ(s.at(0), f.at(0));
  EXPECT_EQ(s.at(5), f.at(5));
  s.at(5) = 42;
  f.at(5) = 42;
  EXPECT_EQ(s.at(0), f.at(0));
  EXPECT_EQ(s.at(5), f.at(5));
  EXPECT_EQ(s.at(5), 42);
  EXPECT_EQ(f.at(5), 42);
  EXPECT_THROW(s.at(s.size()), std::out_of_range);
  EXPECT_THROW(f.at(f.size()), std::out_of_range);
}

TEST(VectorTest, Front) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  EXPECT_EQ(s.front(), f.front());
  s.front() = 42;
  f.front() = 42;
  EXPECT_EQ(s.front(), f.front());
  EXPECT_EQ(s.front(), 42);
  EXPECT_EQ(f.front(), 42);
}

TEST(VectorTest, Back) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  EXPECT_EQ(s.back(), f.back());
  s.back() = 42;
  f.back() = 42;
  EXPECT_EQ(s.back(), f.back());
  EXPECT_EQ(s.back(), 42);
  EXPECT_EQ(f.back(), 42);
}

TEST(VectorTest, Reserve) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  s.reserve(1000);
  f.reserve(1000);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_THROW(s.reserve(s.max_size() + 1), std::length_error);
  EXPECT_THROW(f.reserve(f.max_size() + 1), std::length_error);
}

TEST(VectorTest, BeginAndEnd) {
  std::vector<int> s;
  ft::vector<int>  f;
  for (size_t i = 0; i < 1000; i++) {
    f.push_back(i);
    s.push_back(i);
  }
  auto sit = s.begin();
  auto fit = f.begin();

  EXPECT_EQ(*sit, *fit);

  for (size_t i = 0; i < s.size(); i++) {
    sit++;
    fit++;
  }
  auto send = s.end();
  auto fend = f.end();
  EXPECT_EQ(sit, send);
  EXPECT_EQ(fit, fend);
}

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
  for (size_t i = 0; i < 1000; i++) {
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
  auto sret = s.erase(s.begin() + 50);
  auto fret = f.erase(f.begin() + 50);
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
  auto sret = s.erase(s.begin() + 50, s.begin() + 60);
  auto fret = f.erase(f.begin() + 50, f.begin() + 60);
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
