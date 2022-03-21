#include <map>

#include "Color.hpp"
#include "benchmark/Benchmark.hpp"
#include "map.hpp"

std::map<int, int> pre_sm;
ft::map<int, int>  pre_fm;

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
  std::map<int, int> v;
  for (size_t i = 0; i < 50000; i++) {
    v.insert(std::make_pair(i, i));
  }
}

void map_insert_ft(void) {
  ft::map<int, int> v;
  for (size_t i = 0; i < 50000; i++) {
    v.insert(ft::make_pair(i, i));
  }
}

// void map_insert_pos_std(void) {
//   std::map<int, int> v;
//   for (size_t i = 0; i < 50000; i++) {
//     v.insert(v.find(i), std::make_pair(i, i));
//   }
// }

// void map_insert_pos_ft(void) {
//   ft::map<int, int> v;
//   for (size_t i = 0; i < 50000; i++) {
//     v.insert(v.find(i), ft::make_pair(i, i));
//   }
// }

template <typename Map>
void print_map(Map& m) {
  std::cout << '{';
  typename Map::iterator it(m.begin());
  for (; it != m.end(); it++)
    std::cout << it->first << ':' << it->second << ' ';
  std::cout << "}\n";
}

void map_insert_pos_std(void) {
  std::map<int, int> v;
  for (size_t i = 0; i < 50; i++) {
    v.insert(v.begin(), std::make_pair(i, i));
  }
  print_map(v);
}

void map_insert_pos_ft(void) {
  ft::map<int, int> v;
  for (size_t i = 0; i < 50; i++) {
    v.insert(v.begin(), ft::make_pair(i, i));
  }
  print_map(v);
}

/*

template <typename T>
void map_insert_count(void) {
  T v;
  for (size_t i = 0; i < 2000; i++) {
    v.insert(v.begin(), i, i);
  }
}

template <typename T>
void map_insert_iter(void) {
  T v;
  for (size_t i = 0; i < 200; i++) {
    v.insert(v.begin(), pre_v.begin(), pre_v.end());
  }
}

template <typename T>
void map_erase(void) {
  T v(100000);
  for (size_t i = 0; i < 100000; i++) {
    v.erase(v.begin());
  }
}

template <typename T>
void map_erase_iter(void) {
  T v(100000);
  for (size_t i = 0; i < 20000; i++) {
    v.erase(v.begin(), v.begin() + 5);
  }
}

template <typename T>
void map_push_back(void) {
  T v;
  for (size_t i = 0; i < 50000; i++) {
    v.push_back(i);
  }
}

template <typename T>
void map_pop_back(void) {
  T v(1000000, 42);
  for (size_t i = 0; i < 1000000; i++) {
    v.pop_back();
  }
}

template <typename T>
void map_resize(void) {
  T v;
  for (size_t i = 1; i < 1000; i++) {
    v.resize(i * 100);
  }
}

template <typename T>
void map_clear(void) {
  for (size_t i = 0; i < 50000; i++) {
    T v(i);
    v.clear();
  }
}

*/

// ======================================================
void map_bench_entry(void) {
  for (size_t i = 0; i < 100000; i++) {
    pre_sm.insert(std::make_pair(i, i));
    pre_fm.insert(ft::make_pair(i, i));
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

  /*
  Benchmark("insertIter",
            map_insert_iter<std::map<int, int> >,
            map_insert_iter<ft::map<int, int> >);
  Benchmark(
      "erase", map_erase<std::map<int, int> >, map_erase<ft::map<int, int> >);
  Benchmark("eraseIter",
            map_erase_iter<std::map<int, int> >,
            map_erase_iter<ft::map<int, int> >);
  Benchmark("pushback",
            map_push_back<std::map<int, int> >,
            map_push_back<ft::map<int, int> >);
  Benchmark("popback",
            map_pop_back<std::map<int, int> >,
            map_pop_back<ft::map<int, int> >);
  Benchmark("resize",
            map_resize<std::map<int, int> >,
            map_resize<ft::map<int, int> >);
  Benchmark(
      "clear", map_clear<std::map<int, int> >, map_clear<ft::map<int, int> >);
            */
}
