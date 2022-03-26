#include "pair.hpp"

#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "testframe/testframe.hpp"
#endif

TEST(pair_test, constructor) {
  std::pair<int, int> std_pair(10, 10);
  ft::pair<int, int>  ft_pair(10, 10);

  EXPECT_EQ(std_pair.first, ft_pair.first);
  EXPECT_EQ(std_pair.second, ft_pair.second);
}

TEST(pair_test, copy_constructor) {
  std::pair<int, int> std_pair(10, 10);
  ft::pair<int, int>  ft_pair(10, 10);
  std::pair<int, int> std_copy(std_pair);
  ft::pair<int, int>  ft_copy(ft_pair);

  EXPECT_EQ(std_copy.first, ft_copy.first);
  EXPECT_EQ(std_copy.second, ft_copy.second);
}

TEST(pair_test, assignation) {
  std::pair<std::string, std::string> std_pair("hello", "world");
  ft::pair<std::string, std::string>  ft_pair("hello", "world");
  std::pair<std::string, std::string> std_copy;
  ft::pair<std::string, std::string>  ft_copy;

  std_copy = std_pair;
  ft_copy  = ft_pair;

  EXPECT_EQ(std_copy.first, ft_copy.first);
  EXPECT_EQ(std_copy.second, ft_copy.second);
}

TEST(pair_test, make_pair) {
  std::pair<std::string, std::string> std_pair;
  ft::pair<std::string, std::string>  ft_pair;

  std_pair = std::make_pair("hello", "world");
  ft_pair  = ft::make_pair("hello", "world");

  EXPECT_EQ(std_pair.first, ft_pair.first);
  EXPECT_EQ(std_pair.second, ft_pair.second);
}

TEST(pair_test, comparison) {
  std::pair<std::string, std::string> std_pair("hello", "world");
  ft::pair<std::string, std::string>  ft_pair("hello", "world");

  std::pair<std::string, std::string> std_comp("hello", "world");
  ft::pair<std::string, std::string>  ft_comp("hello", "world");

  EXPECT_EQ(std_pair == std_comp, ft_pair == ft_comp);
  EXPECT_EQ(std_pair != std_comp, ft_pair != ft_comp);
  EXPECT_EQ(std_pair < std_comp, ft_pair < ft_comp);
  EXPECT_EQ(std_pair <= std_comp, ft_pair <= ft_comp);
  EXPECT_EQ(std_pair > std_comp, ft_pair > ft_comp);
  EXPECT_EQ(std_pair >= std_comp, ft_pair >= ft_comp);

  std_comp.first = "helmo";
  ft_comp.first  = "helmo";

  EXPECT_EQ(std_pair == std_comp, ft_pair == ft_comp);
  EXPECT_EQ(std_pair != std_comp, ft_pair != ft_comp);
  EXPECT_EQ(std_pair < std_comp, ft_pair < ft_comp);
  EXPECT_EQ(std_pair <= std_comp, ft_pair <= ft_comp);
  EXPECT_EQ(std_pair > std_comp, ft_pair > ft_comp);
  EXPECT_EQ(std_pair >= std_comp, ft_pair >= ft_comp);

  std_comp.first  = "hello";
  ft_comp.first   = "hello";

  std_comp.second = "worle";
  ft_comp.second  = "worle";

  EXPECT_EQ(std_pair == std_comp, ft_pair == ft_comp);
  EXPECT_EQ(std_pair != std_comp, ft_pair != ft_comp);
  EXPECT_EQ(std_pair < std_comp, ft_pair < ft_comp);
  EXPECT_EQ(std_pair <= std_comp, ft_pair <= ft_comp);
  EXPECT_EQ(std_pair > std_comp, ft_pair > ft_comp);
  EXPECT_EQ(std_pair >= std_comp, ft_pair >= ft_comp);
}
