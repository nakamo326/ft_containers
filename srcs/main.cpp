#include <typeinfo>

#include "ft_container.hpp"

struct s_test {
  static const int a = 5;
  s_test() {}
};

int main() {
  std::vector<int>           v(100);
  // std::cout << v.size() << std::endl;
  // std::cout << v.capacity() << std::endl;
  std::vector<int>::iterator it = v.begin();
  it += 50;
  v.insert(it, 150, 42);
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  v.insert(v.end(), 42);
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  return 0;
}
