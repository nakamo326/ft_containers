#include "RBtree.hpp"

#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "testframe/testframe.hpp"
#endif

#include <functional>
#include <random>

#include "function.hpp"
#include "pair.hpp"

typedef ft::RBtree<int, ft::pair<int, int>, ft::_Select1st<ft::pair<int, int>>,
                   std::less<int>>
    tree_type;

TEST(RBtreeTest, Random) {
  int                test_times = 100000;
  std::random_device rand;
  ft::RBtree<int,
             ft::pair<int, int>,
             ft::_Select1st<ft::pair<int, int>>,
             std::less<int>>
                   tree;
  std::vector<int> keyList;

  int add_times = 0;
  for (size_t i = 0; i < test_times; i++) {
    if (rand() % 2 || add_times == 0) {
      int tmp = rand() % test_times;
      tree.insert(ft::make_pair(tmp, 0));
      keyList.push_back(tmp);
      add_times++;
    } else {
      tree.erase(keyList[rand() % add_times]);
      ASSERT_EQ(tree.is_valid_tree(), true);
      add_times--;
    }
  }
}

TEST(RBtreeTest, BeginNodeTest) {
  tree_type tree;

  EXPECT_EQ(tree.get_begin_node(), tree.begin().base());
  tree.insert(ft::make_pair(10, 42));
  EXPECT_EQ(tree.get_begin_node()->value_.first, 10);
  tree.erase(10);
  EXPECT_EQ(tree.get_begin_node(), tree.begin().base());
  tree.insert(ft::make_pair(9, 42));
  EXPECT_EQ(tree.get_begin_node()->value_.first, 9);
  tree.insert(ft::make_pair(8, 42));
  EXPECT_EQ(tree.get_begin_node()->value_.first, 8);
  tree.erase(8);
  EXPECT_EQ(tree.get_begin_node()->value_.first, 9);
  tree.insert(ft::make_pair(7, 42));
  EXPECT_EQ(tree.get_begin_node()->value_.first, 7);
  tree.insert(ft::make_pair(6, 42));
  EXPECT_EQ(tree.get_begin_node()->value_.first, 6);
  tree.erase(9);
  EXPECT_EQ(tree.get_begin_node()->value_.first, 6);
}

TEST(RBtreeTest, positionInsert) {
  std::random_device rand;
  {
    tree_type            tree;
    tree_type::size_type size  = 0;
    int                  times = 10000;
    for (size_t i = 0; i < times; i++) {
      int tmp    = rand() % times;
      int choice = rand() % 3;
      if (choice == 0) {
        tree.insert(tree.find(tmp), ft::make_pair(tmp, 0));
      } else if (choice == 1) {
        tree.insert(tree.begin(), ft::make_pair(tmp, 0));
      } else {
        tree.insert(tree.end(), ft::make_pair(tmp, 0));
      }
      EXPECT_EQ(tree.is_valid_tree(), true);
      if (tree.count(tmp))
        size++;
    }
  }
}
