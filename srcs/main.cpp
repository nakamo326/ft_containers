#include <algorithm>
#include <map>
#include <stack>
#include <typeinfo>

#include "RBtree.hpp"
#include "ft_container.hpp"

int main() {
  ft::vector<int>       int_vector(10);
  ft::vector<const int> const_int_vector(10);
  ft::vector<int *>     int_pointer_vector(10);

  // check iterator and reverse_iterator
  ft::vector<int>::reverse_iterator       rit  = int_vector.rbegin();
  ft::vector<const int>::reverse_iterator rcit = const_int_vector.rbegin();
  ft::vector<int *>::reverse_iterator     rpit = int_pointer_vector.rbegin();

  return 0;
}
