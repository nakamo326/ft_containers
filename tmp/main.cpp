#include "ft_container.hpp"
#include "test_frame.hpp"
#include "tests/vector_test.hpp"

int main() {
  {
    Suite s("vector Suite");
    s.add_test(Test("Vector_constructor", Vector_constructor));
    s.add_test(
        Test("vector_constructorWithAlloc", Vector_constructorWithAlloc));
    s.add_test(Test("Vector_ConstructorWithSize", Vector_ConstructorWithSize));
    s.add_test(
        Test("Vector_ConstructorWithValue", Vector_ConstructorWithValue));
    s.add_test(Test("Vector_RangeConstructor", Vector_RangeConstructor));
    s.add_test(Test("Vector_CopyConstructor", Vector_CopyConstructor));
    s.add_test(Test("Vector_AssignationOverload", Vector_AssignationOverload));
  }
  return 0;
}
