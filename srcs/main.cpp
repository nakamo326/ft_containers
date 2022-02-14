#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>

#include "vector.hpp"

template <typename T>
void outputVector(ft::vector<T> vec) {
  for (size_t i = 0; i < vec.size() - 1; i++) {
    std::cout << vec.at(i) << " ";
  }
  std::cout << vec.back() << std::endl;
}

int main() {
  std::stringstream ss;
  ss << 1 << std::endl << 2 << std::endl << 3;

  std::istream_iterator<int> beg(ss);
  std::istream_iterator<int> last;

  ft::vector<int> v(10, 42);
  outputVector(v);
  v.insert(v.begin() + 2, beg, last);
  outputVector(v);

  return 0;
}

// int main() {
//   std::stringstream ss;
//   ss << 1 << std::endl << 2 << std::endl << 3;

//   std::istream_iterator<int> beg(ss);
//   std::istream_iterator<int> last;

//   ft::vector<int> v;
//   v.assign(beg, last);
//   for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//     std::cout << *it << std::endl;
//   }

//   std::vector<int> tmp(5);
//   for (size_t i = 0; i < 5; i++) {
//     tmp[i] = i;
//   }

//   v.assign(tmp.begin(), tmp.end());
//   for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//     std::cout << *it << std::endl;
//   }
//   return 0;
// }
