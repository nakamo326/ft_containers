#include "tree/RBtree.hpp"

#include <gtest/gtest.h>

#include <functional>
#include <random>

TEST(RBnodeTest, constructor) {
  ft::_RBnode<int, std::string> node(0, "hello");
  node.outputInfo();
}

TEST(RBtreeTest, add) {
  std::random_device                    rand;
  ft::RBtree<int, int, std::less<int> > tree;
  int                                   times = 10;
  for (size_t i = 0; i < times; i++) {
    int tmp = rand() % times;
    tree.add(tmp, 0);
    EXPECT_EQ(tree.isValidTree(), true);
  }
}