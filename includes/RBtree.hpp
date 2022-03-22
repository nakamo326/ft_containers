#ifndef FT_CONTAINERS_INCLUDES_RBTREE_HPP
#define FT_CONTAINERS_INCLUDES_RBTREE_HPP

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

  void output_info() {
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

  node_pointer _RBtree_increment(node_pointer __x) {
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

  node_pointer _RBtree_decrement(node_pointer __x) {
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
    node_ = _RBtree_increment(node_);
    return *this;
  }

  _Self operator++(int) {
    _Self tmp = *this;
    node_     = _RBtree_increment(node_);
    return tmp;
  }

  _Self& operator--() {
    node_ = _RBtree_decrement(node_);
    return *this;
  }

  _Self operator--(int) {
    _Self tmp = *this;
    node_     = _RBtree_decrement(node_);
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
          typename Alloc = std::allocator<Value> >
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

  typedef RBtree<Key, Value, KeyOfValue, Comp, Alloc> _Self;

  typedef
      typename Alloc::template rebind<_RBnode<Value> >::other node_allocator;

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
  RBtree(const Comp& comp = Comp(), const Alloc& alloc = Alloc())
      : header_(NULL),
        root_(NULL),
        begin_(NULL),
        size_(0),
        comp_(comp),
        alloc_(alloc) {
    init_header();
    begin_ = header_;
  }

  template <typename InputIt>
  RBtree(InputIt first, InputIt last, const Comp& comp,
         const node_allocator& alloc)
      : header_(NULL),
        root_(NULL),
        begin_(NULL),
        size_(0),
        comp_(comp),
        alloc_(alloc) {
    init_header();
    begin_ = header_;
    insert(first, last);
  }

  RBtree(const _Self& other)
      : header_(NULL),
        root_(NULL),
        begin_(NULL),
        size_(0),
        comp_(Comp()),
        alloc_(node_allocator()) {
    init_header();
    begin_ = header_;
    insert(other.begin(), other.end());
  }

  ~RBtree() { destroy_tree(header_); }

  // == assignation ==
  RBtree& operator=(const RBtree& other) {
    if (this == &other)
      return *this;
    clear();
    comp_  = other.comp_;
    alloc_ = other.alloc_;
    insert(other.begin(), other.end());
    return *this;
  }

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
  ft::pair<iterator, bool> insert(const value_type& value) {
    node_pointer res = search_insert_position(get_key(value));
    return insert_with_pos(value, res);
  }

  iterator insert(iterator position, const value_type& val) {
    pair<iterator, node_pointer> res = search_pos_with_hint(val, position);
    if (res.second == NULL) {
      return insert_with_pos(val, res.first.base()).first;
    }
    return res.first;
  }

  template <typename InputIt>
  void insert(InputIt first, InputIt last) {
    for (; first != last; first++) {
      insert(*first);
    }
  }

  void erase(iterator position) {
    if (position == end())
      return;
    if (position.base() == begin_)
      begin_ = begin_->parent_;
    delete_node(position.base());
  }

  size_type erase(const key_type& key) {
    iterator target = find(key);
    if (target == end())
      return 0;
    erase(target);
    return 1;
  }

  void erase(const_iterator first, const_iterator last) {
    while (first != last) {
      erase(first++);
    }
  }

  void swap(RBtree& x) {
    std::swap(header_, x.header_);
    std::swap(root_, x.root_);
    std::swap(begin_, x.begin_);
    std::swap(size_, x.size_);
  }
  void clear() {
    destroy_tree(header_);
    root_ = NULL;
    init_header();
    begin_ = header_;
    size_  = 0;
  }

  // == lookup ==
  size_type count(const Key& key) const {
    node_pointer res = find_helper(key, root_);
    if (res == NULL)
      return 0;
    return 1;
  }

  iterator find(const Key& key) {
    node_pointer res = find_helper(key, root_);
    if (res == NULL)
      return (end());
    return iterator(res);
  }

  const_iterator find(const Key& key) const {
    node_pointer res = find_helper(key, root_);
    if (res == NULL)
      return (end());
    return const_iterator(res);
  }

  ft::pair<iterator, iterator> equal_range(const Key& key) {
    ft::pair<node_pointer, node_pointer> res = equal_range_helper(key);
    return ft::make_pair(iterator(res.first), iterator(res.second));
  }

  ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    ft::pair<node_pointer, node_pointer> res = equal_range_helper(key);
    return ft::make_pair(const_iterator(res.first), const_iterator(res.second));
  }

  iterator lower_bound(const Key& key) {
    node_pointer res = lower_bound_helper(root_, header_, key);
    return iterator(res);
  }

  const_iterator lower_bound(const Key& key) const {
    node_pointer res = lower_bound_helper(root_, header_, key);
    return const_iterator(res);
  }

  iterator upper_bound(const Key& key) {
    node_pointer res = upper_bound_helper(root_, header_, key);
    return iterator(res);
  }
  const_iterator upper_bound(const Key& key) const {
    node_pointer res = upper_bound_helper(root_, header_, key);
    return const_iterator(res);
  }

  friend bool operator==(const RBtree& lhs, const RBtree& rhs) {
    return lhs.size() == rhs.size() &&
           ft::equal(lhs.begin(), lhs.end(), rhs.begin());
  }

  friend bool operator<(const RBtree& lhs, const RBtree& rhs) {
    return ft::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

private:
  // == accessor ==
  bool is_black(node_pointer node) {
    return node == NULL || node->color_ == e_black;
  }

  bool is_red(node_pointer node) {
    if (node == NULL)
      return false;
    return node->color_ == e_red;
  }

  void set_black(node_pointer node) {
    if (node == NULL)
      return;
    node->color_ = e_black;
  }

  void set_red(node_pointer node) {
    if (node == NULL)
      return;
    node->color_ = e_red;
  }

  bool is_left_child(node_pointer node) { return node->parent_->left_ == node; }

  key_type get_key(const Value& value) const { return KeyOfValue()(value); }

  // == helpers ==

  // precondition: node has grandparent
  bool is_uncle_node_black(node_pointer node) {
    if (is_left_child(node->parent_))
      return is_black(node->parent_->parent_->right_);
    return is_black(node->parent_->parent_->left_);
  }

  void flip_color(node_pointer node) {
    set_red(node->parent_->parent_);
    set_black(node->parent_->parent_->left_);
    set_black(node->parent_->parent_->right_);
  }

  node_pointer find_helper(const key_type& key, node_pointer node) const {
    while (node != NULL) {
      if (comp_(get_key(node->value_), key))
        node = node->right_;
      else if (comp_(key, get_key(node->value_)))
        node = node->left_;
      else
        return node;
    }
    return NULL;
  }

  node_pointer search_minimum(node_pointer node) {
    while (node->left_ != NULL) {
      node = node->left_;
    }
    return node;
  }

  ft::pair<node_pointer, node_pointer> equal_range_helper(const Key& key) {
    node_pointer node  = root_;
    node_pointer upper = header_;

    while (node != NULL) {
      if (comp_(get_key(node->value_), key)) {
        node = node->right_;
      } else if (comp_(key, get_key(node->value_))) {
        upper = node;
        node  = node->left_;
      } else {
        node_pointer l_node = node->left_;
        node_pointer lower  = node;
        node                = node->right_;
        return ft::make_pair(lower_bound_helper(l_node, lower, key),
                             upper_bound_helper(node, upper, key));
      }
    }
    return ft::make_pair(upper, upper);
  }

  node_pointer lower_bound_helper(node_pointer node, node_pointer res,
                                  const key_type& key) {
    while (node != NULL) {
      if (!comp_(get_key(node->value_), key)) {
        res  = node;
        node = node->left_;
      } else {
        node = node->right_;
      }
    }
    return res;
  }

  node_pointer upper_bound_helper(node_pointer node, node_pointer res,
                                  const key_type& key) {
    while (node != NULL) {
      if (comp_(key, get_key(node->value_))) {
        res  = node;
        node = node->left_;
      } else {
        node = node->right_;
      }
    }
    return res;
  }

  // 挿入されたノードが左の子のときbeginノードは更新される可能性がある
  void update_begin_node(node_pointer new_node) {
    if (begin_ != header_ &&
        comp_(get_key(new_node->value_), get_key(begin_->value_)))
      begin_ = new_node;
  }

  // == insert helpers ==

  pair<iterator, node_pointer> search_pos_with_hint(const value_type& val,
                                                    iterator          hint) {
    typedef pair<iterator, node_pointer> _Res;
    node_pointer                         dummy = header_;
    key_type                             key   = get_key(val);

    if (hint == end() || comp_(key, get_key(*hint))) {
      // key < hint
      iterator prev = hint;
      if (prev == begin() || comp_(get_key(*--prev), key)) {
        // prev < key < hint
        if (hint.base()->left_ == NULL) {
          return _Res(hint, hint.base()->left_);
        } else {
          return _Res(prev, prev.base()->right_);
        }
      }
      return _Res(insert(val).first, dummy);
    } else if (comp_(get_key(*hint), key)) {
      iterator next = hint;
      next++;
      if (next == end() || comp_(key, get_key(*next))) {
        if (hint.base()->right_ == NULL) {
          return _Res(hint, hint.base()->right_);
        } else {
          return _Res(next, next.base()->left_);
        }
      }
      return _Res(insert(val).first, dummy);
    }
    // key == *hint
    return _Res(hint, dummy);
  }

  // rootからkeyを挿入するべき親ノードを返す。もし同値のkeyをもつノードが見つかった時はその位置を返す。
  // 同値のキーが見つかった時を除いて、挿入する枝がNULLであることが保証される。
  // if root == NULL return NULL
  node_pointer search_insert_position(const key_type& key) {
    node_pointer node = root_;
    node_pointer res  = NULL;
    while (node != NULL) {
      res = node;
      if (comp_(get_key(node->value_), key)) {
        node = node->right_;
      } else if (comp_(key, get_key(node->value_))) {
        node = node->left_;
      } else {
        return node;
      }
    }
    return res;
  }

  ft::pair<iterator, bool> insert_with_pos(const value_type& value,
                                           node_pointer      pos) {
    node_pointer new_node = generate_node(value);
    new_node->parent_     = pos;
    if (root_ == NULL) {
      set_root(new_node);
    } else if (comp_(get_key(pos->value_), get_key(value))) {
      pos->right_ = new_node;
    } else if (comp_(get_key(value), get_key(pos->value_))) {
      pos->left_ = new_node;
      update_begin_node(new_node);
    } else {
      deallocate_node(new_node);
      return ft::make_pair(iterator(pos), false);
    }
    fix_insertion(new_node);
    size_++;
    return ft::make_pair(iterator(new_node), true);
  }

  void fix_insertion(node_pointer node) {
    if (node == root_) {
      if (is_red(node))
        set_black(node);
      return;
    }
    if (is_red(node) && is_red(node->parent_))
      correct_tree(node);
    if (node != root_)
      fix_insertion(node->parent_);
  }

  // black uncle rotate, red uncle color flip
  void correct_tree(node_pointer node) {
    if (is_uncle_node_black(node))
      return rotate(node);
    flip_color(node);
  }

  // == rotate ==
  void rotate(node_pointer node) {
    node_pointer new_parent;
    if (is_left_child(node)) {
      if (is_left_child(node->parent_))
        new_parent = right_rotate(node->parent_->parent_);
      else
        new_parent = right_left_rotate(node->parent_->parent_);
    } else {
      if (!is_left_child(node->parent_))
        new_parent = left_rotate(node->parent_->parent_);
      else
        new_parent = left_right_rotate(node->parent_->parent_);
    }
    set_black(new_parent);
    set_red(new_parent->left_);
    set_red(new_parent->right_);
    return;
  }

  node_pointer left_right_rotate(node_pointer node) {
    left_rotate(node->left_);
    return right_rotate(node);
  }

  node_pointer right_left_rotate(node_pointer node) {
    right_rotate(node->right_);
    return left_rotate(node);
  }

  node_pointer left_rotate(node_pointer node) {
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
      if (is_left_child(node)) {
        tmp->parent_->left_ = tmp;
      } else {
        tmp->parent_->right_ = tmp;
      }
    }
    tmp->left_    = node;
    node->parent_ = tmp;
    return tmp;
  }

  node_pointer right_rotate(node_pointer node) {
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
      if (is_left_child(node)) {
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
  void transplant_nodes(node_pointer old, node_pointer new_node) {
    if (old == root_) {
      root_ = header_->left_ = new_node;
    } else if (is_left_child(old)) {
      old->parent_->left_ = new_node;
    } else {
      old->parent_->right_ = new_node;
    }
    if (new_node != NULL)
      new_node->parent_ = old->parent_;
  }

  bool delete_node(node_pointer z) {
    node_pointer  x, y;
    _RBtree_color y_color;
    node_pointer  x_parent;

    y        = z;
    y_color  = y->color_;
    x_parent = y->parent_;

    if (z->left_ == NULL) {
      x = z->right_;
      transplant_nodes(z, z->right_);
    } else if (z->right_ == NULL) {
      x = z->left_;
      transplant_nodes(z, z->left_);
    } else {
      y        = search_minimum(z->right_);
      y_color  = y->color_;
      x        = y->right_;
      x_parent = y->parent_;

      if (y->parent_ == z) {
        x_parent = y;
      } else {
        transplant_nodes(y, y->right_);
        y->right_          = z->right_;
        y->right_->parent_ = y;
      }
      transplant_nodes(z, y);
      y->left_          = z->left_;
      y->left_->parent_ = y;
      y->color_         = z->color_;
    }

    deallocate_node(z);
    if (y_color == e_black)
      fix_deletion(x, x_parent);
    size_--;
    return true;
  }

  // node could be NULL
  void fix_deletion(node_pointer node, node_pointer parent) {
    node_pointer s;
    while (node != root_ && (node == NULL || node->color_ == e_black)) {
      if (node == parent->left_) {
        s = parent->right_;
        if (is_red(s)) {
          set_black(s);
          set_red(parent);
          left_rotate(parent);
          s = parent->right_;
        }
        if (is_black(s->left_) && is_black(s->right_)) {
          set_red(s);
          node   = parent;
          parent = parent->parent_;
        } else {
          if (is_black(s->right_)) {
            set_black(s->left_);
            set_red(s);
            right_rotate(s);
            s = parent->right_;
          }

          s->color_ = parent->color_;
          set_black(parent);
          set_black(s->right_);
          left_rotate(parent);
          node = root_;
        }
      } else {
        s = parent->left_;
        if (is_red(s)) {
          set_black(s);
          set_red(parent);
          right_rotate(parent);
          s = parent->left_;
        }
        if (is_black(s->right_) && is_black(s->left_)) {
          set_red(s);
          node   = parent;
          parent = parent->parent_;
        } else {
          if (is_black(s->left_)) {
            set_black(s->right_);
            set_red(s);
            left_rotate(s);
            s = parent->left_;
          }

          s->color_ = parent->color_;
          set_black(parent);
          set_black(s->left_);
          right_rotate(parent);
          node = root_;
        }
      }
    }
    set_black(node);
  }

  void deallocate_node(node_pointer node) {
    alloc_.destroy(node);
    alloc_.deallocate(node, 1);
  }

  void destroy_tree(node_pointer node) {
    if (node == NULL)
      return;
    destroy_tree(node->left_);
    destroy_tree(node->right_);
    deallocate_node(node);
  }

  void init_header() {
    header_          = alloc_.allocate(1);
    header_->parent_ = NULL;
    header_->left_   = NULL;
    header_->right_  = NULL;
    set_black(header_);
  }

  void set_root(node_pointer new_root) {
    root_          = new_root;
    root_->parent_ = header_;
    begin_         = root_;
    header_->left_ = root_;
    set_black(root_);
  }

  node_pointer generate_node(const value_type& value) {
    node_pointer new_node = alloc_.allocate(1);
    alloc_.construct(new_node, node_type(value));
    return new_node;
  }

  // == for debug ==
  size_type black_nodes(node_pointer node) {
    if (node == NULL)
      return 1;
    size_type leftBlackNodes  = black_nodes(node->right_);
    size_type rightBlackNodes = black_nodes(node->left_);
    if (leftBlackNodes != rightBlackNodes) {
      throw std::logic_error("this tree is imbalance");
    }
    if (is_black(node))
      leftBlackNodes++;
    return leftBlackNodes;
  }

  bool check_consecutive_red(node_pointer node) {
    if (node == NULL)
      return true;
    if (is_red(node)) {
      if (node->left_ != NULL && is_red(node->left_))
        return false;
      if (node->right_ != NULL && is_red(node->right_))
        return false;
    }
    return check_consecutive_red(node->left_) &&
           check_consecutive_red(node->right_);
  }

public:
  void output_all_tree() { output_tree(root_); }

  node_pointer get_begin_node() { return begin_; }

  void output_tree(node_pointer node) {
    if (node == NULL)
      return;
    node->output_info();
    output_tree(node->left_);
    output_tree(node->right_);
    return;
  }

  void check_black_nodes() { black_nodes(root_); }

  bool is_valid_tree() {
    if (root_ == NULL)
      return true;
    if (root_->parent_ != header_)
      return false;
    if (is_red(root_))
      return false;
    try {
      check_black_nodes();
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      return false;
    }
    return check_consecutive_red(root_);
  }
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_RBTREE_HPP */
