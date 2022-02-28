#ifndef FT_CONTAINERS_INCLUDES_FUNCTION_HPP
#define FT_CONTAINERS_INCLUDES_FUNCTION_HPP

namespace ft {

template <typename _Arg, typename _Result>
struct unary_function {
  typedef _Arg    argument_type;
  typedef _Result result_type;
};

template <typename _Tp>
struct _Identity : public unary_function<_Tp, _Tp> {
  _Tp&       operator()(_Tp& __x) const { return __x; }
  const _Tp& operator()(const _Tp& __x) const { return __x; }
};

template <typename _Tp>
struct _Identity<const _Tp> : _Identity<_Tp> {};

template <typename Pair>
struct _Select1st : public unary_function<Pair, typename Pair::first_type> {
  typename Pair::first_type& operator()(Pair& __x) const { return __x.first; }
  const typename Pair::first_type& operator()(const Pair& __x) const {
    return __x.first;
  }
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_FUNCTION_HPP */
