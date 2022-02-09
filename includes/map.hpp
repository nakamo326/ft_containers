#ifndef FT_CONTAINERS_INCLUDES_MAP_HPP
#define FT_CONTAINERS_INCLUDES_MAP_HPP

#include <functional>

#include "RBtree.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<std::pair<const Key, T> > >
class map {
public:
  typedef Key                             key_type;
  typedef T                               mapped_type;
  typedef std::pair<const Key, T>         value_type;
  typedef std::size_t                     size_type;
  typedef std::ptrdiff_t                  difference_type;
  typedef Compare                         key_compare;
  typedef Alloc                           allocator_type;
  typedef typename Alloc::reference       reference;
  typedef typename Alloc::const_reference const_reference;
  typedef typename Alloc::pointer         pointer;
  typedef typename Alloc::const_pointer   const_pointer;

private:
  typedef RBtree<Key, T, Compare> tree_type;

public:
  typedef tree_type::iterator                  iterator;
  typedef tree_type::const_iterator            const_iterator;
  typedef ft::reverse_iterator<iterator>       reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // FIXME: change mapped_type to value_type(pair)
private:
  RBtree<Key, mapped_type, Compare> tree_;

public:
  class value_compare {
    friend class map<_Key, _Tp, _Compare, _Alloc>;

  public:
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    typedef bool       result_type;

  protected:
    Compare comp;
    value_compare(Compare _c) : comp(_c) {}

  public:
    bool operator()(const value_type& __x, const value_type& __y) const {
      return comp(__x.first, __y.first);
    }
  };

public:
  // == constructor / destructor ==
  map();
  explicit map(const Compare& comp, const Allocator& alloc = Allocator());
  template <class InputIt>
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator());
  map(const map& other);

  ~map();

  // == assignation ==
  map& operator=(const map& other);

  allocator_type get_allocator() const { return Alloc(); };

  // == element access ==
  T& operator[](const Key& key);

  // == iterators ==
  iterator               begin();
  const_iterator         begin() const;
  iterator               end();
  const_iterator         end() const;
  reverse_iterator       rbegin();
  const_reverse_iterator rbegin() const;
  reverse_iterator       rend();
  const_reverse_iterator rend() const;

  // == capacity ==
  bool      empty() const { return tree_.size() == 0; }
  size_type size() const { return tree_.size(); }
  size_type max_size() const { return tree_.max_size(); }

  // == modifiers ==
  pair<iterator, bool> insert(const value_type& val);
  iterator             insert(iterator position, const value_type& val);
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last);

  iterator  erase(const_iterator position);
  size_type erase(const key_type& k);
  iterator  erase(const_iterator first, const_iterator last);

  void swap(map& x);
  void clear();

  // == lookup ==
  size_type                                count(const Key& key) const;
  iterator                                 find(const Key& key);
  const_iterator                           find(const Key& key) const;
  ft::pair<iterator, iterator>             equal_range(const Key& key);
  ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
  iterator                                 lower_bound(const Key& key);
  const_iterator                           lower_bound(const Key& key) const;
  iterator                                 upper_bound(const Key& key);
  const_iterator                           upper_bound(const Key& key) const;

  // == observers ==
  key_compare            key_comp() const { return key_compare(); };
  ft::map::value_compare value_comp() const {
    return value_compare(key_compare());
  };
};

// == non member functions ==
template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs);
template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs);
template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs);
template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs);
template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs);
template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs);

template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs,
          ft::map<Key, T, Compare, Alloc>& rhs);

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_MAP_HPP */
