#include <gtest/gtest.h>

#include "vector.hpp"

TEST(VectorIteratorTest, Iterator) {
  std::vector<int> s(10);
  ft::vector<int>  f(10);
  for (size_t i = 0; i < 10; i++) {
    s[i] = i;
    f[i] = i;
  }
  ft::vector<int>::iterator        it = f.begin();
  ft::vector<int>::iterator        it2(it);
  ft::vector<int>::const_iterator  cit = f.begin();
  std::vector<int>::iterator       sit = s.begin();
  std::vector<int>::iterator       sit2(sit);
  std::vector<int>::const_iterator scit = s.begin();
  EXPECT_EQ((sit == sit2), (it == it2));
  EXPECT_EQ((sit == scit), (it == cit));
  EXPECT_EQ((scit == sit), (cit == it));
  EXPECT_EQ((sit != sit2), (it != it2));
  EXPECT_EQ((sit != scit), (it != cit));
  EXPECT_EQ((sit <= sit2), (it <= it2));
  EXPECT_EQ((sit <= scit), (it <= cit));
  EXPECT_EQ((sit >= sit2), (it >= it2));
  EXPECT_EQ((sit >= scit), (it >= cit));
  EXPECT_EQ((sit < sit2), (it < it2));
  EXPECT_EQ((sit < scit), (it < cit));
  EXPECT_EQ((sit > sit2), (it > it2));
  EXPECT_EQ((sit > scit), (it > cit));
  cit++;
  it2++;
  scit++;
  sit2++;
  EXPECT_EQ((sit == sit2), (it == it2));
  EXPECT_EQ((sit == scit), (it == cit));
  EXPECT_EQ((sit != sit2), (it != it2));
  EXPECT_EQ((sit != scit), (it != cit));
  EXPECT_EQ((sit <= sit2), (it <= it2));
  EXPECT_EQ((sit <= scit), (it <= cit));
  EXPECT_EQ((sit >= sit2), (it >= it2));
  EXPECT_EQ((sit >= scit), (it >= cit));
  EXPECT_EQ((sit < sit2), (it < it2));
  EXPECT_EQ((sit < scit), (it < cit));
  EXPECT_EQ((sit > sit2), (it > it2));
  EXPECT_EQ((sit > scit), (it > cit));
  cit += 9;
  it2 += 9;
  EXPECT_EQ(true, (it2 == f.end()));
  EXPECT_EQ(true, (cit == f.end()));
  EXPECT_EQ((s.end() - s.begin()), (f.end() - f.begin()));
}

TEST(VectorIteratorTest, ReverseIterator) {
  std::vector<int> s(10);
  ft::vector<int>  f(10);
  for (size_t i = 0; i < 10; i++) {
    s[i] = i;
    f[i] = i;
  }
  ft::vector<int>::reverse_iterator        it = f.rbegin();
  ft::vector<int>::reverse_iterator        it2(it);
  ft::vector<int>::const_reverse_iterator  cit = f.rbegin();
  std::vector<int>::reverse_iterator       sit = s.rbegin();
  std::vector<int>::reverse_iterator       sit2(sit);
  std::vector<int>::const_reverse_iterator scit = s.rbegin();
  EXPECT_EQ((sit == sit2), (it == it2));
  EXPECT_EQ((sit == scit), (it == cit));
  EXPECT_EQ((scit == sit), (cit == it));
  EXPECT_EQ((sit != sit2), (it != it2));
  EXPECT_EQ((sit != scit), (it != cit));
  EXPECT_EQ((sit <= sit2), (it <= it2));
  EXPECT_EQ((sit <= scit), (it <= cit));
  EXPECT_EQ((sit >= sit2), (it >= it2));
  EXPECT_EQ((sit >= scit), (it >= cit));
  EXPECT_EQ((sit < sit2), (it < it2));
  EXPECT_EQ((sit < scit), (it < cit));
  EXPECT_EQ((sit > sit2), (it > it2));
  EXPECT_EQ((sit > scit), (it > cit));
  cit++;
  it2++;
  scit++;
  sit2++;
  EXPECT_EQ((sit == sit2), (it == it2));
  EXPECT_EQ((sit == scit), (it == cit));
  EXPECT_EQ((sit != sit2), (it != it2));
  EXPECT_EQ((sit != scit), (it != cit));
  EXPECT_EQ((sit <= sit2), (it <= it2));
  EXPECT_EQ((sit <= scit), (it <= cit));
  EXPECT_EQ((sit >= sit2), (it >= it2));
  EXPECT_EQ((sit >= scit), (it >= cit));
  EXPECT_EQ((sit < sit2), (it < it2));
  EXPECT_EQ((sit < scit), (it < cit));
  EXPECT_EQ((sit > sit2), (it > it2));
  EXPECT_EQ((sit > scit), (it > cit));
  cit += 9;
  it2 += 9;
  EXPECT_EQ(true, (it2 == f.rend()));
  EXPECT_EQ(true, (cit == f.rend()));
  EXPECT_EQ((s.rend() - s.rbegin()), (f.rend() - f.rbegin()));

  ft::vector<int> tmp(100);
  for (size_t i = 0; i < 100; i++) {
    tmp.push_back(i);
  }
  auto crit = tmp.rbegin();
  for (size_t i = 0; i < 100; i++) {
    EXPECT_EQ(*crit, 99 - i);
    crit++;
  }
}

TEST(VectorIteratorTest, const_iterator) {
  std::vector<int> s(10);
  ft::vector<int>  f(10);
  for (size_t i = 0; i < 10; i++) {
    s[i] = i;
    f[i] = i;
  }
  ft::vector<int>::iterator        it        = f.begin();
  ft::vector<int>::const_iterator  const_it  = it;
  std::vector<int>::iterator       sit       = s.begin();
  std::vector<int>::const_iterator const_sit = sit;

  // cannot assign to const_it;
  // *const_it = 42;

  for (size_t i = 0; i < 10; i++) {
    EXPECT_EQ(*it, *sit);
    EXPECT_EQ(*const_it, *const_sit);
    it++;
    sit++;
    const_it++;
    const_sit++;
  }
}

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

TEST(VectorIteratorTest, ReverseIteratorArrowOperator) {
  TestClass                               t[10];
  ft::vector<TestClass>::reverse_iterator it(t + 10);
  ft::vector<TestClass>::reverse_iterator end(t);

  for (int i = 0; it != end; it++) {
    *it->p = i;
    i++;
  }
}