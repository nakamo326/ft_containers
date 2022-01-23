#include <typeinfo>

#include "ft_container.hpp"

int main() {
  // int             array[] = {1, 2, 3, 4, 5};
  ft::vector<int> v(100);
  v[0]  = 42;
  v[1]  = 57;
  v[50] = 77;
  v[99] = 9999;
  std::cout << v[30] << std::endl;
  std::cout << v.at(0) << std::endl;
  std::cout << v.back() << std::endl;
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;

  // ft::vector<int>::iterator it      = v.begin();
  // ft::vector<int>::iterator it2     = v.begin();

  // std::cout << *it << std::endl;
  // std::cout << std::boolalpha << (it == it2) << std::endl;
  // ++it;
  // std::cout << std::boolalpha << (it == it2) << std::endl;
  // std::cout << *it << std::endl;
  // std::cout << *it++ << std::endl;
  // std::cout << *it << std::endl;

  ft::vector<int>::iterator beginit = v.begin();
  ft::vector<int>::iterator endit   = v.end();
  std::cout << *beginit << std::endl;
  std::cout << *endit << std::endl;
  // wtf
  std::cout << std::boolalpha << (beginit == endit) << std::endl;
  for (size_t i = 0; i < 100; i++) {
    if (*beginit != 0) {
      std::cout << "i: " << i << ", *gebinit = " << *beginit << std::endl;
    }
    beginit++;
  }
  std::cout << std::boolalpha << (beginit == endit) << std::endl;
  std::cout << *(--endit) << std::endl;
  beginit = 50 + v.begin();
  std::cout << *beginit << std::endl;

  {
    std::vector<int>           s(10);
    std::vector<int>::iterator it1 = s.begin();
    std::vector<int>::iterator it2(it1);
    std::cout << std::boolalpha << (it1 == it2) << std::endl;
  }

  return 0;
}
