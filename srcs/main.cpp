#include <typeinfo>

#include "ft_container.hpp"

int main() {
  // int             array[] = {1, 2, 3, 4, 5};
  NS::vector<int> v(100);
  v[0]  = 42;
  v[99] = 9999;
  std::cout << v[30] << std::endl;
  std::cout << v.at(0) << std::endl;
  std::cout << v.front() << std::endl;
  std::cout << v.back() << std::endl;
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  v.clear();
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  std::cout << typeid(v.get_allocator()).name() << std::endl;

  std::vector<int> other(100);
  std::vector<int> dest;
  std::cout << dest.size() << std::endl;
  dest = other;
  std::cout << dest.size() << std::endl;
  std::cout << dest.capacity() << std::endl;
  dest.push_back(5);
  std::cout << dest.size() << std::endl;
  std::cout << dest.capacity() << std::endl;
  std::cout << other.size() << std::endl;
  std::cout << other.capacity() << std::endl;
  return 0;
}
