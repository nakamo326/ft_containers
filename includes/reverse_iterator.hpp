#ifndef FT_CONTAINERS_INCLUDES_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_INCLUDES_REVERSE_ITERATOR_HPP

#include "utils.hpp"

namespace ft {

template <class Iter>
struct reverse_iterator {
public:
  typedef Iter iterator_type;
  typedef
      typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
  typedef typename ft::iterator_traits<Iter>::value_type      value_type;
  typedef typename ft::iterator_traits<Iter>::pointer         pointer;
  typedef typename ft::iterator_traits<Iter>::reference       reference;
  typedef typename ft::iterator_traits<Iter>::difference_type difference_type;

private:
  Iter _current;

public:
  reverse_iterator() : _current() {}
  explicit reverse_iterator(iterator_type x) : _current(x) {}
  template <typename _Iter>
  reverse_iterator(const reverse_iterator<_Iter>& __x) : _current(__x.base()) {}

  iterator_type base() const { return _current; }

  reference     operator*() const {
    Iter tmp = _current;
    return *--_current;
  }
  pointer operator->() const {
    Iter tmp = _current;
    --tmp;
    return tmp;
  }

  reverse_iterator& operator++() {
    --_current;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator tmp(*this);
    --_current;
    return tmp;
  }
  reverse_iterator& operator--() {
    ++_current;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator tmp(*this);
    ++_current;
    return tmp;
  }

  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(_current - n);
  }

  reverse_iterator& operator+=(difference_type n) {
    _current -= n;
    return *this;
  }

  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(_current + n);
  }
  reverse_iterator& operator-=(difference_type n) {
    _current += n;
    return *this;
  }

  reference operator[](difference_type n) const { return *(*this + n); }
};

// =========================================
template <class T>
reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type n,
                              reverse_iterator<T>                           x) {
  return reverse_iterator<T>(x.base() - n);
}

template <class T>
typename reverse_iterator<T>::difference_type operator-(
    const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) {
  return rhs.base() - lhs.base();
}

template <class T, class U>
bool operator==(const reverse_iterator<T>& lhs,
                const reverse_iterator<U>& rhs) {
  return lhs.base() == rhs.base();
}

template <class T, class U>
bool operator!=(const reverse_iterator<T>& lhs,
                const reverse_iterator<U>& rhs) {
  return !(lhs == rhs);
}

template <class T, class U>
bool operator<(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) {
  return lhs.base() > rhs.base();
}

template <class T, class U>
bool operator>(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) {
  return rhs < lhs;
}

template <class T, class U>
bool operator>=(const reverse_iterator<T>& lhs,
                const reverse_iterator<U>& rhs) {
  return !(lhs < rhs);
}

template <class T, class U>
bool operator<=(const reverse_iterator<T>& lhs,
                const reverse_iterator<U>& rhs) {
  return !(rhs < lhs);
}

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_REVERSE_ITERATOR_HPP */
