#ifndef FT_CONTAINERS_INCLUDES_STACK_HPP
#define FT_CONTAINERS_INCLUDES_STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {
public:
  typedef Container                  container_type;
  typedef Container::value_type      value_type;
  typedef Container::size_type       size_type;
  typedef Container::reference       reference;
  typedef Container::const_reference const_reference;

private:  // public?
  Container c;

public:
  // == constructor ==
  explicit stack(const Container& cont = Container());
  stack(const stack& other);

  // == destructor ==
  ~stack();

  // == assignation overload ==
  stack&          operator=(const stack& other);

  // == element access ==
  reference       top() { return c.back(); }
  const_reference top() const { return c.back(); }

  // == capacity ==
  bool            empty() const { return c.empty(); }
  size_type       size() const { return c.size(); }

  // == modifires ==
  void            push(const value_type& value) { return c.push_back(value); }
  void            pop() { return c.pop_back(); }
};

// == non-member function ==
template <class T, class Container>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
template <class T, class Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_STACK_HPP */
