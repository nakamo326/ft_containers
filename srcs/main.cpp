#include <typeinfo>

#include "ft_container.hpp"

int main() {
  ft::vector<int> v(100);
  v[0]                           = 42;
  v[1]                           = 57;
  v[49]                          = 77;
  v[99]                          = 9999;
  ft::vector<int>::iterator it   = v.begin();
  ft::vector<int>::iterator last = v.end();
  last -= 50;
  std::vector<int> nv(it, last);
  std::cout << nv.size() << std::endl;
  std::cout << nv.capacity() << std::endl;
  std::cout << nv[49] << std::endl;

  return 0;
}
