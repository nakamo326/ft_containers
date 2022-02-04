#include <algorithm>
#include <map>
#include <stack>
#include <typeinfo>

#include "ft_container.hpp"
#include "tree/RBtree.hpp"

int main() {
  ft::RBtree<int, int, std::less<int> > tree;
  tree.add(0, 0);
  tree.add(1, 0);
  tree.add(2, 0);
  tree.add(3, 0);
  tree.add(4, 0);
  tree.outputAllTree();
  return 0;
}
