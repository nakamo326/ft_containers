#include <vector>

#include "benchmark.hpp"
#include "vector.hpp"

int main(void) {
  NS::vector<int> v;
  v.push_back(5);
  std::cout << v[0] << std::endl;
  return 0;
}
