#include <stack>

#include "Color.hpp"
#include "benchmark/Benchmark.hpp"
#include "stack.hpp"

std::stack<int> pre_sstack;
ft::stack<int>  pre_fstack;

template <typename T>
void stk_constructor(void) {
  for (size_t i = 0; i < 10000000; i++) {
    T s;
    s.push(0);
  }
}

void stk_copy_constructor_std(void) {
  for (size_t i = 0; i < 10000; i++) {
    std::stack<int> s(pre_sstack);
  }
}

void stk_copy_constructor_ft(void) {
  for (size_t i = 0; i < 10000; i++) {
    ft::stack<int> s(pre_fstack);
  }
}

void stk_assignation_std(void) {
  for (size_t i = 0; i < 100000; i++) {
    std::stack<int> s;
    s = pre_sstack;
    std::cerr << s.top() << std::endl;
  }
}

void stk_assignation_ft(void) {
  for (size_t i = 0; i < 100000; i++) {
    ft::stack<int> s;
    s = pre_fstack;
    std::cerr << s.top() << std::endl;
  }
}

void stk_top_std(void) {
  size_t n = 0;

  for (size_t i = 0; i < 10000000; i++) {
    n += pre_sstack.top();
  }
  std::cerr << n << std::endl;
}
void stk_top_ft(void) {
  size_t n = 0;

  for (size_t i = 0; i < 10000000; i++) {
    n += pre_fstack.top();
  }
  std::cerr << n << std::endl;
}

void stk_empty_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_sstack.empty()) {
      num++;
    };
  }
  std::cerr << num << std::endl;
}

void stk_empty_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_fstack.empty()) {
      num++;
    };
  }
  std::cerr << num << std::endl;
}

void stk_size_std(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_sstack.size()) {
      num++;
    };
  }
  std::cerr << num << std::endl;
}
void stk_size_ft(void) {
  int num = 0;
  for (size_t i = 0; i < 10000000; i++) {
    if (pre_fstack.size()) {
      num++;
    };
  }
  std::cerr << num << std::endl;
}

template <typename T>
void stk_push(void) {
  T v;
  for (size_t i = 0; i < 50000; i++) {
    v.push(i);
  }
}

void stk_pop_std(void) {
  std::stack<int> s(pre_sstack);
  for (size_t i = 0; i < 100000; i++) {
    s.pop();
  }
}

void stk_pop_ft(void) {
  ft::stack<int> s(pre_fstack);
  for (size_t i = 0; i < 100000; i++) {
    s.pop();
  }
}

// ======================================================
void stack_bench_entry(void) {
  for (size_t i = 0; i < 100000; i++) {
    pre_sstack.push(i);
    pre_fstack.push(i);
  }
  std::cout << GRN "[ -------- ] " NC << "stack" << std::endl;
  Benchmark("constructor",
            stk_constructor<std::stack<int> >,
            stk_constructor<ft::stack<int> >);
  Benchmark(
      "copyConstructor", stk_copy_constructor_std, stk_copy_constructor_ft);
  Benchmark("assignation", stk_assignation_std, stk_assignation_ft);
  Benchmark("top", stk_top_std, stk_top_ft);
  Benchmark("empty", stk_empty_std, stk_empty_ft);
  Benchmark("size", stk_size_std, stk_size_ft);
  Benchmark("push", stk_push<std::stack<int> >, stk_push<ft::stack<int> >);
  Benchmark("pop", stk_pop_std, stk_pop_ft);
  std::cout << std::endl;
}
