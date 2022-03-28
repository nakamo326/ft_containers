#include "pair.hpp"

#include "switch.hpp"

#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "testframe/testframe.hpp"
#endif

TEST(pair_test, constructor) {
  LIB::pair<int, int> pair(10, 10);

  EXPECT_EQ(pair.first, 10);
  EXPECT_EQ(pair.second, 10);
}

TEST(pair_test, copy_constructor) {
  LIB::pair<int, int> pair(10, 10);
  LIB::pair<int, int> copy(pair);

  EXPECT_EQ(copy.first, pair.first);
  EXPECT_EQ(copy.second, pair.second);
}

TEST(pair_test, assignation) {
  LIB::pair<std::string, std::string> pair("hello", "world");
  LIB::pair<std::string, std::string> copy;

  copy = pair;

  EXPECT_EQ(copy.first, pair.first);
  EXPECT_EQ(copy.second, pair.second);
}

TEST(pair_test, make_pair) {
  LIB::pair<std::string, std::string> pair;

  pair = LIB::make_pair("hello", "world");

  EXPECT_EQ(pair.first, "hello");
  EXPECT_EQ(pair.second, "world");
}

TEST(pair_test, comparison) {
  std::pair<std::string, std::string> std_pair("hello", "world");

  std::pair<std::string, std::string> std_comp("hello", "world");

  EXPECT_EQ(std_pair == std_comp, true);
  EXPECT_EQ(std_pair != std_comp, false);
  EXPECT_EQ(std_pair < std_comp, false);
  EXPECT_EQ(std_pair <= std_comp, true);
  EXPECT_EQ(std_pair > std_comp, false);
  EXPECT_EQ(std_pair >= std_comp, true);

  std_comp.first = "helmo";

  EXPECT_EQ(std_pair == std_comp, false);
  EXPECT_EQ(std_pair != std_comp, true);
  EXPECT_EQ(std_pair < std_comp, true);
  EXPECT_EQ(std_pair <= std_comp, true);
  EXPECT_EQ(std_pair > std_comp, false);
  EXPECT_EQ(std_pair >= std_comp, false);

  std_comp.first  = "hello";

  std_comp.second = "worle";

  EXPECT_EQ(std_pair == std_comp, false);
  EXPECT_EQ(std_pair != std_comp, true);
  EXPECT_EQ(std_pair < std_comp, true);
  EXPECT_EQ(std_pair <= std_comp, true);
  EXPECT_EQ(std_pair > std_comp, false);
  EXPECT_EQ(std_pair >= std_comp, false);
}