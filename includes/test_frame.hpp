#ifndef FT_CONTAINERS_INCLUDES_TEST_FRAME_HPP
#define FT_CONTAINERS_INCLUDES_TEST_FRAME_HPP

#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>
#include <vector>

#include "Color.hpp"

// return as milliseconds
double timespec_diff(struct timespec *start, struct timespec *stop) {
  struct timespec result;
  if ((stop->tv_nsec - start->tv_nsec) < 0) {
    result.tv_sec  = stop->tv_sec - start->tv_sec - 1;
    result.tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
  } else {
    result.tv_sec  = stop->tv_sec - start->tv_sec;
    result.tv_nsec = stop->tv_nsec - start->tv_nsec;
  }
  return result.tv_sec * 1000 + (double)result.tv_nsec / 1000000;
}

class Test {
protected:
  std::string test_name_;
  void (*test_func_)(void);

public:
  Test() {}

  Test(const char *test_name, void (*func)(void)) {
    test_name_ = std::string(test_name);
    test_func_ = func;
  }

  double run_test() {
    struct timespec begin, end;
    std::cout << GRN "[ RUN      ]" NC << test_name_ << std::endl;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
    test_func_();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    double total = timespec_diff(&begin, &end);
    std::cout << GRN "[       OK ]" NC << test_name_ << " (" << total << " ms)"
              << std::endl;
    return total;
  }

  virtual ~Test() {}
};

class Suite {
  std::string       suite_name_;
  std::vector<Test> test_list_;

public:
  Suite() {}

  Suite(const char *suite_name) { suite_name_ = std::string(suite_name); }

  void add_test(const Test &test) { test_list_.push_back(test); }

  ~Suite() {
    double sum = 0;
    std::cout << GRN "[----------]" NC << test_list_.size() << " tests from "
              << suite_name_ << std::endl;
    std::vector<Test>::iterator it = test_list_.begin();
    for (; it != test_list_.end(); it++) {
      sum += (*it).run_test();
    }
    std::cout << GRN "[----------]" NC << test_list_.size() << " tests from "
              << suite_name_ << " (" << sum << " ms total)\n"
              << std::endl;
  }
};

#endif /* FT_CONTAINERS_INCLUDES_TEST_FRAME_HPP */
