#include "tree/RBtree.hpp"

#include <gtest/gtest.h>

TEST(RBnodeTest, constructor) {
  ft::_RBnode<int, std::string> node(0, "hello");
  node.outputInfo();
}