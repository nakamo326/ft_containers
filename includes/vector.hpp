#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP

#include <limits>
#include <memory>
#include <stdexcept>

namespace ft {

template <class T, class Alloc = std::allocator<T> >
struct vector {
public:
  typedef T                               value_type;
  typedef Alloc                           allocator_type;
  typedef typename Alloc::reference       reference;
  typedef typename Alloc::const_reference const_reference;
  typedef typename Alloc::size_type       size_type;
  typedef typename Alloc::difference_type difference_type;
  typedef typename Alloc::pointer         pointer;
  typedef typename Alloc::const_pointer   const_pointer;
  // 要再実装 llvmではwrap_iter<>
  // typedef pointer                                  iterator;
  // typedef const_pointer                            const_iterator;
  // typedef std::reverse_iterator<iterator>          reverse_iterator;
  // typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

private:
  pointer        _begin;
  pointer        _end;
  pointer        _cap;
  allocator_type _alloc;

public:
  // == constructor ==
  vector() : _alloc(Alloc()), _begin(NULL), _end(NULL), _cap(NULL) {}
  explicit vector(const Alloc& alloc)
      : _alloc(alloc), _begin(NULL), _end(NULL), _cap(NULL) {}
  vector(size_type n, const T& value = T(), const Alloc& alloc = Alloc());
  // template <class InputIt>
  // vector(InputIt first, InputIt last, const Alloc& alloc = Alloc());
  // vector(const vector& other);

  // == destructor ==
  //~vector();

  // == assignation overload ==
  // vector&           operator=(const vector& x);

  // == assign ==
  // void    assign(size_type n, const value_type& u);
  // template <class InputIterator>
  // void              assign(InputIterator first, InputIterator last);

  allocator_type    get_allocator() const { return _alloc; }

  // == element access ==
  reference         operator[](size_type n) { return _begin[n]; };
  const_reference   operator[](size_type n) const { return _begin[n]; };
  // reference       at(size_type n);
  // const_reference at(size_type n) const;
  reference         front() { return *_begin; };
  const_reference   front() const { return *_begin; };
  reference         back() { return *(_end - 1); };
  const_reference   back() const { return *(_end - 1); };
  value_type*       data() { return _begin; };
  const value_type* data() const { return _begin; };

  // == iterator ==
  // iterator               begin() noexcept;
  // const_iterator         begin() const noexcept;
  // iterator               end() noexcept;
  // const_iterator         end() const noexcept;
  // reverse_iterator       rbegin() noexcept;
  // const_reverse_iterator rbegin() const noexcept;
  // reverse_iterator       rend() noexcept;
  // const_reverse_iterator rend() const noexcept;

  // == capacity ==
  bool              empty() const { return _begin == _end; };
  size_type         size() const { return _end - _begin; };
  size_type         max_size() const {
    return std::min<size_type>(_alloc.max_size(),
                               std::numeric_limits<difference_type>::max());
  };
  size_type capacity() const { return static_cast<size_type>(_cap - _begin); };
  // void      reserve(size_type new_cap);

  // == modifiers ==
  // void              clear() noexcept;

  // iterator          insert(iterator pos, const T& value);
  // void              insert(iterator pos, size_type count, const T& value);
  // template <class InputIt>
  // void insert(iterator pos, InputIt first, InputIt last);

  // iterator          erase(iterator pos);
  // iterator          erase(iterator first, iterator last);

  // void              push_back(const T& value);
  // void              pop_back();
  // void              resize(size_type count, T value = T());
  // void              swap(vector& other);
};

// non-member functions
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

template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const T& value, const Alloc& alloc)
    : _alloc(alloc) {
  _begin = _end = _cap = _alloc.allocate(n);
  try {
    std::uninitialized_fill_n(_begin, n, value);
    _cap = _end = _begin + n;
  } catch (...) {
    _alloc.deallocate(_begin, n);
    throw;
  }
}

// template <class T, class Alloc>
// void vector<T, Alloc>::reserve(size_type new_cap) {
//   if (new_cap > capacity()) {
//     if (new_cap > max_size())
//       throw std::range_error();
//     pointer new_data = _alloc.allocate(new_cap);
//     // try catch
//     std::uninitialized_copy(begin(), end(), new_data);
//     _alloc.deallocate(_begin, size());
//     _begin = new_data;
//   }
// }

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_HPP */
