#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
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
  std::srand(std::time(NULL));
  ft::map<int, int, std::greater<int> > m;
  std::vector<int>                      v;
  for (size_t i = 0; i < 1000; i++) {
    int                                                            r = rand();
    ft::pair<ft::RBtree_iterator<ft::pair<const int, int>*>, bool> ret =
        m.insert(ft::make_pair(r, r));
    if (ret.second)
      v.push_back(r);
  }
  std::sort(v.begin(), v.end(), std::greater<int>());
  std::vector<int>::iterator  vit = v.begin();
  ft::map<int, int>::iterator mit = m.begin();
  for (; vit != v.end(); vit++) {
    std::cout << *vit << std::endl;
    std::cout << mit->first << std::endl;
    if (*vit != mit->first)
      std::cout << "not equal" << std::endl;
    mit++;
  }

  return 0;
}
