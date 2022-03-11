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
  iterator_type ptr_;

public:
  vector_iterator() : ptr_(NULL) {}
  vector_iterator(iterator_type p) : ptr_(p) {}
  vector_iterator(vector_iterator const& other) : ptr_(other.ptr_) {}
  template <typename _Iter>
  vector_iterator(const vector_iterator<_Iter>& __x) : ptr_(__x.base()) {}
  vector_iterator& operator=(const vector_iterator& __x) {
    ptr_ = __x.ptr_;
    return *this;
  }

  reference operator*() const { return *ptr_; }
  pointer   operator->() const { return ptr_; }

  vector_iterator& operator++() {
    ++ptr_;
    return *this;
  }
  vector_iterator operator++(int) {
    vector_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
  vector_iterator& operator--() {
    --ptr_;
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
    ptr_ += n;
    return *this;
  }

  vector_iterator  operator-(difference_type n) const { return *this + (-n); }
  vector_iterator& operator-=(difference_type n) {
    *this += -n;
    return *this;
  }

  reference operator[](difference_type n) const { return ptr_[n]; }

  pointer base() const { return ptr_; }
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

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_ITERATOR_HPP */
