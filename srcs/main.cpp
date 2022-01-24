#include <typeinfo>

#include "ft_container.hpp"

int main() {
  ft::vector<int> v(100);
  v[0]  = 42;
  v[1]  = 57;
  v[50] = 77;
  v[99] = 9999;
  v.reserve(200);
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;

  return 0;
}
