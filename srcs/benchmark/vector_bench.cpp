#include <vector>

#include "benchmark/Benchmark.hpp"
#include "vector.hpp"

void simple_assign_std(void) {
  std::vector<int> v;

  for (size_t i = 0; i < 20000; i++) {
    v.assign(i, 42);
  }
}

void simple_assign_ft(void) {
  ft::vector<int> v;

  for (size_t i = 0; i < 20000; i++) {
    v.assign(i, 42);
  }
}

void vector_bench_entry(void) {
  Benchmark("simpleAssign", simple_assign_std, simple_assign_ft);
}
