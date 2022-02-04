#include <algorithm>
#include <map>
#include <stack>
#include <typeinfo>

#include "ft_container.hpp"
#include "tree/RBtree.hpp"

int main() {
  ft::RBtree<int, std::string, std::less<int> > tree;
  tree.add(0, "root");
  tree.add(1, "add first");
  tree.outputAllTree();
  return 0;
}
