#include <cassert>
#include <vector>

#include "vector.hpp"

void Vector_constructor() {
  std::vector<int> s;
  ft::vector<int>  f;
  assert(s.size() == f.size());
  assert(s.max_size() == f.max_size());
  assert(s.capacity() == f.capacity());
  assert(s.get_allocator() == f.get_allocator());
}

void Vector_constructorWithAlloc() {
  std::allocator<int> alloc;
  std::vector<int>    s(alloc);
  ft::vector<int>     f(alloc);
  assert(s.size() == f.size());
  assert(s.max_size() == f.max_size());
  assert(s.capacity() == f.capacity());
  assert(s.get_allocator() == f.get_allocator());
}

void Vector_ConstructorWithSize() {
  std::vector<int> s(100);
  ft::vector<int>  f(100);
  assert(s.size() == f.size());
  assert(s.max_size() == f.max_size());
  assert(s.capacity() == f.capacity());
  assert(s.get_allocator() == f.get_allocator());
}

void Vector_ConstructorWithValue() {
  std::vector<int> s(1000, 55);
  ft::vector<int>  f(1000, 55);
  assert(s.size() == f.size());
  assert(s.max_size() == f.max_size());
  assert(s.capacity() == f.capacity());
  assert(s.get_allocator() == f.get_allocator());
  for (size_t i = 0; i < 1000; i++) {
    assert(s[i] == f[i]);
  }
}

void Vector_RangeConstructor() {
  std::vector<int> s(1000);
  for (size_t i = 0; i < 1000; i++) {
    s[i] = i;
  }
  ft::vector<int> f(s.begin(), s.end());
  assert(f.size() == s.size());
  assert(f.max_size() == s.max_size());
  assert(f.capacity() == s.capacity());
  assert(f.get_allocator() == s.get_allocator());
  for (size_t i = 0; i < 1000; i++) {
    assert(f[i] == s[i]);
  }
}

void Vector_CopyConstructor() {
  ft::vector<int> f(1000);
  for (size_t i = 0; i < 1000; i++) {
    f[i] = i;
  }
  ft::vector<int> c(f);
  assert(f.size() == c.size());
  assert(f.max_size() == c.max_size());
  assert(f.capacity() == c.capacity());
  assert(f.get_allocator() == c.get_allocator());
  for (size_t i = 0; i < 1000; i++) {
    assert(f[i] == c[i]);
  }
}

void Vector_AssignationOverload() {
  ft::vector<int>  f(1000);
  std::vector<int> s(1000);
  for (size_t i = 0; i < 1000; i++) {
    f[i] = i;
    s[i] = i;
  }
  // big to small
  {
    ft::vector<int>  cf(100);
    std::vector<int> cs(100);
    cf = f;
    cs = s;
    assert(cf.size() == cs.size());
    assert(cf.max_size() == cs.max_size());
    assert(cf.capacity() == cs.capacity());
    assert(cf.get_allocator() == cs.get_allocator());
    for (size_t i = 0; i < 1000; i++) {
      assert(cf[i] == cs[i]);
    }
  }
  // small to big
  {
    ft::vector<int>  cf(10000);
    std::vector<int> cs(10000);
    cf = f;
    cs = s;
    assert(cf.size() == cs.size());
    assert(cf.capacity() == cs.capacity());
    for (size_t i = 0; i < 1000; i++) {
      assert(cf[i] == cs[i]);
    }
  }
}
