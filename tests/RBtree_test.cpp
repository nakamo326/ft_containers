#include "RBtree.hpp"

#include <gtest/gtest.h>

#include <functional>
#include <random>

TEST(RBnodeTest, constructor) {
  ft::_RBnode<int, std::string> node(0, "hello");
  EXPECT_EQ(node.key_, 0);
  EXPECT_EQ(node.value_, "hello");
  EXPECT_EQ(node.left_, (void *)NULL);
  EXPECT_EQ(node.right_, (void *)NULL);
  EXPECT_EQ(node.parent_, (void *)NULL);
  EXPECT_EQ(node.color_, false);
}

TEST(RBtreeTest, add) {
  std::random_device rand;
  {
    ft::RBtree<int, int, std::less<int> > tree;
    int                                   times = 1000;
    for (size_t i = 0; i < times; i++) {
      tree.add(i, 0);
      EXPECT_EQ(tree.isValidTree(), true);
    }
  }
  {
    ft::RBtree<int, int, std::less<int> > tree;
    int                                   times = 1000;
    for (size_t i = 0; i < times; i++) {
      int tmp = rand() % times;
      tree.add(tmp, 0);
      EXPECT_EQ(tree.isValidTree(), true);
    }
  }
}

TEST(RBtreeTest, erase) {
  std::random_device                    rand;
  ft::RBtree<int, int, std::less<int> > tree;
  std::vector<int>                      keyList(4000);
  for (size_t i = 0; i < 4000; i++) {
    int tmp = rand() % 4000;
    tree.add(tmp, 0);
    keyList[i] = tmp;
  }
  for (size_t i = 0; i < 4000; i++) {
    tree.erase(keyList[i]);
    EXPECT_EQ(tree.isValidTree(), true);
  }
}