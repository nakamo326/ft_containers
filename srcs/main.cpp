#include <cstddef>
#include <iostream>
#include <list>
#include <vector>

#include "vector.hpp"

int main() {
  std::vector<int> v;
  v.reserve(v.max_size());
  return 0;
}
