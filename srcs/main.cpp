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

  v.assign(50, 42);
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  std::cout << v[49] << std::endl;
  std::cout << v[99] << std::endl;

  std::vector<char> a;
  std::cout << a.size() << std::endl;
  std::cout << a.capacity() << std::endl;
  a.assign(50, 'c');
  std::cout << a.size() << std::endl;
  std::cout << a.capacity() << std::endl;
  // a.reserve(a.max_size() + 10);
  a.assign(a.max_size() + 10, 'd');
  return 0;
}
