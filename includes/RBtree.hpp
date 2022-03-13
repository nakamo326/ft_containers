#ifndef FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP
#define FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP

#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "pair.hpp"
#include "utils.hpp"

namespace ft {

enum _RBtree_color { e_red = false, e_black = true };

template <typename Value>
struct _RBnode {
  typedef Value               value_type;
  typedef _RBnode<value_type> node_type;
  typedef node_type*          node_pointer;

  value_type    value_;
  node_pointer  left_;
  node_pointer  right_;
  node_pointer  parent_;
  _RBtree_color color_;

  _RBnode(value_type value = Value())
      : value_(value),
        left_(NULL),
        right_(NULL),
        parent_(NULL),
        color_(e_red) {}

  void outputInfo() {
    std::cout << "------------------------------" << std::endl;
    std::cout << "&this  : " << std::hex << this << std::dec << std::endl;
    std::cout << "key    : " << value_.first << std::endl;
    std::cout << "value  : " << value_.second << std::endl;
    std::cout << "parent : " << std::hex << parent_ << std::dec << std::endl;
    std::cout << "left   : " << std::hex << left_ << std::dec << std::endl;
    std::cout << "right  : " << std::hex << right_ << std::dec << std::endl;
    std::cout << "color  : ";
    if (color_)
      std::cout << "black" << std::endl;
    else
      std::cout << "red" << std::endl;
  }
};

template <typename T>
struct RBtree_iterator {
  typedef std::bidirectional_iterator_tag              iterator_category;
  typedef typename iterator_traits<T>::value_type      value_type;
  typedef typename iterator_traits<T>::pointer         pointer;
  typedef typename iterator_traits<T>::reference       reference;
  typedef typename iterator_traits<T>::difference_type difference_type;
  typedef RBtree_iterator<T>                           _Self;
  typedef _RBnode<value_type>*                         node_pointer;

  RBtree_iterator() : node_(NULL) {}
  RBtree_iterator(node_pointer __x) : node_(__x) {}
  RBtree_iterator(RBtree_iterator const& other) : node_(other.node_) {}
  template <typename _Iter>
  RBtree_iterator(const RBtree_iterator<_Iter>& __x) : node_(__x.node_) {}
  RBtree_iterator& operator=(const RBtree_iterator& __x) {
    node_ = __x.node_;
    return *this;
  }

  reference operator*() const { return node_->value_; }
  pointer   operator->() const { return &node_->value_; }

  node_pointer _RBtreeIncrement(node_pointer __x) {
    if (__x->right_ != NULL) {
      __x = __x->right_;
      while (__x->left_ != NULL) __x = __x->left_;
    } else {
      node_pointer tmp = __x->parent_;
      while (__x == tmp->right_) {
        __x = tmp;
        tmp = tmp->parent_;
      }
      __x = tmp;
    }
    return __x;
  }

  node_pointer _RBtreeDecrement(node_pointer __x) {
    if (__x->left_ != NULL) {
      node_pointer tmp = __x->left_;
      while (tmp->right_ != NULL) tmp = tmp->right_;
      __x = tmp;
    } else {
      node_pointer tmp = __x->parent_;
      while (__x == tmp->left_) {
        __x = tmp;
        tmp = tmp->parent_;
      }
      __x = tmp;
    }
    return __x;
  }

  _Self& operator++() {
    node_ = _RBtreeIncrement(node_);
    return *this;
  }

  _Self operator++(int) {
    _Self tmp = *this;
    node_     = _RBtreeIncrement(node_);
    return tmp;
  }

  _Self& operator--() {
    node_ = _RBtreeDecrement(node_);
    return *this;
  }

  _Self operator--(int) {
    _Self tmp = *this;
    node_     = _RBtreeDecrement(node_);
    return tmp;
  }

  node_pointer base() const { return node_; }

  node_pointer node_;
};

template <class T, class U>
bool operator==(const RBtree_iterator<T>& lhs, const RBtree_iterator<U>& rhs) {
  return lhs.base() == rhs.base();
}

template <class T, class U>
bool operator!=(const RBtree_iterator<T>& lhs, const RBtree_iterator<U>& rhs) {
  return !(lhs == rhs);
}

// case) map
// key == value.first value == ft::pair<key, ...> KeyOfValue == _Select1st
template <typename Key, typename Value, typename KeyOfValue, typename Comp,
          typename Pair_alloc_type = std::allocator<Value> >
class RBtree {
public:
  typedef Key                                key_type;
  typedef Value                              value_type;
  typedef _RBnode<value_type>                node_type;
  typedef node_type*                         node_pointer;
  typedef size_t                             size_type;
  typedef std::ptrdiff_t                     difference_type;
  typedef RBtree_iterator<value_type*>       iterator;
  typedef RBtree_iterator<const value_type*> const_iterator;

  typedef RBtree<Key, Value, KeyOfValue, Comp, Pair_alloc_type> _Self;

  typedef typename Pair_alloc_type::template rebind<_RBnode<Value> >::other
      node_allocator;

private:
  // == accessor ==
  bool isBlack(node_pointer node) {
    return node == NULL || node->color_ == e_black;
  }

  bool isRed(node_pointer node) { return node->color_ == e_red; }

  void setBlack(node_pointer node) {
    if (node == NULL)
      return;
    node->color_ = e_black;
  }

  void setRed(node_pointer node) {
    if (node == NULL)
      return;
    node->color_ = e_red;
  }

  bool isLeftChild(node_pointer node) { return node->parent_->left_ == node; }

  key_type getKeyOfValue(const Value& value) const {
    return KeyOfValue()(value);
  }

  // == helpers ==

  // precondition: node has grandparent
  bool isUncleNodeBlack(node_pointer node) {
    if (isLeftChild(node->parent_))
      return isBlack(node->parent_->parent_->right_);
    return isBlack(node->parent_->parent_->left_);
  }

  void flipColor(node_pointer node) {
    setRed(node->parent_->parent_);
    setBlack(node->parent_->parent_->left_);
    setBlack(node->parent_->parent_->right_);
  }

  node_pointer searchKey(const key_type& key, node_pointer node) const {
    while (node != NULL) {
      if (getKeyOfValue(node->value_) == key)
        break;
      if (comp_(getKeyOfValue(node->value_), key))
        node = node->right_;
      else
        node = node->left_;
    }
    return node;
  }

  node_pointer searchMinimum(node_pointer node) {
    while (node->left_ != NULL) {
      node = node->left_;
    }
    return node;
  }

  void updateBeginNodeInsert(node_pointer new_node) {
    if (begin_ != header_ &&
        comp_(getKeyOfValue(new_node->value_), getKeyOfValue(begin_->value_)))
      begin_ = new_node;
  }

  // == insert ==
  void insert(node_pointer parent, node_pointer new_node) {
    if (comp_(getKeyOfValue(parent->value_), getKeyOfValue(new_node->value_))) {
      if (parent->right_ == NULL) {
        parent->right_    = new_node;
        new_node->parent_ = parent;
        return checkColor(new_node);
      }
      return insert(parent->right_, new_node);
    } else {
      if (parent->left_ == NULL) {
        parent->left_     = new_node;
        new_node->parent_ = parent;
        updateBeginNodeInsert(new_node);
        return checkColor(new_node);
      }
      return insert(parent->left_, new_node);
    }
  }

  void checkColor(node_pointer node) {
    if (node == root_) {
      if (isRed(node))
        setBlack(node);
      return;
    }
    if (isRed(node) && isRed(node->parent_))
      correctTree(node);
    if (node != root_)
      checkColor(node->parent_);
  }

  // black uncle rotate, red uncle color flip
  void correctTree(node_pointer node) {
    if (isUncleNodeBlack(node))
      return rotate(node);
    flipColor(node);
  }

  // == rotate ==
  void rotate(node_pointer node) {
    node_pointer new_parent;
    if (isLeftChild(node)) {
      if (isLeftChild(node->parent_))
        new_parent = rightRotate(node->parent_->parent_);
      else
        new_parent = rightLeftRotate(node->parent_->parent_);
    } else {
      if (!isLeftChild(node->parent_))
        new_parent = leftRotate(node->parent_->parent_);
      else
        new_parent = leftRightRotate(node->parent_->parent_);
    }
    setFamilyColor(new_parent);
    return;
  }

  void setFamilyColor(node_pointer parent) {
    setBlack(parent);
    setRed(parent->left_);
    setRed(parent->right_);
  }

  node_pointer leftRightRotate(node_pointer node) {
    leftRotate(node->left_);
    return rightRotate(node);
  }

  node_pointer rightLeftRotate(node_pointer node) {
    rightRotate(node->right_);
    return leftRotate(node);
  }

  node_pointer leftRotate(node_pointer node) {
    node_pointer tmp = node->right_;
    node->right_     = tmp->left_;
    if (node->right_ != NULL) {
      node->right_->parent_ = node;
    }
    if (node == root_) {
      tmp->parent_ = header_;
      root_ = header_->left_ = tmp;
    } else {
      tmp->parent_ = node->parent_;
      if (isLeftChild(node)) {
        tmp->parent_->left_ = tmp;
      } else {
        tmp->parent_->right_ = tmp;
      }
    }
    tmp->left_    = node;
    node->parent_ = tmp;
    return tmp;
  }

  node_pointer rightRotate(node_pointer node) {
    node_pointer tmp = node->left_;
    node->left_      = tmp->right_;
    if (node->left_ != NULL) {
      node->left_->parent_ = node;
    }
    if (node == root_) {
      tmp->parent_ = header_;
      root_ = header_->left_ = tmp;
    } else {
      tmp->parent_ = node->parent_;
      if (isLeftChild(node)) {
        tmp->parent_->left_ = tmp;
      } else {
        tmp->parent_->right_ = tmp;
      }
    }
    tmp->right_   = node;
    node->parent_ = tmp;
    return tmp;
  }

  // == delete ==

  // set newNode to old position
  void transplantNodes(node_pointer old, node_pointer new_node) {
    if (old == root_) {
      root_ = header_->left_ = new_node;
    } else if (isLeftChild(old)) {
      old->parent_->left_ = new_node;
    } else {
      old->parent_->right_ = new_node;
    }
    if (new_node != NULL)
      new_node->parent_ = old->parent_;
  }

  bool deleteNode(node_pointer z) {
    node_pointer  x, y;
    _RBtree_color y_color;
    node_pointer  x_parent;

    y        = z;
    y_color  = y->color_;
    x_parent = y->parent_;

    if (z->left_ == NULL) {
      x = z->right_;
      transplantNodes(z, z->right_);
    } else if (z->right_ == NULL) {
      x = z->left_;
      transplantNodes(z, z->left_);
    } else {
      y        = searchMinimum(z->right_);
      y_color  = y->color_;
      x        = y->right_;
      x_parent = y->parent_;

      if (y->parent_ == z) {
        x_parent = y;
      } else {
        transplantNodes(y, y->right_);
        y->right_          = z->right_;
        y->right_->parent_ = y;
      }
      transplantNodes(z, y);
      y->left_          = z->left_;
      y->left_->parent_ = y;
      y->color_         = z->color_;
    }

    deallocateNode(z);
    if (y_color == e_black)
      fixDeletion(x, x_parent);
    size_--;
    return true;
  }

  // node could be NULL
  void fixDeletion(node_pointer node, node_pointer parent) {
    node_pointer s;
    while (node != root_ && (node == NULL || node->color_ == e_black)) {
      if (node == parent->left_) {
        s = parent->right_;
        if (isRed(s)) {
          setBlack(s);
          setRed(parent);
          leftRotate(parent);
          s = parent->right_;
        }
        if (isBlack(s->left_) && isBlack(s->right_)) {
          setRed(s);
          node   = parent;
          parent = parent->parent_;
        } else {
          if (isBlack(s->right_)) {
            setBlack(s->left_);
            setRed(s);
            rightRotate(s);
            s = parent->right_;
          }

          s->color_ = parent->color_;
          setBlack(parent);
          setBlack(s->right_);
          leftRotate(parent);
          node = root_;
        }
      } else {
        s = parent->left_;
        if (isRed(s)) {
          setBlack(s);
          setRed(parent);
          rightRotate(parent);
          s = parent->left_;
        }
        if (isBlack(s->right_) && isBlack(s->left_)) {
          setRed(s);
          node   = parent;
          parent = parent->parent_;
        } else {
          if (isBlack(s->left_)) {
            setBlack(s->right_);
            setRed(s);
            leftRotate(s);
            s = parent->left_;
          }

          s->color_ = parent->color_;
          setBlack(parent);
          setBlack(s->left_);
          rightRotate(parent);
          node = root_;
        }
      }
    }
    setBlack(node);
  }

  size_type blackNodes(node_pointer node) {
    if (node == NULL)
      return 1;
    size_type leftBlackNodes  = blackNodes(node->right_);
    size_type rightBlackNodes = blackNodes(node->left_);
    if (leftBlackNodes != rightBlackNodes) {
      throw std::logic_error("this tree is imbalance");
    }
    if (isBlack(node))
      leftBlackNodes++;
    return leftBlackNodes;
  }

  bool checkConsecutiveRed(node_pointer node) {
    if (node == NULL)
      return true;
    if (isRed(node)) {
      if (node->left_ != NULL && isRed(node->left_))
        return false;
      if (node->right_ != NULL && isRed(node->right_))
        return false;
    }
    return checkConsecutiveRed(node->left_) &&
           checkConsecutiveRed(node->right_);
  }

  void deallocateNode(node_pointer node) {
    alloc_.destroy(node);
    alloc_.deallocate(node, 1);
  }

  void destroyTree(node_pointer node) {
    if (node == NULL)
      return;
    destroyTree(node->left_);
    destroyTree(node->right_);
    deallocateNode(node);
  }

  void initHeader() {
    header_          = alloc_.allocate(1);
    header_->parent_ = NULL;
    header_->left_   = NULL;
    header_->right_  = NULL;
    setBlack(header_);
  }

private:
  node_pointer   header_;
  node_pointer   root_;
  node_pointer   begin_;
  size_t         size_;
  Comp           comp_;
  node_allocator alloc_;

  // === public member function ===
public:
  // == constructor / destructor ==
  RBtree(const Comp&            comp  = Comp(),
         const Pair_alloc_type& alloc = Pair_alloc_type())
      : header_(NULL),
        root_(NULL),
        begin_(NULL),
        size_(0),
        comp_(comp),
        alloc_(alloc) {
    initHeader();
    begin_ = header_;
  }

  template <typename InputIt>
  RBtree(InputIt first, InputIt last, const Comp& comp,
         const node_allocator& alloc)
      : RBtree(comp, alloc) {
    insert(first, last);
  }

  RBtree(const _Self& other)
      : RBtree(other.begin(), other.end(), Comp(), node_allocator()) {}

  ~RBtree() { destroyTree(header_); }

  // == iterators ==
  iterator       begin() { return iterator(begin_); }
  const_iterator begin() const { return const_iterator(begin_); }
  iterator       end() { return iterator(header_); }
  const_iterator end() const { return const_iterator(header_); }

  // == capacity ==
  size_type size() const { return size_; }
  size_type max_size() const {
    return std::min<size_type>(alloc_.max_size(),
                               std::numeric_limits<difference_type>::max());
  }

  // == modifiers ==

  // 重複を許可しない
  ft::pair<iterator, bool> insert(const value_type& value) {
    iterator res = find(getKeyOfValue(value));
    if (res != end()) {
      return ft::make_pair(res, false);
    }
    node_pointer new_node = alloc_.allocate(1);
    alloc_.construct(new_node, node_type(value));
    if (root_ == NULL) {
      root_          = new_node;
      root_->parent_ = header_;
      begin_         = root_;
      header_->left_ = root_;
      setBlack(root_);
    } else {
      insert(root_, new_node);
    }
    size_++;
    return ft::make_pair(iterator(new_node), true);
  }

  // iterator insert(iterator position, const value_type& val);

  template <typename InputIt>
  void insert(InputIt first, InputIt last) {
    for (; first != last; first++) {
      insert(*first);
    }
  }

  void erase(const_iterator position) {
    if (position == end())
      return;
    if (position.base() == begin_)
      begin_ = begin_->parent_;
    deleteNode(position.base());
  }

  size_type erase(const key_type& key) {
    iterator target = find(key);
    if (target == end())
      return 0;
    erase(target);
    return 1;
  }

  // iterator  erase(const_iterator first, const_iterator last);

  // void swap(map& x);
  // void clear();

  // == lookup ==
  size_type count(const Key& key) const {
    node_pointer res = searchKey(key, root_);
    if (res == NULL)
      return 0;
    return 1;
  }
  // TODO: check searchKey return NULL when size == 0
  iterator find(const Key& key) {
    node_pointer res = searchKey(key, root_);
    if (res == NULL)
      return (end());
    return iterator(res);
  }
  const_iterator find(const Key& key) const {
    node_pointer res = searchKey(key, root_);
    if (res == NULL)
      return (end());
    return const_iterator(res);
  }
  // ft::pair<iterator, iterator>             equal_range(const Key& key);
  // ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
  // iterator                                 lower_bound(const Key& key);
  // const_iterator                           lower_bound(const Key& key) const;
  // iterator                                 upper_bound(const Key& key);
  // const_iterator                           upper_bound(const Key& key) const;

  // == for debug ==
  void outputAllTree() { outputTree(root_); }

  node_pointer getBeginNode() { return begin_; }

  void outputTree(node_pointer node) {
    if (node == NULL)
      return;
    node->outputInfo();
    outputTree(node->left_);
    outputTree(node->right_);
    return;
  }

  void checkBlackNodes() { blackNodes(root_); }

  bool isValidTree() {
    if (root_ == NULL)
      return true;
    if (root_->parent_ != header_)
      return false;
    if (isRed(root_))
      return false;
    try {
      checkBlackNodes();
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      return false;
    }
    return checkConsecutiveRed(root_);
  }
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP */
