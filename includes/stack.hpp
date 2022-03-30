#ifndef FT_CONTAINERS_INCLUDES_STACK_HPP
#define FT_CONTAINERS_INCLUDES_STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Container = vector<T> >
class stack {
public:
  typedef Container                           container_type;
  typedef typename Container::value_type      value_type;
  typedef typename Container::size_type       size_type;
  typedef typename Container::reference       reference;
  typedef typename Container::const_reference const_reference;

protected:
  Container c_;

public:
  // == constructor ==
  explicit stack(const Container& cont = Container()) : c_(cont) {}
  stack(const stack& other) : c_(other.c_) {}

  // == destructor ==
  ~stack() {}

  // == assignation overload ==
  stack& operator=(const stack& other) {
    c_ = other.c_;
    return *this;
  }

  // == element access ==
  reference       top() { return c_.back(); }
  const_reference top() const { return c_.back(); }

  // == capacity ==
  bool      empty() const { return c_.empty(); }
  size_type size() const { return c_.size(); }

  // == modifires ==
  void push(const value_type& value) { return c_.push_back(value); }
  void pop() { return c_.pop_back(); }

  // == comparison ==
  template <typename Tp, typename Cont>
  friend bool operator==(const stack<Tp, Cont>& lhs,
                         const stack<Tp, Cont>& rhs);
  template <typename Tp, typename Cont>
  friend bool operator!=(const stack<Tp, Cont>& lhs,
                         const stack<Tp, Cont>& rhs);
  template <typename Tp, typename Cont>
  friend bool operator<(const stack<Tp, Cont>& lhs, const stack<Tp, Cont>& rhs);
  template <typename Tp, typename Cont>
  friend bool operator<=(const stack<Tp, Cont>& lhs,
                         const stack<Tp, Cont>& rhs);
  template <typename Tp, typename Cont>
  friend bool operator>(const stack<Tp, Cont>& lhs, const stack<Tp, Cont>& rhs);
  template <typename Tp, typename Cont>
  friend bool operator>=(const stack<Tp, Cont>& lhs,
                         const stack<Tp, Cont>& rhs);
};

// == non-member function ==
template <class T, class Container>
bool operator==(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return lhs.c_ == rhs.c_;
}
template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
  return lhs.c_ < rhs.c_;
}

template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(rhs < lhs);
}

template <class T, class Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
  return rhs < lhs;
}
template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_STACK_HPP */
