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

TEST(VectorTest, Iterator) {
  std::vector<int> s(10);
  ft::vector<int>  f(10);
  for (size_t i = 0; i < 10; i++) {
    s[i] = i;
    f[i] = i;
  }
  ft::vector<int>::iterator  it = f.begin();
  ft::vector<int>::iterator  it2(it);
  ft::vector<int>::iterator  cit = f.begin();
  std::vector<int>::iterator sit = s.begin();
  std::vector<int>::iterator sit2(sit);
  std::vector<int>::iterator scit = s.begin();
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

TEST(VectorTest, ReverseIterator) {
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
}