#include "RBtree.hpp"

#include <gtest/gtest.h>

#include <functional>
#include <random>

#include "function.hpp"
#include "pair.hpp"

TEST(RBnodeTest, constructor) {
  ft::_RBnode<ft::pair<int, int>> node(ft::make_pair(0, 0));
  EXPECT_EQ(node.value_, ft::make_pair(0, 0));
  EXPECT_EQ(node.left_, (void *)NULL);
  EXPECT_EQ(node.right_, (void *)NULL);
  EXPECT_EQ(node.parent_, (void *)NULL);
  EXPECT_EQ(node.color_, false);
}

TEST(RBtreeTest, add) {
  std::random_device rand;
  {
    ft::RBtree<int,
               ft::pair<int, int>,
               ft::_Select1st<ft::pair<int, int>>,
               std::less<int>>
        tree;
    int times = 10000;
    for (size_t i = 0; i < times; i++) {
      tree.insert(ft::make_pair(i, 0));
      EXPECT_EQ(tree.isValidTree(), true);
    }
  }
  {
    ft::RBtree<int,
               ft::pair<int, int>,
               ft::_Select1st<ft::pair<int, int>>,
               std::less<int>>
        tree;
    int times = 10000;
    for (size_t i = 0; i < times; i++) {
      int tmp = rand() % times;
      tree.insert(ft::make_pair(tmp, 0));
      EXPECT_EQ(tree.isValidTree(), true);
    }
  }
}

TEST(RBtreeTest, erase) {
  std::random_device rand;
  ft::RBtree<int,
             ft::pair<int, int>,
             ft::_Select1st<ft::pair<int, int>>,
             std::less<int>>
                   tree;
  std::vector<int> keyList(4000);
  for (size_t i = 0; i < 4000; i++) {
    int tmp = rand() % 4000;
    tree.insert(ft::make_pair(tmp, 0));
    keyList[i] = tmp;
  }
  for (size_t i = 0; i < 4000; i++) {
    tree.erase(keyList[i]);
    EXPECT_EQ(tree.isValidTree(), true);
  }
}

TEST(RBtreeTest, Random) {
  int                test_times = 40000;
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
      EXPECT_EQ(tree.isValidTree(), true);
      add_times--;
    }
  }
}

// TEST(RBtreeTest, Iterator) {
//   typedef ft::RBtree<int,
//                      ft::pair<int, int>,
//                      ft::_Select1st<ft::pair<int, int>>,
//                      std::less<int>>
//                  test_tree_type;
//   test_tree_type tree;

//   tree.insert(ft::make_pair(7, 7));
//   tree.insert(ft::make_pair(1, 1));
//   tree.insert(ft::make_pair(3, 3));
//   tree.insert(ft::make_pair(2, 2));
//   tree.insert(ft::make_pair(4, 4));
//   tree.insert(ft::make_pair(6, 6));
//   tree.insert(ft::make_pair(5, 5));

//   test_tree_type::iterator it;
// }