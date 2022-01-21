#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP

#include <memory>
#include <stdexcept>

namespace ft {

template <class T, class Allocator>
class __vector_base {
  typedef Allocator                        allocator_type;
  typedef typename allocator_type::pointer pointer;
  // pair再実装必要, そもそもpairの必要あるか確認
  // __end_cap() { return this->__end_cap_.first(); } -> _cap
  // __alloc() { return this->__end_cap_.second(); }  -> _alloc
protected:
  pointer        _begin;
  pointer        _end;
  pointer        _cap;
  allocator_type _alloc;

  __vector_base() : _begin(NULL), _end(NULL), _cap(NULL) {}

  __vector_base(const allocator_type& __a)
      : _begin(NULL), _end(NULL), _cap(NULL), _alloc(__a) {}
};

template <class T, class Alloc = std::allocator<T> >
struct vector : private __vector_base<T, Alloc> {
private:
  typedef __vector_base<T, Alloc> _base;

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

  // == constructor ==
  vector() {}
  explicit vector(const Alloc& alloc) : _base(alloc) {}
  explicit vector(size_type n);
  // vector(size_type n, const value_type& x);
  // template <class = __enable_if_t<__is_allocator<_Allocator>::value>>
  // vector(size_type n, const value_type& x, const allocator_type& a)
  //     : __base(a) {
  //   if (n > 0) {
  //     __vallocate(n);
  //     __construct_at_end(n, x);
  //   }
  // }
  // explicit vector(size_type count, const T& value = T(),
  //                 const Alloc& alloc = Alloc());
  // template <class InputIt>
  // vector(InputIt first, InputIt last, const Alloc& alloc = Alloc());
  // vector(const vector& other);

  // == destructor ==
  //~vector();

  // == assignation overload ==
  vector& operator=(const vector& x);

  // == assign ==
  void    assign(size_type n, const value_type& u);
  template <class InputIterator>
  void            assign(InputIterator first, InputIterator last);

  allocator_type  get_allocator() const { return this->_alloc; }

  // == element access ==
  reference       operator[](size_type n) { return this->_begin[n]; };
  const_reference operator[](size_type n) const { return this->_begin[n]; };
  // reference       at(size_type n);
  // const_reference at(size_type n) const;

  reference       front() { return *this->_begin; };
  const_reference front() const { return *this->_begin; };
  reference       back() { return *(this->_end - 1); };
  const_reference back() const { return *(this->_end - 1); };

  // value_type*       data();
  // const value_type* data() const;

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
  size_type       size() const;
  size_type       max_size() const;
  size_type       capacity() const;
  bool            empty() const;
  void            reserve(size_type n);

  // == modifiers ==

private:
  void __vallocate(size_type n);
  void __construct_at_end(size_type n);
};

// non-member functions

template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n) {
  if (n > 0) {
    __vallocate(n);
    __construct_at_end(n);
  }
}

template <class T, class Alloc>
void vector<T, Alloc>::__vallocate(size_type n) {
  // if (n > max_size())
  //   this->__throw_length_error();
  this->_begin = this->_alloc.allocate(n);
  this->_end   = this->_begin;
  this->_cap   = this->_begin + n;
}

template <class T, class Alloc>
void vector<T, Alloc>::__construct_at_end(size_type n) {
  pointer new_end = this->_end + n;
  for (pointer pos = this->_end; pos != new_end; pos = ++pos) {
    this->_alloc.construct(pos, 0);
  }
  this->_end = new_end;
}

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_VECTOR_HPP */
