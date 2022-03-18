#ifndef FT_CONTAINERS_INCLUDES_FT_CONTAINER_HPP
#define FT_CONTAINERS_INCLUDES_FT_CONTAINER_HPP

#include <iostream>

class Benchmark {
protected:
  std::string test_name_;
  void (*std_func_)(void);
  void (*ft_func_)(void);

private:
  Benchmark();
  Benchmark(const Benchmark& x);

public:
  Benchmark(const char* test_name, void (*std_func)(void),
            void (*ft_func)(void));

  ~Benchmark();

  double run_bench(void (*func_)(void));
};

#endif /* FT_CONTAINERS_INCLUDES_FT_CONTAINER_HPP */
