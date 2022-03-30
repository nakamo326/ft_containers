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
  return 0;
}
