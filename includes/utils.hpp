#ifndef FT_CONTAINERS_INCLUDES_UTILS_HPP
#define FT_CONTAINERS_INCLUDES_UTILS_HPP

namespace ft {

template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
  typedef typename Iterator::iterator_category iterator_category;
};
// ポインタ型の特殊化必要？

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_UTILS_HPP */
