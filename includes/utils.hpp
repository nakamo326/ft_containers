#ifndef FT_CONTAINERS_INCLUDES_UTILS_HPP
#define FT_CONTAINERS_INCLUDES_UTILS_HPP

namespace ft {

template <class Iterator>
struct iterator_traits {
  using difference_type   = typename Iterator::difference_type;
  using value_type        = typename Iterator::value_type;
  using pointer           = typename Iterator::pointer;
  using reference         = typename Iterator::reference;
  using iterator_category = typename Iterator::iterator_category;
};
// ポインタ型の特殊化必要？

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_UTILS_HPP */
