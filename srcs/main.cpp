#include <cstddef>
#include <vector>

int main() {
  std::vector<int> v;
  for (size_t i = 0; i < 1000; i++) {
    v.push_back(i);
  }
}
