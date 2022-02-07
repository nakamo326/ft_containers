#include <algorithm>
#include <map>
#include <stack>
#include <typeinfo>

#include "RBtree.hpp"
#include "ft_container.hpp"

int main() {
  ft::RBtree<int, int, std::less<int> > tree;
  tree.add(0, 0);
  tree.add(8, 0);
  tree.add(6, 0);
  tree.add(3, 0);
  tree.add(5, 0);
  // tree.add(4, 0);
  // tree.add(7, 0);

  tree.outputAllTree();
  std::cout << std::endl;
  tree.erase(6);
  tree.outputAllTree();
  // tree.outputAllTree();
  std::cout << tree.isValidTree() << std::endl;
  std::pair<int, int> a;
  return 0;
}
