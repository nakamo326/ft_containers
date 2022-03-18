#include <vector>

#include "benchmark/Benchmark.hpp"
#include "vector.hpp"

std::vector<int> pre_v(100000);
ft::vector<int>  pre_f(100000);

void vec_construct_value_std(void) {
  for (size_t i = 0; i < 20000; i++) {
    std::vector<int> v(i, 42);
  }
}
void vec_construct_value_ft(void) {
  for (size_t i = 0; i < 20000; i++) {
    ft::vector<int> v(i, 42);
  }
}

void vec_construct_iter_std(void) {
  for (size_t i = 0; i < 10000; i++) {
    std::vector<int> v(pre_v.begin(), pre_v.end());
  }
}
void vec_construct_iter_ft(void) {
  for (size_t i = 0; i < 10000; i++) {
    ft::vector<int> v(pre_v.begin(), pre_v.end());
  }
}

void vec_simple_assign_std(void) {
  std::vector<int> v;

  for (size_t i = 0; i < 20000; i++) {
    v.assign(i, 42);
  }
}
void vec_simple_assign_ft(void) {
  ft::vector<int> v;

  for (size_t i = 0; i < 20000; i++) {
    v.assign(i, 42);
  }
}

void vec_range_assign_std(void) {
  std::vector<int> v;

  for (size_t i = 0; i < 10000; i++) {
    v.assign(pre_v.begin(), pre_v.end());
  }
}
void vec_range_assign_ft(void) {
  ft::vector<int> v;

  for (size_t i = 0; i < 10000; i++) {
    v.assign(pre_v.begin(), pre_v.end());
  }
}

void vec_get_allocator_std(void) {
  std::vector<int> v;

  for (size_t i = 0; i < 100000; i++) {
    v.get_allocator();
  }
}
void vec_get_allocator_ft(void) {
  ft::vector<int> v;

  for (size_t i = 0; i < 100000; i++) {
    v.get_allocator();
  }
}

void vec_array_op_std(void) {
  int n;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 100000; i++) {
      n = pre_v[i];
    }
  }
}
void vec_array_op_ft(void) {
  int n;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 100000; i++) {
      n = pre_f[i];
    }
  }
}

// ======================================================
void vector_bench_entry(void) {
  for (size_t i = 0; i < 100000; i++) {
    pre_v[i] = i;
    pre_f[i] = i;
  }

  Benchmark("constructValue", vec_construct_value_std, vec_construct_value_ft);
  Benchmark("constructIter", vec_construct_iter_std, vec_construct_iter_ft);
  Benchmark("simpleAssign", vec_simple_assign_std, vec_simple_assign_ft);
  Benchmark("rangeAssign", vec_range_assign_std, vec_range_assign_ft);
  Benchmark("getAllocator", vec_get_allocator_std, vec_get_allocator_ft);
  Benchmark("arrayOperator", vec_array_op_std, vec_array_op_ft);
}
