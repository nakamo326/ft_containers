#ifndef FT_CONTAINERS_INCLUDES_TYPE_TRAITS_HPP
#define FT_CONTAINERS_INCLUDES_TYPE_TRAITS_HPP

namespace ft {

// == enable_if ==
template <bool, typename _Tp = void>
struct enable_if {};

template <typename _Tp>
struct enable_if<true, _Tp> {
  typedef _Tp type;
};

// == remove_const ==
template <typename _Tp>
struct remove_const {
  typedef _Tp type;
};

template <typename _Tp>
struct remove_const<_Tp const> {
  typedef _Tp type;
};

// == remove_volatile ==
template <typename _Tp>
struct remove_volatile {
  typedef _Tp type;
};

template <typename _Tp>
struct remove_volatile<_Tp volatile> {
  typedef _Tp type;
};

// == remove_cv ==
template <typename _Tp>
struct remove_cv {
  typedef typename remove_const<typename remove_volatile<_Tp>::type>::type type;
};

// == integral_constant ==
template <typename _Tp, _Tp __v>
struct integral_constant {
  const static _Tp                    value = __v;
  typedef _Tp                         value_type;
  typedef integral_constant<_Tp, __v> type;
  // clang-format off
  operator value_type() { return value; }
  // clang-format on
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <typename>
struct __is_integral_helper : public false_type {};

template <>
struct __is_integral_helper<bool> : public true_type {};

template <>
struct __is_integral_helper<char> : public true_type {};

template <>
struct __is_integral_helper<signed char> : public true_type {};

template <>
struct __is_integral_helper<unsigned char> : public true_type {};

template <>
struct __is_integral_helper<wchar_t> : public true_type {};

template <>
struct __is_integral_helper<short> : public true_type {};

template <>
struct __is_integral_helper<unsigned short> : public true_type {};

template <>
struct __is_integral_helper<int> : public true_type {};

template <>
struct __is_integral_helper<unsigned int> : public true_type {};

template <>
struct __is_integral_helper<long> : public true_type {};

template <>
struct __is_integral_helper<unsigned long> : public true_type {};

// == is_integral ==
template <typename _Tp>
struct is_integral
    : public __is_integral_helper<typename ft::remove_cv<_Tp>::type>::type {};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_TYPE_TRAITS_HPP */
