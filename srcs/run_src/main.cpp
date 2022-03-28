#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
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
  // {
  //   std::map<int, int> v;
  //   for (size_t i = 0; i < 50; i++) {
  //     v.insert(v.begin(), std::make_pair(i, i));
  //   }
  //   print_map(v);
  // }
  // {
  //   ft::map<int, int> v;
  //   for (size_t i = 0; i < 50; i++) {
  //     v.insert(v.begin(), ft::make_pair(i, i));
  //   }
  //   print_map(v);
  // }

  std::set<int> s;

  s.insert(1);
  s.insert(2);

  std::set<int>::iterator it = s.begin();
  *it                        = 3;

  // {
  //   ft::map<int, int> m;
  //   for (size_t i = 0; i < 100000; i++) {
  //     m.insert(ft::make_pair(i, i));
  //   }
  //   for (size_t i = 0; i < 20000; i++) {
  //     m.erase(m.find(i), m.find(i + 5));
  //   }
  // }

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
