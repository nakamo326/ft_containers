#ifndef FT_CONTAINERS_INCLUDES_TYPE_TRAITS_HPP
#define FT_CONTAINERS_INCLUDES_TYPE_TRAITS_HPP

namespace ft {

template <bool, typename _Tp = void>
struct enable_if {};

template <typename _Tp>
struct enable_if<true, _Tp> {
  typedef _Tp type;
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_TYPE_TRAITS_HPP */
