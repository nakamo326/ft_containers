#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>

#include "Color.hpp"
#include "benchmark/Benchmark.hpp"
#include "set.hpp"

std::set<int>    pre_ss;
ft::set<int>     pre_fs;
std::vector<int> random_v_s(50000);

template <typename T>
void set_construct_value(void) {
  for (size_t i = 0; i < 1000000; i++) {
    T m;
    m.insert(0);
  }
}

void set_construct_iter_std(void) {
  for (size_t i = 0; i < 500; i++) {
    std::set<int> v(pre_ss.begin(), pre_ss.end());
  }
}

void set_construct_iter_ft(void) {
  for (size_t i = 0; i < 500; i++) {
    ft::set<int> v(pre_fs.begin(), pre_fs.end());
  }
}

void set_copy_construct_std(void) {
  for (size_t i = 0; i < 500; i++) {
    std::set<int> v(pre_ss);
  }
}

void set_copy_construct_ft(void) {
  for (size_t i = 0; i < 500; i++) {
    ft::set<int> v(pre_fs);
  }
}

void set_assignation_op_std(void) {
  std::set<int> v;
  for (size_t i = 0; i < 500; i++) {
    v = pre_ss;
  }
}

void set_assignation_op_ft(void) {
  ft::set<int> v;
  for (size_t i = 0; i < 500; i++) {
    v = pre_fs;
  }
}

template <typename T>
void set_get_allocator(void) {
  T                          v;
  typename T::allocator_type a;

  for (size_t i = 0; i < 10000000; i++) {
    a = v.get_allocator();
  }
}

void set_begin_std(void) {
  std::set<int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_ss.begin();
  }
}
void set_begin_ft(void) {
  ft::set<int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_fs.begin();
  }
}

void set_end_std(void) {
  std::set<int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_ss.end();
  }
}
void set_end_ft(void) {
  ft::set<int>::iterator it;

  for (size_t i = 0; i < 100000000; i++) {
    it = pre_fs.end();
  }
}

void set_rbegin_std(void) {
  std::set<int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_ss.rbegin();
  }
}
void set_rbegin_ft(void) {
  ft::set<int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_fs.rbegin();
  }
}

void set_rend_std(void) {
  std::set<int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_ss.rend();
  }
}
void set_rend_ft(void) {
  ft::set<int>::reverse_iterator it;

  for (size_t i = 0; i < 10000000; i++) {
    it = pre_fs.rend();
  }
}

void set_empty_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_ss.empty()) {
      num++;
    };
  }
}
void set_empty_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_fs.empty()) {
      num++;
    };
  }
}

void set_size_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_ss.size()) {
      num++;
    };
  }
}
void set_size_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_fs.size()) {
      num++;
    };
  }
}

void set_max_size_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_ss.max_size()) {
      num++;
    };
  }
}
void set_max_size_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_fs.max_size()) {
      num++;
    };
  }
}

void set_insert_std(void) {
  std::set<int> m;
  for (size_t i = 0; i < 50000; i++) {
    m.insert(i);
  }
}

void set_insert_ft(void) {
  ft::set<int> m;
  for (size_t i = 0; i < 50000; i++) {
    m.insert(i);
  }
}

void set_insert_pos_std(void) {
  std::set<int> m;

  for (size_t i = 0; i < 50000; i++) {
    if (i % 4 == 0) {
      m.insert(m.begin(), random_v_s[i]);
    } else if (i % 4 == 1) {
      m.insert(m.end(), random_v_s[i]);
    } else if (i % 4 == 2) {
      m.insert(m.upper_bound(random_v_s[i]), random_v_s[i]);
    } else if (i % 4 == 3) {
      m.insert(m.lower_bound(random_v_s[i]), random_v_s[i]);
    }
  }
}

void set_insert_pos_ft(void) {
  ft::set<int> m;

  for (size_t i = 0; i < 50000; i++) {
    if (i % 4 == 0) {
      m.insert(m.begin(), random_v_s[i]);
    } else if (i % 4 == 1) {
      m.insert(m.end(), random_v_s[i]);
    } else if (i % 4 == 2) {
      m.insert(m.upper_bound(random_v_s[i]), random_v_s[i]);
    } else if (i % 4 == 3) {
      m.insert(m.lower_bound(random_v_s[i]), random_v_s[i]);
    }
  }
}

void set_insert_iter_std(void) {
  std::set<int> m;
  for (size_t i = 0; i < 10; i++) {
    m.insert(pre_ss.begin(), pre_ss.end());
  }
}

void set_insert_iter_ft(void) {
  ft::set<int> m;
  for (size_t i = 0; i < 10; i++) {
    m.insert(pre_fs.begin(), pre_fs.end());
  }
}

void set_erase_pos_std(void) {
  std::set<int> m(pre_ss);
  for (size_t i = 0; i < 100000; i++) {
    m.erase(m.begin());
  }
}

void set_erase_pos_ft(void) {
  ft::set<int> m(pre_fs);
  for (size_t i = 0; i < 100000; i++) {
    m.erase(m.begin());
  }
}

void set_erase_std(void) {
  std::set<int> m(pre_ss);
  for (size_t i = 0; i < 100000; i++) {
    m.erase(i);
  }
}

void set_erase_ft(void) {
  ft::set<int> m(pre_fs);
  for (size_t i = 0; i < 100000; i++) {
    m.erase(i);
  }
}

void set_erase_iter_std(void) {
  std::set<int> m(pre_ss);
  for (size_t i = 0; i < 20000; i++) {
    m.erase(m.find(i * 5), m.find((i + 1) * 5));
  }
}

void set_erase_iter_ft(void) {
  ft::set<int> m(pre_fs);
  for (size_t i = 0; i < 20000; i++) {
    m.erase(m.find(i * 5), m.find((i + 1) * 5));
  }
}

void set_swap_std(void) {
  std::set<int> m;
  for (size_t i = 0; i < 100000; i++) {
    m.swap(pre_ss);
  }
}

void set_swap_ft(void) {
  ft::set<int> m;
  for (size_t i = 0; i < 100000; i++) {
    m.swap(pre_fs);
  }
}

void set_clear_std(void) {
  std::set<int> m(pre_ss);
  for (size_t i = 0; i < 20000; i++) {
    m.clear();
  }
}

void set_clear_ft(void) {
  ft::set<int> m(pre_fs);
  for (size_t i = 0; i < 20000; i++) {
    m.clear();
  }
}

void set_count_std(void) {
  size_t res = 0;
  for (size_t i = 0; i < 100000; i++) {
    res += pre_ss.count(i);
  }
  std::cerr << res << std::endl;
}

void set_count_ft(void) {
  size_t res = 0;
  for (size_t i = 0; i < 100000; i++) {
    res += pre_fs.count(i);
  }
  std::cerr << res << std::endl;
}

void set_find_std(void) {
  size_t                  count = 0;
  std::set<int>::iterator it;
  for (size_t i = 0; i < 100000; i++) {
    it = pre_ss.find(i);
    if (it != pre_ss.end())
      count++;
  }
  std::cerr << count << std::endl;
}

void set_find_ft(void) {
  size_t                 count = 0;
  ft::set<int>::iterator it;
  for (size_t i = 0; i < 100000; i++) {
    it = pre_fs.find(i);
    if (it != pre_fs.end())
      count++;
  }
  std::cerr << count << std::endl;
}

void set_equal_range_std(void) {
  typedef std::set<int>::iterator it;
  std::pair<it, it>               res;
  size_t                          count = 0;

  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 100000; i++) {
      res = pre_ss.equal_range(i);
      if (res.first != pre_ss.end())
        count++;
    }
  }
  std::cerr << count << std::endl;
}

void set_equal_range_ft(void) {
  typedef ft::set<int>::iterator it;
  ft::pair<it, it>               res;
  size_t                         count = 0;
  for (size_t j = 0; j < 10; j++) {
    for (size_t i = 0; i < 100000; i++) {
      res = pre_fs.equal_range(i);
      if (res.first != pre_fs.end())
        count++;
    }
  }
  std::cerr << count << std::endl;
}

void set_lower_bound_std(void) {
  size_t                  count = 0;
  std::set<int>::iterator it;
  for (size_t i = 0; i < 100000; i++) {
    it = pre_ss.lower_bound(i);
    if (it != pre_ss.end())
      count++;
  }
  std::cerr << count << std::endl;
}

void set_lower_bound_ft(void) {
  size_t                 count = 0;
  ft::set<int>::iterator it;
  for (size_t i = 0; i < 100000; i++) {
    it = pre_fs.lower_bound(i);
    if (it != pre_fs.end())
      count++;
  }
  std::cerr << count << std::endl;
}

void set_upper_bound_std(void) {
  size_t                  count = 0;
  std::set<int>::iterator it;
  for (size_t i = 0; i < 100000; i++) {
    it = pre_ss.upper_bound(i);
    if (it != pre_ss.end())
      count++;
  }
  std::cerr << count << std::endl;
}

void set_upper_bound_ft(void) {
  size_t                 count = 0;
  ft::set<int>::iterator it;
  for (size_t i = 0; i < 100000; i++) {
    it = pre_fs.upper_bound(i);
    if (it != pre_fs.end())
      count++;
  }
  std::cerr << count << std::endl;
}

// ======================================================
void set_bench_entry(void) {
  std::srand(std::time(NULL));

  for (size_t i = 0; i < 100000; i++) {
    pre_ss.insert(i);
    pre_fs.insert(i);
  }

  for (size_t i = 0; i < 50000; i++) {
    random_v_s[i] = i;
  }
  for (size_t i = 50000; i > 1; --i) {
    size_t a = i - 1;
    size_t b = std::rand() % i;
    std::swap(random_v_s[a], random_v_s[b]);
  }

  std::cout << GRN "[ -------- ] " NC << "Set" << std::endl;
  Benchmark("constructValue",
            set_construct_value<std::set<int> >,
            set_construct_value<ft::set<int> >);
  Benchmark("constructIter", set_construct_iter_std, set_construct_iter_ft);
  Benchmark("copyconstructor", set_copy_construct_std, set_copy_construct_ft);
  Benchmark("assignationOp", set_assignation_op_std, set_assignation_op_ft);
  Benchmark("getAllocator",
            set_get_allocator<std::set<int> >,
            set_get_allocator<ft::set<int> >);
  Benchmark("begin", set_begin_std, set_begin_ft);
  Benchmark("end", set_end_std, set_end_ft);
  Benchmark("rbegin", set_rbegin_std, set_rbegin_ft);
  Benchmark("rend", set_rend_std, set_rend_ft);
  Benchmark("empty", set_empty_std, set_empty_ft);
  Benchmark("size", set_size_std, set_size_ft);
  Benchmark("max_size", set_max_size_std, set_max_size_ft);
  Benchmark("insert", set_insert_std, set_insert_ft);
  Benchmark("insertPosition", set_insert_pos_std, set_insert_pos_ft);
  Benchmark("insertIter", set_insert_iter_std, set_insert_iter_ft);

  Benchmark("erasePos", set_erase_pos_std, set_erase_pos_ft);
  Benchmark("erase", set_erase_std, set_erase_ft);
  Benchmark("eraseIter", set_erase_iter_std, set_erase_iter_ft);
  Benchmark("swap", set_swap_std, set_swap_ft);
  Benchmark("clear", set_clear_std, set_clear_ft);
  Benchmark("count", set_count_std, set_count_ft);
  Benchmark("find", set_find_std, set_find_ft);
  Benchmark("equal_range", set_equal_range_std, set_equal_range_ft);
  Benchmark("lower_bound", set_lower_bound_std, set_lower_bound_ft);
  Benchmark("upper_bound", set_upper_bound_std, set_upper_bound_ft);

  std::cout << std::endl;
}
