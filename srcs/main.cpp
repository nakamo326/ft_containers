#include <cstddef>
#include <iostream>
#include <vector>

class TestClass {
public:
  int* p;
  TestClass() {
    std::cout << __func__ << std::endl;
    p = new int;
  }
  ~TestClass() {
    std::cout << __func__ << std::endl;
    delete p;
  }
  TestClass(const TestClass& other) {
    std::cout << __func__ << std::endl;
    p  = new int;
    *p = *(other.p);
  }
  TestClass& operator=(const TestClass& other) {
    *p = *(other.p);
    return *this;
  }
};

int main() {
  std::vector<TestClass> v(10);
  return 0;
}
