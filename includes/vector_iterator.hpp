#ifndef FT_CONTAINERS_INCLUDES_VECTOR_ITERATOR_HPP
#define FT_CONTAINERS_INCLUDES_VECTOR_ITERATOR_HPP

#include <iterator>

namespace ft {

template <class T>
struct _vector_iterator {
public:
  typedef std::random_access_iterator_tag iterator_category;
  typedef T                               value_type;
  typedef T*                              pointer;
  typedef T&                              reference;
  typedef std::ptrdiff_t                  difference_type;

private:
  pointer _ptr;

public:
  _vector_iterator() : _ptr(NULL) {}
  _vector_iterator(T* p) : _ptr(p) {}
  _vector_iterator(_vector_iterator const& other) : _ptr(other._ptr) {}

  reference         operator*() const { return *_ptr; }
  pointer           operator->() const { return _ptr; }

  _vector_iterator& operator++() {
    ++_ptr;
    return *this;
  }
  _vector_iterator operator++(int) {
    _vector_iterator tmp(*this);
    ++(*this);
    return tmp;
  }

  _vector_iterator& operator--() {
    --_ptr;
    return *this;
  }
  _vector_iterator operator--(int) {
    _vector_iterator tmp(*this);
    --(*this);
    return tmp;
  }

  _vector_iterator operator+(difference_type n) const {
    _vector_iterator tmp(*this);
    tmp += n;
    return tmp;
  }

  _vector_iterator& operator+=(difference_type n) {
    _ptr += n;
    return *this;
  }

  _vector_iterator  operator-(difference_type n) const { return *this + (-n); }
  _vector_iterator& operator-=(difference_type n) {
    *this += -n;
    return *this;
  }

  reference operator[](difference_type n) const { return _ptr[n]; }

  pointer   base() const { return _ptr; }

  bool operator==(const _vector_iterator& rhs) { return base() == rhs.base(); }
  bool operator!=(const _vector_iterator& rhs) { return base() != rhs.base(); }
};

template <class _Iter1, class _Iter2>
typename _vector_iterator<_Iter1>::difference_type operator-(
    const _vector_iterator<_Iter1>& _x, const _vector_iterator<_Iter2>& _y) {
  return _x.base() - _y.base();
}

//  comparison  maybe should use friend?
// template <class _Iter1, class _Iter2>
// bool operator==(const __wrap_iter<_Iter1>& __x,
//                 const __wrap_iter<_Iter2>& __y) {
//   return __x.base() == __y.base();
// }

// template <class _Iter1>
// bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>&
// __y) {
//   return __x.base() < __y.base();
// }

// template <class _Iter1, class _Iter2>
// bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>&
// __y) {
//   return __x.base() < __y.base();
// }

// template <class _Iter1>
// bool operator!=(const __wrap_iter<_Iter1>& __x,
//                 const __wrap_iter<_Iter1>& __y) {
//   return !(__x == __y);
// }

// template <class _Iter1, class _Iter2>
// bool operator!=(const __wrap_iter<_Iter1>& __x,
//                 const __wrap_iter<_Iter2>& __y) {
//   return !(__x == __y);
// }

// template <class _Iter1>
// bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>&
// __y) {
//   return __y < __x;
// }

// template <class _Iter1, class _Iter2>
// bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>&
// __y) {
//   return __y < __x;
// }

// template <class _Iter1>
// bool operator>=(const __wrap_iter<_Iter1>& __x,
//                 const __wrap_iter<_Iter1>& __y) {
//   return !(__x < __y);
// }

// template <class _Iter1, class _Iter2>
// bool operator>=(const __wrap_iter<_Iter1>& __x,
//                 const __wrap_iter<_Iter2>& __y) {
//   return !(__x < __y);
// }

// template <class _Iter1>
// bool operator<=(const __wrap_iter<_Iter1>& __x,
//                 const __wrap_iter<_Iter1>& __y) {
//   return !(__y < __x);
// }

// template <class _Iter1, class _Iter2>
// bool operator<=(const __wrap_iter<_Iter1>& __x,
//                 const __wrap_iter<_Iter2>& __y) {
//   return !(__y < __x);
// }

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_ITERATOR_HPP */
