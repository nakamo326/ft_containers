#include <map>
#include <stack>
#include <typeinfo>

#include "ft_container.hpp"

int main() {
  std::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }

  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  v.insert(v.begin(), 1000, 0);
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;

  return 0;
}
