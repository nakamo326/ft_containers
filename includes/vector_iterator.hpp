#ifndef FT_CONTAINERS_INCLUDES_VECTOR_ITERATOR_HPP
#define FT_CONTAINERS_INCLUDES_VECTOR_ITERATOR_HPP

#include <iterator>

#include "type_traits.hpp"

namespace ft {

template <class T>
struct vector_iterator {
public:
  typedef T                                              iterator_type;
  typedef typename iterator_traits<T>::iterator_category iterator_category;
  typedef typename iterator_traits<T>::value_type        value_type;
  typedef typename iterator_traits<T>::pointer           pointer;
  typedef typename iterator_traits<T>::reference         reference;
  typedef typename iterator_traits<T>::difference_type   difference_type;

private:
  iterator_type _ptr;

public:
  vector_iterator() : _ptr(NULL) {}
  vector_iterator(iterator_type p) : _ptr(p) {}
  vector_iterator(vector_iterator const& other) : _ptr(other._ptr) {}
  template <typename _Iter>
  vector_iterator(const vector_iterator<_Iter>& __x) : _ptr(__x.base()) {}

  reference operator*() const { return *_ptr; }
  pointer   operator->() const { return _ptr; }

  vector_iterator& operator++() {
    ++_ptr;
    return *this;
  }
  vector_iterator operator++(int) {
    vector_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
  vector_iterator& operator--() {
    --_ptr;
    return *this;
  }
  vector_iterator operator--(int) {
    vector_iterator tmp(*this);
    --(*this);
    return tmp;
  }

  vector_iterator operator+(difference_type n) const {
    vector_iterator tmp(*this);
    tmp += n;
    return tmp;
  }

  vector_iterator& operator+=(difference_type n) {
    _ptr += n;
    return *this;
  }

  vector_iterator  operator-(difference_type n) const { return *this + (-n); }
  vector_iterator& operator-=(difference_type n) {
    *this += -n;
    return *this;
  }

  reference operator[](difference_type n) const { return _ptr[n]; }

  pointer base() const { return _ptr; }
};

template <class T>
vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n,
                             vector_iterator<T>                           x) {
  x += n;
  return x;
}

template <class T, class U>
typename vector_iterator<T>::difference_type operator-(
    const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
  return lhs.base() - rhs.base();
}

template <class T, class U>
bool operator==(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
  return lhs.base() == rhs.base();
}

template <class T, class U>
bool operator!=(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
  return !(lhs == rhs);
}

template <class T, class U>
bool operator<(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
  return lhs.base() < rhs.base();
}

template <class T, class U>
bool operator>(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
  return rhs < lhs;
}

template <class T, class U>
bool operator>=(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
  return !(lhs < rhs);
}

template <class T, class U>
bool operator<=(const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
  return !(rhs < lhs);
}

// hituyou?
// template <class T>
// bool operator==(const vector_iterator<T>& rhs,
//                 const vector_iterator<T>& lhs) {
//   return rhs.base() == lhs.base();
// }

// template <class T>
// bool operator!=(const vector_iterator<T>& rhs,
//                 const vector_iterator<T>& lhs) {
//   return !(rhs == lhs);
// }

// template <class T>
// bool operator<(const vector_iterator<T>& rhs, const vector_iterator<T>&
// lhs) {
//   return rhs.base() < lhs.base();
// }

// template <class T>
// bool operator>(const vector_iterator<T>& rhs, const vector_iterator<T>&
// lhs) {
//   return lhs < rhs;
// }

// template <class T>
// bool operator>=(const vector_iterator<T>& rhs,
//                 const vector_iterator<T>& lhs) {
//   return !(rhs < lhs);
// }

// template <class T>
// bool operator<=(const vector_iterator<T>& rhs,
//                 const vector_iterator<T>& lhs) {
//   return !(lhs < rhs);
// }

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_ITERATOR_HPP */
