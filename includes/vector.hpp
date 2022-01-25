#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP

#include <limits>
#include <memory>
#include <stdexcept>

#include "reverse_iterator.hpp"
#include "type_traits.hpp"
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
  pointer        begin_;
  pointer        end_;
  pointer        cap_;
  allocator_type alloc_;

  void           deallocate();

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
  void reserve(size_type new_cap);

  // == modifiers ==
  void clear();

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

// == helper private func ==

// くだらないコメント

// FIXME: use clear
template <class T, class Alloc>
void vector<T, Alloc>::deallocate() {
  if (begin_ != NULL) {
    alloc_.deallocate(begin_, capacity());
  }
}

// == constructor ==
template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const T& value, const Alloc& alloc)
    : alloc_(alloc) {
  begin_ = alloc_.allocate(n);
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
// FIXME: use destroy
template <class T, class Alloc>
vector<T, Alloc>::~vector() {
  // need to fix?
  deallocate();
}

// == assignation overload ==

// FIXME: use construct?
template <class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& x) {
  if (x.capacity() > capacity()) {
    pointer new_data = alloc_.allocate(x.capacity());
    std::uninitialized_copy(x.begin(), x.end(), new_data);
    // deallocate()の前にclear?
    // destroy呼ばないとheapが確保されていた時リークしそう
    deallocate();
    begin_ = new_data;
    cap_   = begin_ + x.capacity();
  } else {
    // 初期化済み領域へのcopyには適さないかも
    std::uninitialized_copy(x.begin(), x.end(), begin_);
  }
  end_ = begin_ + x.size();
  return *this;
}

// == assign ==

// FIXME: use construct?
template <class T, class Alloc>
void vector<T, Alloc>::assign(size_type n, const value_type& u) {
  if (n > capacity()) {
    if (n > max_size()) {
      throw std::length_error(
          "cannot create ft::vector larger than max_size()");
    }
    pointer new_data = alloc_.allocate(n);
    std::uninitialized_fill_n(new_data, n, u);
    deallocate();
    begin_ = new_data;
    cap_ = end_ = new_data + n;
  } else {
    // 初期化済み領域へのcopyには適さないかも
    std::uninitialized_fill_n(begin_, n, u);
    end_ = begin_ + n;
  }
}

// template <class T, class Alloc>
// template <class InputIt>
// void vector<T, Alloc>::assign(
//     InputIt                                                         first,
//     typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
//   (void)first;
//   (void)last;
// }

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

// FIXME: use construct?
template <class T, class Alloc>
void vector<T, Alloc>::reserve(size_type new_cap) {
  if (new_cap > capacity()) {
    if (new_cap > max_size()) {
      throw std::length_error("vector::reserve");
    }
    pointer new_data = alloc_.allocate(new_cap);
    std::uninitialized_copy(begin(), end(), new_data);
    typename vector<T, Alloc>::size_type sz = size();
    deallocate();
    begin_ = new_data;
    end_   = begin_ + sz;
    cap_   = begin_ + new_cap;
  }
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
void vector<T, Alloc>::push_back(const T& value) {
  if (end_ == cap_) {
    reserve(size() * 2);
  }
  this->alloc_.construct(end_, value);
  ++end_;
}

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_HPP */
