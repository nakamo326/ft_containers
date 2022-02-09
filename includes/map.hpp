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
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_MAP_HPP */
