void vector_bench_entry(void);
void stack_bench_entry(void);
void map_bench_entry(void);
void set_bench_entry(void);

int main(void) {
  vector_bench_entry();
  stack_bench_entry();
  map_bench_entry();
  set_bench_entry();
  return 0;
}
