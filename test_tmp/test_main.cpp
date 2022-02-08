#include <iostream>

#include "test.hpp"

test_func_vec_type test_functions;

#include "hoge.cpp"

namespace ft {
namespace test {

bool MakeAndRegisterTestInfo(test_func_type func) {
  std::cout << "MakeAndRegisterTestInfo が呼ばれた" << std::endl;
  test_functions.push_back(func);
  return true;
}

}  // namespace test
}  // namespace ft

int main() {
  typedef test_func_vec_type::iterator test_func_vec_iterator;

  std::cout << "Test Start!!" << std::endl;
  std::cout << "Test count: " << test_functions.size() << std::endl;

  for (test_func_vec_iterator it = test_functions.begin();
       it != test_functions.end();
       ++it) {
    (*it)();
  }

  std::cout << "Test finished!!" << std::endl;
}