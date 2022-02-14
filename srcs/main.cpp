#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>

#include "vector.hpp"

int main() {
  // 文字列の入力ストリームにデータを入れる
  std::stringstream ss;
  ss << 1 << std::endl << 2 << std::endl << 3;

  // 文字列の入力ストリームからデータを読み込むイテレータを作る
  std::istream_iterator<int> beg(ss);
  std::istream_iterator<int> last;

  ft::vector<int> v;
  v.assign(beg, last);
  for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    std::cout << *it << std::endl;
  }

  std::vector<int> tmp(5);
  for (size_t i = 0; i < 5; i++) {
    tmp[i] = i;
  }

  v.assign(tmp.begin(), tmp.end());
  for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    std::cout << *it << std::endl;
  }
  return 0;
}
