#ifndef FT_CONTAINERS_INCLUDES_SET_HPP
#define FT_CONTAINERS_INCLUDES_SET_HPP

#include <functional>

#include "RBtree.hpp"
#include "function.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class Key, class Compare = std::less<Key>,
          typename Alloc = std::allocator<Key> >
class set {
public:
  typedef Key                             key_type;
  typedef Key                             value_type;
  typedef std::size_t                     size_type;
  typedef std::ptrdiff_t                  difference_type;
  typedef Compare                         key_compare;
  typedef Compare                         value_compare;
  typedef Alloc                           allocator_type;
  typedef typename Alloc::reference       reference;
  typedef typename Alloc::const_reference const_reference;
  typedef typename Alloc::pointer         pointer;
  typedef typename Alloc::const_pointer   const_pointer;

private:
  typedef typename allocator_type::template rebind<value_type>::other
      Pair_alloc_type;

  typedef RBtree<key_type, value_type, _Identity<value_type>, key_compare,
                 Pair_alloc_type>
      tree_type;

public:
  typedef typename tree_type::const_iterator   iterator;
  typedef typename tree_type::const_iterator   const_iterator;
  typedef ft::reverse_iterator<iterator>       reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
  tree_type tree_;

public:
  // == constructor / destructor ==
  explicit set(const Compare& comp = Compare(), const Alloc& alloc = Alloc())
      : tree_(comp, Pair_alloc_type(alloc)) {}

  template <class InputIt>
  set(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Alloc& alloc = Alloc())
      : tree_(first, last, comp, Pair_alloc_type(alloc)) {}

  set(const set& other) : tree_(other.tree_) {}

  ~set() {}

  // == assignation ==
  set& operator=(const set& other) {
    tree_ = other.tree_;
    return *this;
  }

  allocator_type get_allocator() const { return Alloc(); }

  // == iterators ==
  iterator               begin() { return tree_.begin(); }
  const_iterator         begin() const { return tree_.begin(); }
  iterator               end() { return tree_.end(); }
  const_iterator         end() const { return tree_.end(); }
  reverse_iterator       rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator       rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // == capacity ==
  bool      empty() const { return tree_.size() == 0; }
  size_type size() const { return tree_.size(); }
  size_type max_size() const { return tree_.max_size(); }

  // == modifiers ==
  pair<iterator, bool> insert(const value_type& val) {
    return tree_.insert(val);
  }
  iterator insert(iterator position, const value_type& val) {
    return tree_.insert(position, val);
  }
  template <class InputIt>
  void insert(InputIt first, InputIt last) {
    return tree_.insert(first, last);
  }

  void      erase(iterator position) { return tree_.erase(position); }
  size_type erase(const Key& key) { return tree_.erase(key); }
  void      erase(const_iterator first, const_iterator last) {
    tree_.erase(first, last);
  }

  void swap(set& x) { return tree_.swap(x.tree_); }
  void clear() { return tree_.clear(); }

  // == lookup ==
  size_type      count(const Key& key) const { return tree_.count(key); }
  iterator       find(const Key& key) { return tree_.find(key); }
  const_iterator find(const Key& key) const { return tree_.find(key); }
  ft::pair<iterator, iterator> equal_range(const Key& key) {
    return tree_.equal_range(key);
  }
  ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    return tree_.equal_range(key);
  }
  iterator       lower_bound(const Key& key) { return tree_.lower_bound(key); }
  const_iterator lower_bound(const Key& key) const {
    return tree_.lower_bound(key);
  }
  iterator       upper_bound(const Key& key) { return tree_.upper_bound(key); }
  const_iterator upper_bound(const Key& key) const {
    return tree_.upper_bound(key);
  }

  // == observers ==
  key_compare   key_comp() const { return key_compare(); };
  value_compare value_comp() const { return value_compare(key_compare()); };

  template <class _Key, class _Compare, class _Alloc>
  friend bool operator==(const ft::set<_Key, _Compare, _Alloc>& lhs,
                         const ft::set<_Key, _Compare, _Alloc>& rhs);

  template <class _Key, class _Compare, class _Alloc>
  friend bool operator<(const ft::set<_Key, _Compare, _Alloc>& lhs,
                        const ft::set<_Key, _Compare, _Alloc>& rhs);
};

// == non member functions ==
template <class Key, class Compare, class Alloc>
bool operator==(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs) {
  return lhs.tree_ == rhs.tree_;
}

template <class Key, class Compare, class Alloc>
bool operator!=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool operator<(const ft::set<Key, Compare, Alloc>& lhs,
               const ft::set<Key, Compare, Alloc>& rhs) {
  return lhs.tree_ < rhs.tree_;
}

template <class Key, class Compare, class Alloc>
bool operator>(const ft::set<Key, Compare, Alloc>& lhs,
               const ft::set<Key, Compare, Alloc>& rhs) {
  return rhs < lhs;
}

template <class Key, class Compare, class Alloc>
bool operator<=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool operator>=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <class Key, class Compare, class Alloc>
void swap(ft::set<Key, Compare, Alloc>& lhs,
          ft::set<Key, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_SET_HPP */
