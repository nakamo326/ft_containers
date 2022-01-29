#include "vector.hpp"

#include <gtest/gtest.h>

#include <typeinfo>
#include <vector>

class VectorTest : public ::testing::Test {
protected:
  std::vector<int> s;
  ft::vector<int>  f;

  virtual void     SetUp() {
    for (size_t i = 0; i < 1000; i++) {
      f.push_back(i);
      s.push_back(i);
    }
  }
};

TEST(VectorConstructorTest, DefaultConstructor) {
  std::vector<int> s;
  ft::vector<int>  f;
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.data(), f.data());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}

TEST(VectorConstructorTest, ConstructorWithAllocator) {
  std::allocator<int> alloc;
  std::vector<int>    s(alloc);
  ft::vector<int>     f(alloc);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.data(), f.data());
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
  EXPECT_EQ(f.size(), s.size());
  EXPECT_EQ(f.max_size(), s.max_size());
  EXPECT_EQ(f.capacity(), s.capacity());
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

TEST_F(VectorTest, AssignationOverload) {
  // big to small
  {
    ft::vector<int>  cf(100);
    std::vector<int> cs(100);
    cf = f;
    cs = s;
    EXPECT_EQ(cf.size(), cs.size());
    EXPECT_EQ(cf.max_size(), cs.max_size());
    EXPECT_EQ(cf.capacity(), cs.capacity());
    EXPECT_EQ(cf.get_allocator(), cs.get_allocator());
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
    EXPECT_EQ(cf.size(), cs.size());
    EXPECT_EQ(cf.capacity(), cs.capacity());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(cf[i], cs[i]);
    }
  }
}

TEST_F(VectorTest, AssignFunc) {
  // big to small
  {
    s.assign(10000, 50);
    f.assign(10000, 50);
    EXPECT_EQ(s.size(), f.size());
    EXPECT_EQ(s.max_size(), f.max_size());
    EXPECT_EQ(s.capacity(), f.capacity());
    EXPECT_EQ(s.get_allocator(), f.get_allocator());
    for (size_t i = 0; i < 10000; i++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }

  // small to big
  {
    s.assign(100, 50);
    f.assign(100, 50);
    EXPECT_EQ(s.size(), f.size());
    EXPECT_EQ(s.max_size(), f.max_size());
    EXPECT_EQ(s.capacity(), f.capacity());
    EXPECT_EQ(s.get_allocator(), f.get_allocator());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }
}

TEST_F(VectorTest, GetAllocator) {
  EXPECT_EQ(typeid(s.get_allocator()).name(), typeid(f.get_allocator()).name());
}

TEST_F(VectorTest, AssignFuncIter) {
  // big to small
  {
    std::vector<int> src(10000);
    for (size_t i = 0; i < 10000; i++) {
      src[i] = i;
    }
    s.assign(src.begin(), src.end());
    f.assign(src.begin(), src.end());
    EXPECT_EQ(s.size(), f.size());
    EXPECT_EQ(s.max_size(), f.max_size());
    EXPECT_EQ(s.capacity(), f.capacity());
    EXPECT_EQ(s.get_allocator(), f.get_allocator());
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
    EXPECT_EQ(s.max_size(), f.max_size());
    EXPECT_EQ(s.capacity(), f.capacity());
    EXPECT_EQ(s.get_allocator(), f.get_allocator());
    for (size_t i = 0; i < 1000; i++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }
}

TEST_F(VectorTest, Destructor) {
  ft::vector<int> *f = new ft::vector<int>(1000);
  for (size_t i = 0; i < 1000; i++) {
    (*f)[i] = i;
  }
  delete f;
}

TEST_F(VectorTest, At) {
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

TEST_F(VectorTest, BeginAndEnd) {
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

TEST_F(VectorTest, Pushback) {
  for (size_t i = 0; i < 100000; i++) {
    s.push_back(i);
    f.push_back(i);
    EXPECT_EQ(s[i], f[i]);
    EXPECT_EQ(s.size(), f.size());
    EXPECT_EQ(s.capacity(), f.capacity());
  }
}

TEST_F(VectorTest, Clear) {}

TEST_F(VectorTest, InsertWithValue) {
  s.insert(s.begin() + 5, 42);
  f.insert(f.begin() + 5, 42);
  EXPECT_EQ(s[5], 42);
  EXPECT_EQ(f[5], 42);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  s.insert(s.end(), 42);
  f.insert(f.end(), 42);
  EXPECT_EQ(s[s.size() - 1], 42);
  EXPECT_EQ(f[f.size() - 1], 42);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
}

// TODO: check recommend implemantation of c++11
TEST_F(VectorTest, InsertWithCount) {
  // std::cout << s.capacity() << std::endl;
  // std::cout << f.capacity() << std::endl;
  s.insert(s.begin(), 2000, 42);
  f.insert(f.begin(), 2000, 42);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  s.insert(s.begin() + 5, 4000, 57);
  f.insert(f.begin() + 5, 4000, 57);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  for (size_t i = 0; i < s.size(); i++) {
    EXPECT_EQ(s[i], f[i]);
  }
}

TEST_F(VectorTest, InsertWithIter) {
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

TEST_F(VectorTest, EraseOne) {
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
}

TEST_F(VectorTest, EraseIter) {
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
}

TEST_F(VectorTest, PopBack) {
  for (size_t i = 0; i < 100; i++) {
    s.pop_back();
    f.pop_back();
    EXPECT_EQ(s.size(), f.size());
    EXPECT_EQ(s.capacity(), f.capacity());
    for (size_t j = 0; j < s.size(); j++) {
      EXPECT_EQ(s[i], f[i]);
    }
  }
}

TEST_F(VectorTest, Resize) {
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

TEST_F(VectorTest, Swap) {
  for (size_t i = 0; i < 100; i++) {
    s[i] = i + 1;
    f[i] = i + 1;
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
}

TEST_F(VectorTest, Comparison) {
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
