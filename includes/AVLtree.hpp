#ifndef FT_CONTAINERS_INCLUDES_AVLTREE_HPP
#define FT_CONTAINERS_INCLUDES_AVLTREE_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace ft {

template <typename K, typename V>
struct _node {
  typedef _node<K, V> node_type;
  typedef node_type*  node_pointer;

  K            key_;
  V            value_;
  node_pointer left_;
  node_pointer right_;
  node_pointer parent_;

  _node(K key, V value)
      : key_(key), value_(value), left_(NULL), right_(NULL), parent_(NULL) {}

  void outputInfo() {
    std::cout << "------------------------------" << std::endl;
    std::cout << "&this  : " << std::hex << this << std::dec << std::endl;
    std::cout << "key    : " << key_ << std::endl;
    std::cout << "parent : " << std::hex << parent_ << std::dec << std::endl;
    std::cout << "left   : " << std::hex << left_ << std::dec << std::endl;
    std::cout << "right  : " << std::hex << right_ << std::dec << std::endl;
  }
};

template <typename K, typename V, typename Comp>
class AVLtree {
public:
  typedef _node<K, V>                  node_type;
  typedef node_type*                   node_pointer;
  typedef std::allocator<_node<K, V> > node_allocator;
  typedef size_t                       size_type;

private:
  bool isLeftChild(node_pointer node) { return node->parent_->left_ == node; }

  // == helpers ==
  node_pointer searchKey(K key, node_pointer node) {
    while (node != NULL) {
      if (node->key_ == key)
        break;
      node = comp_(node->key_, key) ? node->right_ : node->left_;
    }
    return node;
  }

  node_pointer searchMinimum(node_pointer node) {
    while (node->left_ != NULL) {
      node = node->left_;
    }
    return node;
  }

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

  void copyVal(node_pointer from, node_pointer to) {
    to->key_   = from->key_;
    to->value_ = from->value_;
  }

  // == add ==
  void add(node_pointer parent, node_pointer new_node) {
    if (comp_(parent->key_, new_node->key_)) {
      if (parent->right_ == NULL) {
        parent->right_    = new_node;
        new_node->parent_ = parent;
        return checkColor(new_node);
      }
      return add(parent->right_, new_node);
    } else {
      if (parent->left_ == NULL) {
        parent->left_     = new_node;
        new_node->parent_ = parent;
        return checkColor(new_node);
      }
      return add(parent->left_, new_node);
    }
  }

  // need check something

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
    return;
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
  bool deleteNode(K key) {
    node_pointer target = searchKey(key, root_);
    if (target == NULL)
      return false;

    _RBtree_color deleted_color = target->color_;
    node_pointer  x, x_parent = target->parent_;
    if (target->left_ == NULL) {
      x = target->right_;
      transplantNodes(target, target->right_);
    } else if (target->right_ == NULL) {
      x = target->left_;
      transplantNodes(target, target->left_);
    } else {
      node_pointer min = searchMinimum(target->right_);
      x                = min->right_;
      x_parent         = min->parent_;

      copyVal(min, target);
      if (min->right_ != NULL) {
        transplantNodes(min, min->right_);
      } else {
        if (isLeftChild(min))
          min->parent_->left_ = NULL;
        else
          min->parent_->right_ = NULL;
      }
      target        = min;
      deleted_color = target->color_;
    }
    deallocateNode(target);
    if (deleted_color == e_black)
      fixDeletion(x, x_parent);
    return true;
  }

  // == height ==
  size_type height(node_pointer node) {
    if (node == NULL)
      return 0;
    size_type leftHeight  = height(node->left_) + 1;
    size_type rightHeight = height(node->right_) + 1;
    return std::max(leftHeight, rightHeight);
  }

  size_type height() {
    if (root_ == NULL)
      return 0;
    return height(root_) - 1;
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

private:
  node_pointer   header_;
  node_pointer   root_;
  size_t         size_;
  Comp           comp_;
  node_allocator alloc_;

public:
  RBtree() : root_(NULL), size_(0), comp_(Comp()), alloc_(node_allocator()) {
    header_ = new node_type(K(), V());
  }
  ~RBtree() { destroyTree(header_); }

  void add(K key, V value) {
    node_pointer new_node = alloc_.allocate(1);
    alloc_.construct(new_node, node_type(key, value));
    if (root_ == NULL) {
      root_          = new_node;
      root_->parent_ = header_;
      header_->left_ = root_;
      size_++;
      return;
    }
    add(root_, new_node);
    size_++;
  }

  bool erase(K key) { return deleteNode(key); }

  // == for debug ==
  void outputAllTree() { outputTree(root_); }

  void outputTree(node_pointer node) {
    if (node == NULL)
      return;
    node->outputInfo();
    outputTree(node->left_);
    outputTree(node->right_);
    return;
  }

  bool isValidTree() {
    if (root_ == NULL)
      return true;
    if (root_->parent_ != header_)
      return false;
    if (isRed(root_))
      return false;
    try {
      // check balance
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      return false;
    }
    return checkConsecutiveRed(root_);
  }
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_AVLTREE_HPP */
