#include <typeinfo>

#include "ft_container.hpp"

int main() {
  std::vector<int> v(100);
  v[0]  = 42;
  v[1]  = 57;
  v[49] = 77;
  v[99] = 9999;

  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  std::cout << v[49] << std::endl;

  std::vector<int> c;
  std::cout << c.size() << std::endl;
  std::cout << c.capacity() << std::endl;
  v = c;
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  v.assign(50, 42);
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  std::cout << v[49] << std::endl;
  std::cout << v[99] << std::endl;

  return 0;
}
