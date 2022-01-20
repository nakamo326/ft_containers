#include "ft_container.hpp"

int main() {
  int array[] = {1, 2, 3, 4, 5};
  NS::vector<int> v(array, array + 5);
  std::cout << "v.size() = " << v.size() << std::endl;
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;

  // test erase
  std::cout << "========== erase ===========" << std::endl;
  NS::vector<int>::iterator it = v.begin();
  std::cout << "v.erase(it)" << std::endl;
  NS::vector<int>::iterator it2 = v.erase(it);
  std::cout << "v.size() = " << v.size() << std::endl;
  std::cout << "it2 = " << *it2 << std::endl;
  std::cout << "v.erase(it2)" << std::endl;
  NS::vector<int>::iterator it3 = v.erase(it2);
  std::cout << "v.size() = " << v.size() << std::endl;
  std::cout << "it3 = " << *it3 << std::endl;

  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
