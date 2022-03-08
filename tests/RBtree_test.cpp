#include "RBtree.hpp"

#include <gtest/gtest.h>

#include <functional>
#include <random>

#include "function.hpp"
#include "pair.hpp"

typedef ft::RBtree<int, ft::pair<int, int>, ft::_Select1st<ft::pair<int, int>>,
                   std::less<int>>
    tree_type;

TEST(RBnodeTest, constructor) {
  ft::_RBnode<ft::pair<int, int>> node(ft::make_pair(0, 0));
  EXPECT_EQ(node.value_, ft::make_pair(0, 0));
  EXPECT_EQ(node.left_, (void *)NULL);
  EXPECT_EQ(node.right_, (void *)NULL);
  EXPECT_EQ(node.parent_, (void *)NULL);
  EXPECT_EQ(node.color_, false);
}

// TEST(RBtreeTest, add) {
//   std::random_device rand;
//   {
//     tree_type tree;
//     int       times = 10000;
//     for (size_t i = 0; i < times; i++) {
//       tree.insert(ft::make_pair(i, 0));
//       EXPECT_EQ(tree.isValidTree(), true);
//       EXPECT_EQ(tree.size(), i + 1);
//     }
//   }
//   {
//     tree_type tree;
//     int       times = 10000;
//     for (size_t i = 0; i < times; i++) {
//       int tmp = rand() % times;
//       tree.insert(ft::make_pair(tmp, 0));
//       EXPECT_EQ(tree.isValidTree(), true);
//       EXPECT_EQ(tree.size(), i + 1);
//     }
//   }
// }

// TEST(RBtreeTest, erase) {
//   std::random_device rand;
//   tree_type          tree;
//   std::vector<int>   keyList(4000);
//   for (size_t i = 0; i < 4000; i++) {
//     int tmp = rand() % 4000;
//     tree.insert(ft::make_pair(tmp, 0));
//     keyList[i] = tmp;
//     EXPECT_EQ(tree.size(), i + 1);
//   }
//   for (size_t i = 0; i < 4000; i++) {
//     tree.erase(keyList[i]);
//     EXPECT_EQ(tree.isValidTree(), true);
//     EXPECT_EQ(tree.size(), 4000 - (i + 1));
//   }
// }

// TEST(RBtreeTest, Random) {
//   int                test_times = 40000;
//   std::random_device rand;
//   ft::RBtree<int,
//              ft::pair<int, int>,
//              ft::_Select1st<ft::pair<int, int>>,
//              std::less<int>>
//                    tree;
//   std::vector<int> keyList;

//   int add_times = 0;
//   for (size_t i = 0; i < test_times; i++) {
//     if (rand() % 2 || add_times == 0) {
//       int tmp = rand() % test_times;
//       tree.insert(ft::make_pair(tmp, 0));
//       keyList.push_back(tmp);
//       add_times++;
//     } else {
//       tree.erase(keyList[rand() % add_times]);
//       EXPECT_EQ(tree.isValidTree(), true);
//       add_times--;
//     }
//   }
// }

TEST(RBtreeTest, BeginNodeTest) {
  tree_type tree;

  EXPECT_EQ(tree.getBeginNode(), static_cast<void *>(NULL));
  tree.insert(ft::make_pair(10, 42));
  EXPECT_EQ(tree.getBeginNode()->value_.first, 10);
  tree.erase(10);
  EXPECT_EQ(tree.getBeginNode(), static_cast<void *>(NULL));
  tree.insert(ft::make_pair(9, 42));
  EXPECT_EQ(tree.getBeginNode()->value_.first, 9);
  tree.insert(ft::make_pair(8, 42));
  EXPECT_EQ(tree.getBeginNode()->value_.first, 8);
  tree.erase(8);
  EXPECT_EQ(tree.getBeginNode()->value_.first, 9);
  tree.insert(ft::make_pair(7, 42));
  EXPECT_EQ(tree.getBeginNode()->value_.first, 7);
  tree.insert(ft::make_pair(6, 42));
  EXPECT_EQ(tree.getBeginNode()->value_.first, 6);
  tree.erase(9);
  EXPECT_EQ(tree.getBeginNode()->value_.first, 6);
}

TEST(RBtreeTest, Iterator) {
  tree_type tree;

  tree.insert(ft::make_pair(7, 7));
  tree.insert(ft::make_pair(1, 1));
  tree.insert(ft::make_pair(3, 3));
  tree.insert(ft::make_pair(2, 2));
  tree.insert(ft::make_pair(4, 4));
  tree.insert(ft::make_pair(6, 6));
  tree.insert(ft::make_pair(5, 5));

  tree_type::iterator it = tree.begin();
  EXPECT_EQ((*it).second, 1);
  EXPECT_EQ(it->second, 1);
  (*it).second = 42;
  EXPECT_EQ((*it).second, 42);
  EXPECT_EQ(it->second, 42);
  it->second = 57;
  EXPECT_EQ((*it).second, 57);
  EXPECT_EQ(it->second, 57);
  ++it;
  EXPECT_EQ((*it).second, 2);
  EXPECT_EQ(it->second, 2);
  it++;
  EXPECT_EQ((*it).second, 3);
  EXPECT_EQ(it->second, 3);
  --it;
  EXPECT_EQ((*it).second, 2);
  EXPECT_EQ(it->second, 2);
  it--;
  for (int i = 1; it != tree.end(); it++) {
    EXPECT_EQ(it->first, i);
    i++;
  }
}

TEST(RBtreeTest, ReverseIterator) {
  tree_type tree;

  tree.insert(ft::make_pair(7, 7));
  tree.insert(ft::make_pair(1, 1));
  tree.insert(ft::make_pair(3, 3));
  tree.insert(ft::make_pair(2, 2));
  tree.insert(ft::make_pair(4, 4));
  tree.insert(ft::make_pair(6, 6));
  tree.insert(ft::make_pair(5, 5));

  tree_type::reverse_iterator rit(tree.begin());
}