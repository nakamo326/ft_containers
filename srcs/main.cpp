#include <algorithm>
#include <map>
#include <stack>
#include <typeinfo>

#include "ft_container.hpp"
#include "tree/RBtree.hpp"

int main() {
  ft::RBtree<int, int, std::less<int> > tree;
  tree.add(0, 0);
  tree.add(8, 0);
  // tree.outputAllTree();
  // std::cout << std::endl;
  tree.add(6, 0);
  tree.outputAllTree();
  std::cout << std::endl;
  // tree.add(3, 0);
  // tree.add(4, 0);
  // tree.add(5, 0);
  // tree.add(6, 0);
  // tree.add(7, 0);
  // tree.outputAllTree();
  return 0;
}
