#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

#include "Color.hpp"
#include "benchmark/Benchmark.hpp"
#include "map.hpp"

std::map<int, int> pre_sm;
ft::map<int, int>  pre_fm;
std::vector<int>   random_v(50000);

template <typename T>
void map_construct_value(void) {
  for (size_t i = 0; i < 100000; i++) {
    T m;
  }
}

void map_construct_iter_std(void) {
  for (size_t i = 0; i < 500; i++) {
    std::map<int, int> v(pre_sm.begin(), pre_sm.end());
  }
}

void map_construct_iter_ft(void) {
  for (size_t i = 0; i < 500; i++) {
    ft::map<int, int> v(pre_fm.begin(), pre_fm.end());
  }
}

void map_copy_construct_std(void) {
  for (size_t i = 0; i < 500; i++) {
    std::map<int, int> v(pre_sm);
  }
}

void map_copy_construct_ft(void) {
  for (size_t i = 0; i < 500; i++) {
    ft::map<int, int> v(pre_fm);
  }
}

void map_assignation_op_std(void) {
  std::map<int, int> v;
  for (size_t i = 0; i < 500; i++) {
    v = pre_sm;
  }
}

void map_assignation_op_ft(void) {
  ft::map<int, int> v;
  for (size_t i = 0; i < 500; i++) {
    v = pre_fm;
  }
}

template <typename T>
void map_get_allocator(void) {
  T                          v;
  typename T::allocator_type a;

  for (size_t i = 0; i < 10000000; i++) {
    a = v.get_allocator();
  }
}

void map_array_op_std(void) {
  int n;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 1000000; i++) {
      n = pre_sm[i];
    }
  }
}
void map_array_op_ft(void) {
  int n;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 1000000; i++) {
      n = pre_fm[i];
    }
  }
}

void map_begin_std(void) {
  std::map<int, int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_sm.begin();
  }
}
void map_begin_ft(void) {
  ft::map<int, int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_fm.begin();
  }
}

void map_end_std(void) {
  std::map<int, int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_sm.end();
  }
}
void map_end_ft(void) {
  ft::map<int, int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_fm.end();
  }
}

void map_rbegin_std(void) {
  std::map<int, int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_sm.rbegin();
  }
}
void map_rbegin_ft(void) {
  ft::map<int, int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_fm.rbegin();
  }
}

void map_rend_std(void) {
  std::map<int, int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_sm.rend();
  }
}
void map_rend_ft(void) {
  ft::map<int, int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_fm.rend();
  }
}

void map_empty_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_sm.empty()) {
      num++;
    };
  }
}
void map_empty_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_fm.empty()) {
      num++;
    };
  }
}

void map_size_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_sm.size()) {
      num++;
    };
  }
}
void map_size_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_fm.size()) {
      num++;
    };
  }
}

void map_max_size_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_sm.max_size()) {
      num++;
    };
  }
}
void map_max_size_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_fm.max_size()) {
      num++;
    };
  }
}

void map_insert_std(void) {
  std::map<int, int> m;
  for (size_t i = 0; i < 50000; i++) {
    m.insert(std::make_pair(i, i));
  }
}

void map_insert_ft(void) {
  ft::map<int, int> m;
  for (size_t i = 0; i < 50000; i++) {
    m.insert(ft::make_pair(i, i));
  }
}

void map_insert_pos_std(void) {
  std::map<int, int> m;

  for (size_t i = 0; i < 50000; i++) {
    if (i % 4 == 0) {
      m.insert(m.begin(), std::make_pair(random_v[i], random_v[i]));
    } else if (i % 4 == 1) {
      m.insert(m.end(), std::make_pair(random_v[i], random_v[i]));
    } else if (i % 4 == 2) {
      m.insert(m.upper_bound(random_v[i]),
               std::make_pair(random_v[i], random_v[i]));
    } else if (i % 4 == 3) {
      m.insert(m.lower_bound(random_v[i]),
               std::make_pair(random_v[i], random_v[i]));
    }
  }
}

void map_insert_pos_ft(void) {
  ft::map<int, int> m;

  for (size_t i = 0; i < 50000; i++) {
    if (i % 4 == 0) {
      m.insert(m.begin(), ft::make_pair(random_v[i], random_v[i]));
    } else if (i % 4 == 1) {
      m.insert(m.end(), ft::make_pair(random_v[i], random_v[i]));
    } else if (i % 4 == 2) {
      m.insert(m.upper_bound(random_v[i]),
               ft::make_pair(random_v[i], random_v[i]));
    } else if (i % 4 == 3) {
      m.insert(m.lower_bound(random_v[i]),
               ft::make_pair(random_v[i], random_v[i]));
    }
  }
}

void map_insert_iter_std(void) {
  std::map<int, int> m;
  for (size_t i = 0; i < 10; i++) {
    m.insert(pre_sm.begin(), pre_sm.end());
  }
}

void map_insert_iter_ft(void) {
  ft::map<int, int> m;
  for (size_t i = 0; i < 10; i++) {
    m.insert(pre_fm.begin(), pre_fm.end());
  }
}

void map_erase_pos_std(void) {
  std::map<int, int> m(pre_sm);
  for (size_t i = 0; i < 100000; i++) {
    m.erase(m.begin());
  }
}

void map_erase_pos_ft(void) {
  ft::map<int, int> m(pre_fm);
  for (size_t i = 0; i < 100000; i++) {
    m.erase(m.begin());
  }
}

void map_erase_std(void) {
  std::map<int, int> m(pre_sm);
  for (size_t i = 0; i < 100000; i++) {
    m.erase(i);
  }
}

void map_erase_ft(void) {
  ft::map<int, int> m(pre_fm);
  for (size_t i = 0; i < 100000; i++) {
    m.erase(i);
  }
}

void map_erase_iter_std(void) {
  std::map<int, int> m(pre_sm);
  for (size_t i = 0; i < 20000; i++) {
    m.erase(m.find(i * 5), m.find((i + 1) * 5));
  }
}

void map_erase_iter_ft(void) {
  ft::map<int, int> m(pre_fm);
  for (size_t i = 0; i < 20000; i++) {
    m.erase(m.find(i * 5), m.find((i + 1) * 5));
  }
}

void map_swap_std(void) {
  std::map<int, int> m;
  for (size_t i = 0; i < 100000; i++) {
    m.swap(pre_sm);
  }
}

void map_swap_ft(void) {
  ft::map<int, int> m;
  for (size_t i = 0; i < 100000; i++) {
    m.swap(pre_fm);
  }
}

void map_clear_std(void) {
  std::map<int, int> m(pre_sm);
  for (size_t i = 0; i < 20000; i++) {
    m.clear();
  }
}

void map_clear_ft(void) {
  ft::map<int, int> m(pre_fm);
  for (size_t i = 0; i < 20000; i++) {
    m.clear();
  }
}

void map_count_std(void) {
  for (size_t i = 0; i < 100000; i++) {
    pre_sm.count(i);
  }
}

void map_count_ft(void) {
  for (size_t i = 0; i < 100000; i++) {
    pre_fm.count(i);
  }
}

void map_find_std(void) {
  for (size_t i = 0; i < 100000; i++) {
    pre_sm.find(i);
  }
}

void map_find_ft(void) {
  for (size_t i = 0; i < 100000; i++) {
    pre_fm.find(i);
  }
}

// ======================================================
void map_bench_entry(void) {
  std::srand(std::time(NULL));

  for (size_t i = 0; i < 100000; i++) {
    pre_sm.insert(std::make_pair(i, i));
    pre_fm.insert(ft::make_pair(i, i));
  }

  for (size_t i = 0; i < 50000; i++) {
    random_v[i] = i;
  }
  for (size_t i = 50000; i > 1; --i) {
    size_t a = i - 1;
    size_t b = std::rand() % i;
    std::swap(random_v[a], random_v[b]);
  }

  std::cout << GRN "[ -------- ] " NC << "Map" << std::endl;
  Benchmark("constructValue",
            map_construct_value<std::map<int, int> >,
            map_construct_value<ft::map<int, int> >);
  Benchmark("constructIter", map_construct_iter_std, map_construct_iter_ft);
  Benchmark("copyconstructor", map_copy_construct_std, map_copy_construct_ft);
  Benchmark("assignationOp", map_assignation_op_std, map_assignation_op_ft);
  Benchmark("getAllocator",
            map_get_allocator<std::map<int, int> >,
            map_get_allocator<ft::map<int, int> >);
  Benchmark("arrayOperator", map_array_op_std, map_array_op_ft);
  Benchmark("begin", map_begin_std, map_begin_ft);
  Benchmark("end", map_end_std, map_end_ft);
  Benchmark("rbegin", map_rbegin_std, map_rbegin_ft);
  Benchmark("rend", map_rend_std, map_rend_ft);
  Benchmark("empty", map_empty_std, map_empty_ft);
  Benchmark("size", map_size_std, map_size_ft);
  Benchmark("max_size", map_max_size_std, map_max_size_ft);
  Benchmark("insert", map_insert_std, map_insert_ft);
  Benchmark("insertPosition", map_insert_pos_std, map_insert_pos_ft);
  Benchmark("insertIter", map_insert_iter_std, map_insert_iter_ft);

  Benchmark("erasePos", map_erase_pos_std, map_erase_pos_ft);
  Benchmark("erase", map_erase_std, map_erase_ft);
  Benchmark("eraseIter", map_erase_iter_std, map_erase_iter_ft);
  Benchmark("swap", map_swap_std, map_swap_ft);
  Benchmark("clear", map_clear_std, map_clear_ft);
  Benchmark("count", map_count_std, map_count_ft);
  Benchmark("count", map_find_std, map_find_ft);

  std::cout << std::endl;
}
