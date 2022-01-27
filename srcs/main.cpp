#include <typeinfo>

#include "ft_container.hpp"

struct s_test {
  static const int a = 5;
  s_test() {}
};

int main() {
  std::vector<int> v(100);
  std::vector<int> c(100);
  for (size_t i = 0; i < 100; i++) {
    v[i] = c[i] = i;
  }
  std::cout << std::boolalpha << (v == c) << std::endl;

  v.reserve(200);
  std::cout << std::boolalpha << (v == c) << std::endl;
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  return 0;
}
