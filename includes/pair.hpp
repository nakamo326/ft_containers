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

public:
  // == constructor ==
  pair();
  pair(const T1& x, const T2& y);
  template <class U1, class U2>
  pair(const pair<U1, U2>& p);

  // == assignation overload ==
  pair& operator=(const pair& other);
};
// == non-member function ==
template <class T1, class T2>
pair<T1, T2> make_pair(T1 t, T2 u);

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_PAIR_HPP */
