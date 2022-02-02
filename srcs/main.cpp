#include <algorithm>
#include <map>
#include <stack>
#include <typeinfo>

#include "ft_container.hpp"

int main() {
  ft::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  ft::vector<int>::iterator it = std::find(v.begin(), v.end(), 50);
  std::cout << *it << std::endl;
  std::vector<int> s;
  for (size_t i = 0; i < 100; i++) {
    s.push_back(i);
  }
  v.insert(v.begin() + 10, s.begin(), s.end());
  std::cout << v.size() << std::endl;
  s.insert(s.begin(), v.begin(), v.end());
  std::cout << s.size() << std::endl;
  return 0;
}
