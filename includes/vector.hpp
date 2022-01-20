#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP

namespace ft {
template <class T, class Allocator = std::allocator<T> >
struct vector {
public:
  typedef T                                     value_type;
  typedef Allocator                             allocator_type;
  typedef std::size_t                           size_type;
  typedef std::ptrdiff_t                        difference_type;
  typedef T*                                    pointer;
  typedef const pointer                         const_pointer;
  typedef value_type&                           reference;
  typedef const value_type&                     const_reference;
  // 実実装要確認
  typedef pointer                               iterator;
  typedef const_pointer                         const_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  vector(){};
  explicit vector(const allocator_type& alloc) : _alloc(alloc){};
  explicit vector(size_type count, const T& value = T(),
                  const Allocator& alloc = Allocator());
  vector(const vector& other){};
  // ~vector() {};
  // template <class InputIt>
  // vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
  // vector &         operator=(const vector &x) {};

  iterator         begin() { return _first; }
  iterator         end() { return _last; }
  const_iterator   cbegin() const { return _first; }
  const_iterator   cend() const { return _last; }
  reverse_iterator rbegin() { return static_cast<reverse_iterator>(_first); }
  reverse_iterator rend() { return static_cast<reverse_iterator>(_last); }
  size_type        size() { return _last - _first; }
  bool             empty() { return _first == _last; }
  size_type        capacity() { return _reserve_last - _first; }
  reference        operator[](size_type i) { return _first[i]; }
  const_reference  operator[](size_type i) const { return _first[i]; }
  reference        at(size_type i) {
    if (i >= size())
      throw std::out_of_range("index is out of range.");
    return _first[i];
  }
  const_reference at(size_type i) const {
    if (i >= size())
      throw std::out_of_range("index is out of range.");
    return _first[i];
  }
  reference       front() { return _first; }
  const_reference front() const { return _first; }
  reference       back() { return _last - 1; }
  const_reference back() const { return _last - 1; }

private:
  pointer        _first;
  pointer        _last;
  pointer        _reserve_last;
  allocator_type _alloc;
};
}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_HPP */
