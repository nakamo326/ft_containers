#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP

#include <limits>
#include <memory>
#include <stdexcept>

#include "reverse_iterator.hpp"
#include "type_trait.hpp"
#include "vector_iterator.hpp"

namespace ft {

// 後でinlineにすること！
template <class T, class Alloc = std::allocator<T> >
struct vector {
public:
  typedef T                                    value_type;
  typedef Alloc                                allocator_type;
  typedef typename Alloc::reference            reference;
  typedef typename Alloc::const_reference      const_reference;
  typedef typename Alloc::size_type            size_type;
  typedef typename Alloc::difference_type      difference_type;
  typedef typename Alloc::pointer              pointer;
  typedef typename Alloc::const_pointer        const_pointer;
  typedef vector_iterator<T>                   iterator;
  typedef vector_iterator<T const>             const_iterator;
  typedef ft::reverse_iterator<iterator>       reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
  pointer        _begin;
  pointer        _end;
  pointer        _cap;
  allocator_type _alloc;

public:
  // == constructor ==
  vector() : _begin(NULL), _end(NULL), _cap(NULL), _alloc(Alloc()) {}
  explicit vector(const Alloc& alloc)
      : _begin(NULL), _end(NULL), _cap(NULL), _alloc(alloc) {}
  vector(size_type n, const T& value = T(), const Alloc& alloc = Alloc());
  template <class InputIt>
  vector(InputIt first, InputIt last, const Alloc& alloc = Alloc());
  vector(const vector& other);

  // == destructor ==
  ~vector();

  // == assignation overload ==
  // vector&           operator=(const vector& x);

  // == assign ==
  // void    assign(size_type n, const value_type& u);
  // template <class InputIterator>
  // void              assign(InputIterator first, InputIterator last);

  allocator_type    get_allocator() const { return _alloc; }

  // == element access ==
  reference         operator[](size_type pos) { return _begin[pos]; };
  const_reference   operator[](size_type pos) const { return _begin[pos]; };
  reference         at(size_type pos);
  const_reference   at(size_type pos) const;
  reference         front() { return *_begin; };
  const_reference   front() const { return *_begin; };
  reference         back() { return *(_end - 1); };
  const_reference   back() const { return *(_end - 1); };
  value_type*       data() { return _begin; };
  const value_type* data() const { return _begin; };

  // == iterator ==
  iterator          begin() { return vector_iterator<T>(_begin); };
  const_iterator    begin() const { return vector_iterator<T const>(_begin); };
  iterator          end() { return vector_iterator<T>(_end); };
  const_iterator    end() const { return vector_iterator<T const>(_end); };
  reverse_iterator  rbegin() { return ft::reverse_iterator<iterator>(end()); };
  const_reverse_iterator rbegin() const {
    return ft::reverse_iterator<const_iterator>(end());
  };
  reverse_iterator rend() { return ft::reverse_iterator<iterator>(begin()); };
  const_reverse_iterator rend() const {
    return ft::reverse_iterator<const_iterator>(begin());
  };

  // == capacity ==
  bool      empty() const { return _begin == _end; };
  size_type size() const { return static_cast<size_type>(_end - _begin); };
  size_type capacity() const { return static_cast<size_type>(_cap - _begin); };
  size_type max_size() const {
    return std::min<size_type>(_alloc.max_size(),
                               std::numeric_limits<difference_type>::max());
  };
  void reserve(size_type new_cap);

  // == modifiers ==
  void clear() { _end = _begin; };

  // iterator          insert(iterator pos, const T& value);
  // void              insert(iterator pos, size_type count, const T& value);
  // template <class InputIt>
  // void insert(iterator pos, InputIt first, InputIt last);

  // iterator          erase(iterator pos);
  // iterator          erase(iterator first, iterator last);

  void push_back(const T& value);
  // void              pop_back();
  // void              resize(size_type count, T value = T());
  // void              swap(vector& other);
};

// == non-member functions ==
// template <class T, class Alloc>
// bool operator==(const std::vector<T, Alloc>& lhs,
//                 const std::vector<T, Alloc>& rhs);
// template <class T, class Alloc>
// bool operator!=(const std::vector<T, Alloc>& lhs,
//                 const std::vector<T, Alloc>& rhs);
// template <class T, class Alloc>
// bool operator<(const std::vector<T, Alloc>& lhs,
//                const std::vector<T, Alloc>& rhs);
// template <class T, class Alloc>
// bool operator<=(const std::vector<T, Alloc>& lhs,
//                 const std::vector<T, Alloc>& rhs);
// template <class T, class Alloc>
// bool operator>(const std::vector<T, Alloc>& lhs,
//                const std::vector<T, Alloc>& rhs);
// template <class T, class Alloc>
// bool operator>=(const std::vector<T, Alloc>& lhs,
//                 const std::vector<T, Alloc>& rhs);

// template <class T, class Alloc>
// void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs);

// == constructor ==
template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const T& value, const Alloc& alloc)
    : _alloc(alloc) {
  _begin = _end = _cap = _alloc.allocate(n);
  try {
    std::uninitialized_fill_n(_begin, n, value);
    _end = _begin + n;
    _cap = _end;
  } catch (...) {
    _alloc.deallocate(_begin, n);
    throw;
  }
}

template <class T, class Alloc>
template <class InputIt>
vector<T, Alloc>::vector(InputIt first, InputIt last, const Alloc& alloc)
    : _alloc(alloc) {
  _end = _begin = _alloc.allocate(last - first);
  for (; first != last; ++first) {
    *_end = *first;
    ++_end;
  }
  _cap = _end;
}

template <class T, class Alloc>
vector<T, Alloc>::vector(const vector& other) {
  _begin = _alloc.allocate(other.capacity());
  std::uninitialized_copy(other.begin(), other.end(), _begin);
  _end = other._end;
  _cap = other._cap;
}

// == destructor ==
template <class T, class Alloc>
vector<T, Alloc>::~vector() {
  if (_begin != NULL)
    _alloc.deallocate(_begin, capacity());
}

// == element access ==
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos) {
  if (pos >= size())
    throw std::out_of_range("input index is out of range.");
  return _begin[pos];
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type pos) const {
  if (pos >= size())
    throw std::out_of_range("input index is out of range.");
  return _begin[pos];
}

// == capacity ==
template <class T, class Alloc>
void vector<T, Alloc>::reserve(size_type new_cap) {
  if (new_cap > capacity()) {
    if (new_cap > max_size()) {
      throw std::length_error("vector::reserve");
    }
    pointer new_data = _alloc.allocate(new_cap);
    std::uninitialized_copy(begin(), end(), new_data);
    typename vector<T, Alloc>::size_type sz = size();
    _alloc.deallocate(_begin, sz);
    _begin = new_data;
    _end   = _begin + sz;
    _cap   = _begin + new_cap;
  }
}

// == modifiers ==
template <class T, class Alloc>
void vector<T, Alloc>::push_back(const T& value) {
  if (_end != _cap) {
    this->_alloc.construct(_end, value);
    ++_end;
  } else {
    reserve(size() * 2);
    this->_alloc.construct(_end, value);
    ++_end;
  }
}

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_HPP */
