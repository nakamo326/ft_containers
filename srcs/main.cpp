#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <sstream>
#include <vector>

#include "function.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"

template <typename T>
void outputVector(ft::vector<T> vec) {
  for (size_t i = 0; i < vec.size() - 1; i++) {
    std::cout << vec.at(i) << " ";
  }
  std::cout << vec.back() << std::endl;
}

template <typename Map>
void print_map(Map& m) {
  std::cout << '{';
  typename Map::iterator it(m.begin());
  for (; it != m.end(); it++)
    std::cout << it->first << ':' << it->second << ' ';
  std::cout << "}\n";
}

int main() {
  std::map<int, int> m;
  m[0] = 42;
  m[5] = 5;
  m[2] = 2;
  m[3] = 3;

  std::map<int, int> from;
  from[0] = 57;
  from[1] = 99;

  m       = from;
  from[5] = 5;

  std::cout << "\nm = ";
  print_map(m);
  std::cout << "\nfrom = ";
  print_map(from);

  ft::map<int, int> ftm;
  ftm.find(0);

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
//   std::cout << "===========" << std::endl;
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
