#ifndef FT_CONTAINERS_INCLUDES_HODE_HPP
#define FT_CONTAINERS_INCLUDES_HODE_HPP

#include <vector>

typedef void (*test_func_type)();
typedef std::vector<test_func_type> test_func_vec_type;
extern test_func_vec_type           test_functions;

namespace ft {
namespace test {

bool MakeAndRegisterTestInfo(test_func_type func);

}  // namespace test
}  // namespace ft

#define GEN_TEST_CLASS_NAME(test_suite_name, test_name) \
  test_suite_name##_##test_name##_##TEST

#define GEN_TEST_FUNCTION_NAME(test_suite_name, test_name) \
  test_suite_name##_##test_name##_##test_func

#define TEST(test_suite_name, test_name)                                                                    \
  /* このクラスは使わない。値をセット時に関数が呼べる仕様を使いたいだけ */ \
  class GEN_TEST_CLASS_NAME(test_suite_name, test_name) {                                                   \
  private:                                                                                                  \
    static const bool tmp_;                                                                                 \
  };                                                                                                        \
  void       GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)();                                          \
  const bool GEN_TEST_CLASS_NAME(test_suite_name, test_name)::tmp_ =                                        \
      ft::test::MakeAndRegisterTestInfo(                                                                    \
          GEN_TEST_FUNCTION_NAME(test_suite_name, test_name));                                              \
  void GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)()

#endif /* FT_CONTAINERS_INCLUDES_HODE_HPP */
