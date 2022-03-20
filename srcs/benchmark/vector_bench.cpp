#include <vector>

#include "benchmark/Benchmark.hpp"
#include "vector.hpp"

std::vector<int> pre_v(100000);
ft::vector<int>  pre_f(100000);

template <typename T>
void vec_construct_value(void) {
  for (size_t i = 0; i < 100000; i++) {
    T v(i, 42);
  }
}

template <typename T>
void vec_construct_iter(void) {
  for (size_t i = 0; i < 100000; i++) {
    T v(pre_v.begin(), pre_v.end());
  }
}

template <typename T>
void vec_simple_assign(void) {
  T v;

  for (size_t i = 0; i < 100000; i++) {
    v.assign(i, 42);
  }
}

template <typename T>
void vec_range_assign(void) {
  T v;

  for (size_t i = 0; i < 100000; i++) {
    v.assign(pre_v.begin(), pre_v.end());
  }
}

template <typename T>
void vec_get_allocator(void) {
  T                          v;
  typename T::allocator_type a;

  for (size_t i = 0; i < 10000000; i++) {
    a = v.get_allocator();
  }
}

void vec_array_op_std(void) {
  int n;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 1000000; i++) {
      n = pre_v[i];
    }
  }
}
void vec_array_op_ft(void) {
  int n;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 1000000; i++) {
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

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_v.begin();
  }
}
void vec_begin_ft(void) {
  ft::vector<int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_f.begin();
  }
}

void vec_end_std(void) {
  std::vector<int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_v.end();
  }
}
void vec_end_ft(void) {
  ft::vector<int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
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

template <typename T>
void vec_reserve(void) {
  T v(1000);
  for (size_t i = 0; i < 1000; i++) {
    v[i] = i;
  }

  for (size_t i = 0; i < 100000; i++) {
    v.reserve(i);
  }
}

template <typename T>
void vec_clear(void) {
  for (size_t i = 0; i < 50000; i++) {
    T v(i);
    v.clear();
  }
}

template <typename T>
void vec_insert(void) {
  T v;
  for (size_t i = 0; i < 50000; i++) {
    v.insert(v.begin(), i);
  }
}

template <typename T>
void vec_insert_count(void) {
  T v;
  for (size_t i = 0; i < 2000; i++) {
    v.insert(v.begin(), i, i);
  }
}

template <typename T>
void vec_insert_iter(void) {
  T v;
  for (size_t i = 0; i < 200; i++) {
    v.insert(v.begin(), pre_v.begin(), pre_v.end());
  }
}

// ======================================================
void vector_bench_entry(void) {
  for (size_t i = 0; i < 100000; i++) {
    pre_v[i] = i;
    pre_f[i] = i;
  }

  Benchmark("constructValue",
            vec_construct_value<std::vector<int> >,
            vec_construct_value<ft::vector<int> >);
  Benchmark("constructIter",
            vec_construct_iter<std::vector<int> >,
            vec_construct_iter<ft::vector<int> >);
  Benchmark("simpleAssign",
            vec_simple_assign<std::vector<int> >,
            vec_simple_assign<ft::vector<int> >);
  Benchmark("rangeAssign",
            vec_range_assign<std::vector<int> >,
            vec_range_assign<ft::vector<int> >);
  Benchmark("getAllocator",
            vec_get_allocator<std::vector<int> >,
            vec_get_allocator<ft::vector<int> >);
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
  Benchmark(
      "reserve", vec_reserve<std::vector<int> >, vec_reserve<ft::vector<int> >);
  Benchmark("clear", vec_clear<std::vector<int> >, vec_clear<ft::vector<int> >);
  Benchmark(
      "insert", vec_insert<std::vector<int> >, vec_insert<ft::vector<int> >);
  Benchmark("insertCount",
            vec_insert_count<std::vector<int> >,
            vec_insert_count<ft::vector<int> >);
  Benchmark("insertIter",
            vec_insert_iter<std::vector<int> >,
            vec_insert_iter<ft::vector<int> >);
}
