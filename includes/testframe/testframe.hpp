#ifndef FT_CONTAINERS_INCLUDES_TESTFRAME_TESTFRAME_HPP
#define FT_CONTAINERS_INCLUDES_TESTFRAME_TESTFRAME_HPP

#include <cassert>
#include <string>
#include <vector>

/********** TESTの登録に必要な型とグローバル変数の定義 **********/

typedef void (*test_func_type)();
typedef std::pair<std::string, test_func_type> test_func_pair_type;
typedef std::vector<test_func_pair_type>       test_func_vec_type;

extern test_func_vec_type test_functions;

namespace ft {
namespace test {

// TEST()
bool MakeAndRegisterTestInfo(std::string test_name, test_func_type func);

}  // namespace test
}  // namespace ft

/********** TEST登録マクロ **********/

#define STR_HELPER(x) #x
#define STR(x)        STR_HELPER(x)

#define GEN_TEST_CLASS_NAME(test_suite_name, test_name) \
  test_suite_name##_##test_name##_##TEST

#define GEN_TEST_CLASS_OBJ_NAME(test_suite_name, test_name) \
  test_suite_name##_##test_name##_##TEST_OBJ

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
          STR(GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)),                                          \
          GEN_TEST_FUNCTION_NAME(test_suite_name, test_name));                                              \
  void GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)()

/********** EXPECT **********/

#define EXPECT_EQ(arg1, arg2) \
  { assert((arg1) == (arg2)); }

#define EXPECT_NE(arg1, arg2) \
  { assert((arg1) != (arg2)); }

#define EXPECT_TRUE(arg) \
  { assert((arg)); }

#define EXPECT_FALSE(arg) \
  { assert(!(arg)); }

#define EXPECT_THROW(expr, exception_type) \
  {                                        \
    bool has_caught_error = false;         \
    try {                                  \
      expr;                                \
    } catch (const exception_type &e) {    \
      has_caught_error = true;             \
    }                                      \
    assert(has_caught_error);              \
  }

/********** ASSERT **********/
// 動作はEXPECTと同じ。
// GoogleTestを使ってるコードを変更せずに使えるようにマクロを定義してる。

#define ASSERT_EQ(arg1, arg2) \
  { assert((arg1) == (arg2)); }

#define ASSERT_NE(arg1, arg2) \
  { assert((arg1) != (arg2)); }

#define ASSERT_TRUE(arg) \
  { assert((arg)); }

#define ASSERT_FALSE(arg) \
  { assert(!(arg)); }

#endif
