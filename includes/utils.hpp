#ifndef FT_CONTAINERS_INCLUDES_UTILS_HPP
#define FT_CONTAINERS_INCLUDES_UTILS_HPP

namespace ft {

template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
};

template <typename T>
struct iterator_traits<T*> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T                               value_type;
  typedef std::ptrdiff_t                  difference_type;
  typedef T*                              pointer;
  typedef T&                              reference;
};

template <typename T>
struct iterator_traits<const T*> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T                               value_type;
  typedef std::ptrdiff_t                  difference_type;
  typedef const T*                        pointer;
  typedef const T&                        reference;
};

template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}

// InputIt1が辞書的に小さいときはtrue
template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
    if (*first1 < *first2)
      return true;
    if (*first2 < *first1)
      return false;
  }
  return (first1 == last1) && (first2 != last2);
}

// 関数アダプタのための基底クラス
template <typename _Arg1, typename _Arg2, typename _Result>
struct binary_function {
  typedef _Arg1   first_argument_type;
  typedef _Arg2   second_argument_type;
  typedef _Result result_type;
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_UTILS_HPP */
