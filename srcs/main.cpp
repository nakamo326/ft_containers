#include <cstddef>
#include <iostream>
#include <vector>

class TestClass {
public:
  int* p;
  TestClass() {
    std::cout << "constructor" << std::endl;
    p = new int;
  }
  // TestClass(int num) {
  //   std::cout << "int constructor" << std::endl;
  //   p  = new int;
  //   *p = num;
  // }
  ~TestClass() {
    std::cout << "destructor" << std::endl;
    delete p;
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
