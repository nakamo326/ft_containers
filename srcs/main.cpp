#include <typeinfo>

#include "ft_container.hpp"

struct s_test {
  static const int a = 5;
  s_test() {}
};

int main() {
  std::vector<int> v(100);
  v[0]  = 42;
  v[1]  = 57;
  v[49] = 77;
  v[99] = 9999;

  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  std::cout << v[49] << std::endl;

  std::vector<int> a(59);
  std::cout << a.size() << std::endl;
  std::cout << a.capacity() << std::endl;
  std::cout << std::hex << a.data() << std::endl;
  a.assign(v.begin(), v.end());
  std::cout << a.size() << std::endl;
  std::cout << a.capacity() << std::endl;
  std::cout << std::hex << a.data() << std::endl;
  std::vector<s_test> test(5);
  std::cout << test[1].a << std::endl;
  return 0;
}
