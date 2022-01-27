#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP

#include <limits>
#include <memory>
#include <stdexcept>

#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include "vector_iterator.hpp"

namespace ft {

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
  pointer        begin_;
  pointer        end_;
  pointer        cap_;
  allocator_type alloc_;

  void           vallocate(size_type n);
  void           vdeallocate();
  size_type      recommend(size_type new_size) const;

public:
  // == constructor ==
  vector() : begin_(NULL), end_(NULL), cap_(NULL), alloc_(Alloc()) {}
  explicit vector(const Alloc& alloc)
      : begin_(NULL), end_(NULL), cap_(NULL), alloc_(alloc) {}
  explicit vector(size_type n, const T& value = T(),
                  const Alloc& alloc = Alloc());
  template <class InputIt>
  vector(InputIt                                                         first,
         typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
         const Alloc& alloc = Alloc());
  vector(const vector& other);

  // == destructor ==
  ~vector();

  // == assignation overload ==
  vector& operator=(const vector& x);

  // == assign ==
  void    assign(size_type n, const value_type& u);
  template <class InputIt>
  void assign(
      InputIt                                                         first,
      typename enable_if<!is_integral<InputIt>::value, InputIt>::type last);

  allocator_type    get_allocator() const { return alloc_; }

  // == element access ==
  reference         operator[](size_type pos) { return begin_[pos]; };
  const_reference   operator[](size_type pos) const { return begin_[pos]; };
  reference         at(size_type pos);
  const_reference   at(size_type pos) const;
  reference         front() { return *begin_; };
  const_reference   front() const { return *begin_; };
  reference         back() { return *(end_ - 1); };
  const_reference   back() const { return *(end_ - 1); };
  value_type*       data() { return begin_; };
  const value_type* data() const { return begin_; };

  // == iterator ==
  iterator          begin() { return vector_iterator<T>(begin_); };
  const_iterator    begin() const { return vector_iterator<T const>(begin_); };
  iterator          end() { return vector_iterator<T>(end_); };
  const_iterator    end() const { return vector_iterator<T const>(end_); };
  reverse_iterator  rbegin() { return ft::reverse_iterator<iterator>(end()); };
  const_reverse_iterator rbegin() const {
    return ft::reverse_iterator<const_iterator>(end());
  };
  reverse_iterator rend() { return ft::reverse_iterator<iterator>(begin()); };
  const_reverse_iterator rend() const {
    return ft::reverse_iterator<const_iterator>(begin());
  };

  // == capacity ==
  bool      empty() const { return begin_ == end_; };
  size_type size() const { return static_cast<size_type>(end_ - begin_); };
  size_type capacity() const { return static_cast<size_type>(cap_ - begin_); };
  size_type max_size() const {
    return std::min<size_type>(alloc_.max_size(),
                               std::numeric_limits<difference_type>::max());
  };
  void     reserve(size_type new_cap);

  // == modifiers ==
  void     clear();

  iterator insert(iterator pos, const T& value);
  void     insert(iterator pos, size_type count, const T& value);
  template <class InputIt>
  void insert(
      iterator                                                        pos,
      typename enable_if<!is_integral<InputIt>::value, InputIt>::type first,
      InputIt                                                         last);

  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);

  void     push_back(const T& value);
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

// == helper private func ==
template <class T, class Alloc>
void vector<T, Alloc>::vdeallocate() {
  if (begin_ != NULL) {
    clear();
    alloc_.deallocate(begin_, capacity());
    begin_ = end_ = cap_ = NULL;
  }
}

template <class T, class Alloc>
void vector<T, Alloc>::vallocate(size_type n) {
  if (n > max_size())
    throw std::length_error("cannot create ft::vector larger than max_size()");
  begin_ = end_ = alloc_.allocate(n);
  cap_          = begin_ + n;
}

template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::recommend(
    size_type new_size) const {
  const size_type _max_size = max_size();
  if (new_size > _max_size)
    throw std::length_error("vector");
  const size_type _capacity = capacity();
  if (_capacity >= _max_size / 2)
    return _max_size;
  return std::max<size_type>(2 * _capacity, new_size);
}

// == constructor ==
template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const T& value, const Alloc& alloc)
    : alloc_(alloc) {
  vallocate(n);
  try {
    std::uninitialized_fill_n(begin_, n, value);
    cap_ = end_ = begin_ + n;
  } catch (...) {
    alloc_.deallocate(begin_, n);
    throw;
  }
}

template <class T, class Alloc>
template <class InputIt>
vector<T, Alloc>::vector(
    InputIt                                                         first,
    typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
    const Alloc&                                                    alloc)
    : alloc_(alloc) {
  end_ = begin_ = alloc_.allocate(last - first);
  for (; first != last; ++first) {
    *end_ = *first;
    ++end_;
  }
  cap_ = end_;
}

template <class T, class Alloc>
vector<T, Alloc>::vector(const vector& other) {
  begin_ = alloc_.allocate(other.capacity());
  std::uninitialized_copy(other.begin(), other.end(), begin_);
  end_ = begin_ + other.size();
  cap_ = begin_ + other.capacity();
}

// == destructor ==
template <class T, class Alloc>
vector<T, Alloc>::~vector() {
  vdeallocate();
}

// == assignation overload ==
template <class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& x) {
  if (x.capacity() > capacity()) {
    pointer new_data = alloc_.allocate(x.capacity());
    std::uninitialized_copy(x.begin(), x.end(), new_data);
    vdeallocate();
    begin_ = new_data;
    cap_   = begin_ + x.capacity();
  } else {
    std::copy(x.begin(), x.end(), begin());
  }
  end_ = begin_ + x.size();
  return *this;
}

// == assign ==
template <class T, class Alloc>
void vector<T, Alloc>::assign(size_type n, const value_type& u) {
  if (n > capacity()) {
    if (n > max_size()) {
      throw std::length_error(
          "cannot create ft::vector larger than max_size()");
    }
    pointer new_data = alloc_.allocate(n);
    std::uninitialized_fill_n(new_data, n, u);
    vdeallocate();
    begin_ = new_data;
    cap_ = end_ = begin_ + n;
  } else {
    std::fill(begin(), begin() + n, u);
    end_ = begin_ + n;
  }
}

template <class T, class Alloc>
template <class InputIt>
void vector<T, Alloc>::assign(
    InputIt                                                         first,
    typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
  difference_type len = std::distance(first, last);
  if (len > capacity()) {
    pointer new_data = alloc_.allocate(len);
    std::uninitialized_copy(first, last, new_data);
    vdeallocate();
    begin_ = new_data;
    end_ = cap_ = begin_ + len;
  } else {
    std::copy(first, last, begin());
    end_ = begin_ + len;
  }
}

// == element access ==
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos) {
  if (pos >= size())
    throw std::out_of_range("input index is out of range.");
  return begin_[pos];
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type pos) const {
  if (pos >= size())
    throw std::out_of_range("input index is out of range.");
  return begin_[pos];
}

// == capacity ==
template <class T, class Alloc>
void vector<T, Alloc>::reserve(size_type new_cap) {
  if (capacity() >= new_cap)
    return;
  if (new_cap > max_size()) {
    throw std::length_error("vector::reserve");
  }
  pointer   new_data = alloc_.allocate(new_cap);
  size_type sz       = size();
  std::uninitialized_copy(begin(), end(), new_data);
  vdeallocate();
  begin_ = new_data;
  end_   = begin_ + sz;
  cap_   = begin_ + new_cap;
}

// == modifiers ==
template <class T, class Alloc>
void vector<T, Alloc>::clear() {
  pointer ptr = end_;
  while (begin_ != ptr) {
    alloc_.destroy(--ptr);
  }
  end_ = begin_;
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator pos,
                                                             const T& value) {
  difference_type len = pos - begin();
  if (end_ == cap_) {
    reserve(recommend(size() + 1));
    pos = begin() + len;
  }
  if (pos == end()) {
    push_back(value);
  } else {
    alloc_.construct(end_, T());
    std::copy_backward(pos, end(), end() + 1);
    *pos = value;
    ++end_;
  }
  return begin() + len;
}

template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator pos, size_type count, const T& value) {
  difference_type len = pos - begin();
  if (size() + count > capacity()) {
    reserve(recommend(size() + count));
    pos = begin() + len;
  }
  if (pos == end()) {
    std::uninitialized_fill_n(end(), count, value);
  } else {
    for (pointer p = end_; p < end_ + count; p++) {
      alloc_.construct(p, T());
    }
    std::copy_backward(pos, end(), end() + count);
    std::fill(pos, pos + count, value);
  }
  end_ += count;
}

template <class T, class Alloc>
template <class InputIt>
void vector<T, Alloc>::insert(
    iterator                                                        pos,
    typename enable_if<!is_integral<InputIt>::value, InputIt>::type first,
    InputIt                                                         last) {
  difference_type len    = pos - begin();
  difference_type offset = std::distance(first, last);
  if (size() + offset > capacity()) {
    reserve(recommend(size() + offset));
    pos = begin() + len;
  }
  if (pos == end()) {
    std::uninitialized_copy(first, last, end());
  } else {
    for (pointer p = end_; p < end_ + offset; p++) {
      alloc_.construct(p, T());
    }
    std::copy_backward(pos, end(), end() + offset);
    std::copy(first, last, pos);
  }
  end_ += offset;
}
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator pos) {
  std::copy(pos + 1, end(), pos);
  alloc_.destroy(end_);
  --end_;
  return pos;
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first,
                                                            iterator last) {
  if (first == last)
    return last;
  std::copy(last, end(), first);
  pointer new_end = end_ - std::distance(first, last);
  for (pointer p = new_end; p <= end_; p++) {
    alloc_.destroy(p);
  }
  end_ = new_end;
  return first;
}

template <class T, class Alloc>
void vector<T, Alloc>::push_back(const T& value) {
  if (end_ == cap_) {
    reserve(recommend(size() + 1));
  }
  alloc_.construct(end_, value);
  ++end_;
}

// void              pop_back();
// void              resize(size_type count, T value = T());
// void              swap(vector& other);

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_HPP */
