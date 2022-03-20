
#include "benchmark/Benchmark.hpp"

#include <time.h>

#include <iomanip>

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

Benchmark::Benchmark() {}

Benchmark::Benchmark(const Benchmark &x) { (void)x; }

Benchmark::Benchmark(const char *test_name, void (*std_func)(void),
                     void (*ft_func)(void))
    : test_name_(test_name), std_func_(std_func), ft_func_(ft_func) {}

Benchmark::~Benchmark() {
  double std_time, ft_time, times;
  std::cout << GRN "[ RUN      ] " NC << test_name_ << std::endl;
  std_time = run_bench(std_func_);
  ft_time  = run_bench(ft_func_);
  times    = ft_time / std_time;
  std::cout << GRN "[       OK ] " NC << test_name_;
  std::cout << BLU " (" << std::setprecision(2) << times << "x)" NC
            << std::endl;
}

double Benchmark::run_bench(void (*func_)(void)) {
  struct timespec begin, end;
  double          res;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
  func_();
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
  res = timespec_diff(&begin, &end);

  if (func_ == std_func_) {
    std::cout << GRN "[    STD   ] " NC;
  } else {
    std::cout << GRN "[    FT    ] " NC;
  }
  std::cout << std::setprecision(6) << res << " ms" << std::endl;
  return res;
}
