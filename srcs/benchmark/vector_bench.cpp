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

  for (size_t i = 0; i < 1000000; i++) {
    v.get_allocator();
  }
}
void vec_get_allocator_ft(void) {
  ft::vector<int> v;

  for (size_t i = 0; i < 1000000; i++) {
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

void vec_at_std(void) {
  int n;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 100000; i++) {
      n = pre_v.at(i);
    }
  }
}
void vec_at_ft(void) {
  int n;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 100000; i++) {
      n = pre_f.at(i);
    }
  }
}

void vec_front_std(void) {
  int n;

  for (size_t i = 0; i < 10000000; i++) {
    n = pre_v.front();
  }
}
void vec_front_ft(void) {
  int n;

  for (size_t i = 0; i < 10000000; i++) {
    n = pre_f.front();
  }
}

void vec_back_std(void) {
  int n;

  for (size_t i = 0; i < 10000000; i++) {
    n = pre_v.back();
  }
}
void vec_back_ft(void) {
  int n;

  for (size_t i = 0; i < 10000000; i++) {
    n = pre_f.back();
  }
}

void vec_begin_std(void) {
  std::vector<int>::iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_v.begin();
  }
}
void vec_begin_ft(void) {
  ft::vector<int>::iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_f.begin();
  }
}

void vec_end_std(void) {
  std::vector<int>::iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_v.end();
  }
}
void vec_end_ft(void) {
  ft::vector<int>::iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_f.end();
  }
}

void vec_rbegin_std(void) {
  std::vector<int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_v.rbegin();
  }
}
void vec_rbegin_ft(void) {
  ft::vector<int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_f.rbegin();
  }
}

void vec_rend_std(void) {
  std::vector<int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_v.rend();
  }
}
void vec_rend_ft(void) {
  ft::vector<int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_f.rend();
  }
}

void vec_empty_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_v.empty()) {
      num++;
    };
  }
}
void vec_empty_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_f.empty()) {
      num++;
    };
  }
}

void vec_size_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_v.size()) {
      num++;
    };
  }
}
void vec_size_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_f.size()) {
      num++;
    };
  }
}

void vec_capacity_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_v.capacity()) {
      num++;
    };
  }
}
void vec_capacity_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_f.capacity()) {
      num++;
    };
  }
}

void vec_max_size_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_v.max_size()) {
      num++;
    };
  }
}
void vec_max_size_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_f.max_size()) {
      num++;
    };
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
  Benchmark("at", vec_at_std, vec_at_ft);
  Benchmark("front", vec_front_std, vec_front_ft);
  Benchmark("back", vec_back_std, vec_back_ft);
  Benchmark("begin", vec_begin_std, vec_begin_ft);
  Benchmark("end", vec_end_std, vec_end_ft);
  Benchmark("rbegin", vec_rbegin_std, vec_rbegin_ft);
  Benchmark("rend", vec_rend_std, vec_rend_ft);
  Benchmark("empty", vec_empty_std, vec_empty_ft);
  Benchmark("size", vec_size_std, vec_size_ft);
  Benchmark("capacity", vec_capacity_std, vec_capacity_ft);
  Benchmark("max_size", vec_max_size_std, vec_max_size_ft);
}
