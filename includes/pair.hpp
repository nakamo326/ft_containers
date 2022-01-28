#ifndef FT_CONTAINERS_INCLUDES_PAIR_HPP
#define FT_CONTAINERS_INCLUDES_PAIR_HPP

namespace ft {
template <typename T1, typename T2>
class pair {
public:
  typedef T1 first_type;
  typedef T2 second_type;

private:
  T1 first;
  T2 second;
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_PAIR_HPP */
