#include "vector.hpp"

#include <gtest/gtest.h>

TEST(VectorTest, DefaultConstructor) {
  std::vector<int> s;
  ft::vector<int>  f;
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.data(), f.data());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}

TEST(VectorTest, ConstructorWithAllocator) {
  std::allocator<int> alloc;
  std::vector<int>    s(alloc);
  ft::vector<int>     f(alloc);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.data(), f.data());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}

TEST(VectorTest, ConstructorWithSize) {
  std::vector<int> s(100);
  ft::vector<int>  f(100);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.max_size(), f.max_size());
  EXPECT_EQ(s.capacity(), f.capacity());
  EXPECT_EQ(s.get_allocator(), f.get_allocator());
}

TEST(VectorTest, ConstructorWithValue) {
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

TEST(VectorTest, RangeConstructor) {
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

TEST(VectorTest, CopyConstructor) {
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
  // big to small
  {
    ft::vector<int>  f(1000);
    std::vector<int> s(1000);
    for (size_t i = 0; i < 1000; i++) {
      f[i] = i;
      s[i] = i;
    }
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
    ft::vector<int>  f(1000);
    std::vector<int> s(1000);
    for (size_t i = 0; i < 1000; i++) {
      f[i] = i;
      s[i] = i;
    }
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

TEST(VectorTest, AssignFunc) {
  // big to small
  {
    std::vector<int> s(1000);
    ft::vector<int>  f(1000);
    for (size_t i = 0; i < 1000; i++) {
      s[i] = i;
      f[i] = i;
    }
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
    std::vector<int> s(1000);
    ft::vector<int>  f(1000);
    for (size_t i = 0; i < 1000; i++) {
      s[i] = i;
      f[i] = i;
    }
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

TEST(VectorTest, AssignFuncIter) {
  // big to small
  {
    std::vector<int> s(1000);
    ft::vector<int>  f(1000);
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
    std::vector<int> s(1000);
    ft::vector<int>  f(1000);
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

TEST(VectorTest, Destructor) {
  ft::vector<int> *f = new ft::vector<int>(1000);
  for (size_t i = 0; i < 1000; i++) {
    (*f)[i] = i;
  }
  delete f;
}

TEST(VectorTest, At) {
  std::vector<int> s(10);
  ft::vector<int>  f(10);

  s[5] = 10;
  f[5] = 10;
  EXPECT_EQ(s.at(0), f.at(0));
  EXPECT_EQ(s.at(5), f.at(5));
  EXPECT_THROW(s.at(20), std::out_of_range);
  EXPECT_THROW(f.at(20), std::out_of_range);
}

TEST(VectorTest, BeginAndEnd) {
  ft::vector<int>           f(10);
  ft::vector<int>::iterator it = f.begin();

  f[0]                         = 21;
  f[9]                         = 42;
  EXPECT_EQ(f[0], *(f.begin()));
  EXPECT_EQ(f[9], *(--(f.end())));
  for (size_t i = 0; i < 10; i++) {
    it++;
  }
  EXPECT_EQ(it, f.end());
}

TEST(VectorTest, Pushback) {
  std::vector<int> s(10);
  ft::vector<int>  f(10);
  for (size_t i = 0; i < 100000; i++) {
    s.push_back(i);
    f.push_back(i);
    EXPECT_EQ(s[i], f[i]);
    EXPECT_EQ(s.size(), f.size());
    EXPECT_EQ(s.capacity(), f.capacity());
  }
}

TEST(VectorTest, Clear) {}

TEST(VectorTest, InsertWithValue) {
  std::vector<int> s(10);
  ft::vector<int>  f(10);
  s.insert(s.begin() + 5, 42);
  f.insert(f.begin() + 5, 42);
  EXPECT_EQ(s[5], 42);
  EXPECT_EQ(f[5], 42);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
  s.insert(s.end(), 42);
  f.insert(f.end(), 42);
  EXPECT_EQ(s[5], 42);
  EXPECT_EQ(f[5], 42);
  EXPECT_EQ(s.size(), f.size());
  EXPECT_EQ(s.capacity(), f.capacity());
}