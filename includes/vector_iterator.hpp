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
};

template <class T>
_vector_iterator<T> operator+(typename _vector_iterator<T>::difference_type n,
                              _vector_iterator<T>                           x) {
  x += n;
  return x;
}

//  comparison  maybe should use friend?
template <class T>
bool operator==(const _vector_iterator<T>& rhs,
                const _vector_iterator<T>& lhs) {
  return rhs._ptr == lhs._ptr;
}

template <class T, class U>
bool operator==(const _vector_iterator<T>& rhs,
                const _vector_iterator<U>& lhs) {
  return rhs._ptr == lhs._ptr;
}

template <class T>
bool operator!=(const _vector_iterator<T>& rhs,
                const _vector_iterator<T>& lhs) {
  return !(rhs == lhs);
}

template <class T>
bool operator<(const _vector_iterator<T>& rhs, const _vector_iterator<T>& lhs) {
  return rhs._ptr < lhs._ptr;
}

template <class T>
bool operator>(const _vector_iterator<T>& rhs, const _vector_iterator<T>& lhs) {
  return lhs < rhs;
}

template <class T>
bool operator>=(const _vector_iterator<T>& rhs,
                const _vector_iterator<T>& lhs) {
  return !(rhs < lhs);
}

template <class T>
bool operator<=(const _vector_iterator<T>& rhs,
                const _vector_iterator<T>& lhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_ITERATOR_HPP */
