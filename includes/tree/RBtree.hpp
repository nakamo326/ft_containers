#ifndef FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP
#define FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP

#include <cstddef>
#include <memory>

namespace ft {

enum _RBtree_color { e_red = false, e_black = true };

template <typename K, typename V>
class _RBnode {
public:
  typedef _RBnode<K, V> node_type;
  typedef node_type*    link_type;

private:
  K          key_;
  V          value_;
  link_type *left_, *right_, *parent_;
  bool       isLeftChild_, isBlack_;

public:
  _RBnode(K key, V value)
      : key_(key),
        value_(value),
        left_(NULL),
        right_(NULL),
        parent_(NULL),
        isLeftChild_(false),
        isBlack_(false) {}
};

template <typename K, typename V, typename Comp>
class RBtree {
public:
  typedef _RBnode<K, V>                 node_type;
  typedef node_type*                    node_pointer;
  typedef std::allocator<_RBnode<K, V>> node_allocator;

private:
  node_pointer root_;
  size_t       size_;
  Comp         comp_;

private:
  void add(node_pointer parent, node_pointer new_node) {
    if (comp_(parent->key_, new_node->key_)) {  // parent < new_node -> right
      if (parent->right_ == NULL) {
        parent->right_         = new_node;
        new_node->parent_      = parent;
        new_node->isLeftChild_ = false;
        return /* check_color */;
      }
      return add(parent->right_, new_node);
    } else {  // parent >= new_node -> left
      if (parent->left_ == NULL) {
        parent->left_          = new_node;
        new_node->parent_      = parent;
        new_node->isLeftChild_ = true;
        return /* check_color */;
      }
      return add(parent->left_, new_node);
    }
  }

  void checkColor(node_pointer node) {
    if (node == root_)
      return;
    if (!node->isBlack_ && node->parent_->isBlack_)
      correctTree(node);
    checkColor(node->parent_);
  }

  // red aunt color flip, black aunt rotate.

  void correctTree(node_pointer node) {
    // aunt is node.parent.parent.right
    if (node->parent_->isLeftChild_) {
      if (node->parent_->parent_->right_ == NULL ||
          node->parent_->parent_->right_->isBlack_)
        return rotate(node);
      if (node->parent_->parent_->right_ != NULL)
        node->parent_->parent_->right_->isBlack_ = true;
      node->parent_->parent_->isBlack_ = false;
      node->parent_->isBlack_          = true;
      return;
    }
    // aunt is grandpa.left
    if (node->parent_->parent_->left_ == NULL ||
        node->parent_->parent_->left_.isBlack_)
      return rotate(node);
    if (node->parent_->parent_->left_ != NULL)
      node->parent_->parent_->left_->isBlack_ = true;
    node->parent_->parent_->isBlack_ = false;
    node->parent_->isBlack_          = true;
    return;
  }

  // left child left subtree imbalance right rotation
  // right child right subtree imbalance right rotation
  // left, right -> left,right right,left -> right, left

  void rotate(node_pointer node) {
    if (node->isLeftChild_) {
      if (node->parent_->isLeftChild_) {
        rightRotate(node->parent_->parent_);
        node->isBlack_          = false;
        node->parent_->isBlack_ = true;
        if (node->parent_->right_ != NULL)
          node->parent_->right_ = false;
        return;
      }
      rightLeftRotate(node->parent_->parent_);
      node->isBlack_         = true;
      node->right_->isBlack_ = false;
      node->left_->isBlack_  = false;
      return;
    } else {
      if (!node->parent_->isLeftChild_) {
        leftRotate(node->parent_->parent_);
        node->isBlack_          = false;
        node->parent_->isBlack_ = true;
        if (node->parent_->right_ != NULL)
          node->parent_->right_ = false;
        return;
      }
      leftRightRotate(node->parent_->parent_);
      node->isBlack_         = true;
      node->right_->isBlack_ = false;
      node->left_->isBlack_  = false;
      return;
    }
  }

public:
  RBtree() : root_(NULL), size_(0), comp_(Comp()) {}

  void add(K key, V value) {
    node_pointer new_node = new node_type(key, value);  // FIXME: use allocator
    if (root_ == NULL) {
      root_           = new_node;
      root_->isBlack_ = true;
      size_++;
      return;
    }
    add(root_, new_node);
    size_++;
  }
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP */
