#include <algorithm>
#include <map>
#include <stack>
#include <typeinfo>

#include "RBtree.hpp"
#include "ft_container.hpp"

int main() {
  ft::vector<int>   int_vector(10);
  ft::vector<int *> int_pointer_vector(10);

  // check iterator and reverse_iterator
  ft::vector<int>::reverse_iterator   rit  = int_vector.rbegin();
  ft::vector<int *>::reverse_iterator rpit = int_pointer_vector.rbegin();
  (void)rit;
  (void)rpit;

  int *                                          p;
  ft::vector<int *>::reverse_iterator::reference ref = p;
  std::cout << typeid(ref).name() << std::endl;
  std::vector<int> v;
  return 0;
}
