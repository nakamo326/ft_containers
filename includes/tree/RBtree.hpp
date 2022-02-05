#ifndef FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP
#define FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "Color.hpp"

namespace ft {

enum _RBtree_color { e_red = false, e_black = true };

template <typename K, typename V>
struct _RBnode {
  typedef _RBnode<K, V> node_type;
  typedef node_type*    node_pointer;

  K            key_;
  V            value_;
  node_pointer left_;
  node_pointer right_;
  node_pointer parent_;
  bool         isLeftChild_, isBlack_;

  _RBnode(K key, V value)
      : key_(key),
        value_(value),
        left_(NULL),
        right_(NULL),
        parent_(NULL),
        isLeftChild_(false),
        isBlack_(false) {}

  void outputInfo() {
    std::cout << "------------------------------" << std::endl;
    std::cout << "&this  : " << std::hex << this << std::dec << std::endl;
    std::cout << "key    : " << key_ << std::endl;
    // std::cout << "value  : " << value_ << std::endl;
    std::cout << "parent : " << std::hex << parent_ << std::dec << std::endl;
    std::cout << "left   : " << std::hex << left_ << std::dec << std::endl;
    std::cout << "right  : " << std::hex << right_ << std::dec << std::endl;
    std::cout << "isLeft : " << std::boolalpha << isLeftChild_ << std::endl;
    std::cout << "isBlack: ";
    if (isBlack_)
      std::cout << BLU << std::boolalpha << isBlack_ << NC << std::endl;
    else
      std::cout << RED << std::boolalpha << isBlack_ << NC << std::endl;
  }
};

template <typename K, typename V, typename Comp>
class RBtree {
public:
  typedef _RBnode<K, V>                  node_type;
  typedef node_type*                     node_pointer;
  typedef std::allocator<_RBnode<K, V> > node_allocator;
  typedef size_t                         size_type;

private:
  node_pointer root_;
  size_t       size_;
  Comp         comp_;

private:
  void add(node_pointer parent, node_pointer new_node) {
    std::cout << "call add method. key is " << new_node->key_ << std::endl;
    if (comp_(parent->key_, new_node->key_)) {
      if (parent->right_ == NULL) {
        parent->right_         = new_node;
        new_node->parent_      = parent;
        new_node->isLeftChild_ = false;
        return checkColor(new_node);
      }
      return add(parent->right_, new_node);
    } else {
      if (parent->left_ == NULL) {
        parent->left_          = new_node;
        new_node->parent_      = parent;
        new_node->isLeftChild_ = true;
        return checkColor(new_node);
      }
      return add(parent->left_, new_node);
    }
  }

  void checkColor(node_pointer node) {
    std::cout << "call checkColor method." << std::endl;
    if (node == root_) {
      if (node->isBlack_ == false)
        node->isBlack_ = true;
      return;
    }
    if (!node->isBlack_ && !node->parent_->isBlack_)
      correctTree(node);
    if (node->parent_ != NULL)
      checkColor(node->parent_);
  }

  // isUncleBlack

  bool isBlackOrNull(node_pointer node) {
    return node == NULL || node->isBlack_;
  }

  void flipColor(node_pointer node) {
    std::cout << "call flipColor" << std::endl;
    node->parent_->parent_->isBlack_         = false;
    node->parent_->parent_->left_->isBlack_  = true;
    node->parent_->parent_->right_->isBlack_ = true;
  }

  // precondition: node has parent
  // root is black always
  void correctTree(node_pointer node) {
    std::cout << "call correctTree" << std::endl;
    if (node->parent_->isLeftChild_) {
      if (isBlackOrNull(node->parent_->parent_->right_))
        return rotate(node);
      flipColor(node);
    } else {
      if (isBlackOrNull(node->parent_->parent_->left_))
        return rotate(node);
      flipColor(node);
    }
  }

  // left child left subtree imbalance right rotation
  // right child right subtree imbalance right rotation
  // left, right -> left,right
  // right,left -> right, left

  // FIXME: changing color after rotation is wrong?
  void rotate(node_pointer node) {
    std::cout << "call rotate method." << std::endl;
    if (node->isLeftChild_) {
      if (node->parent_->isLeftChild_) {
        rightRotate(node->parent_->parent_);
        node->parent_->isBlack_ = true;
        node->isBlack_          = false;
        if (node->parent_->right_ != NULL)
          node->parent_->right_->isBlack_ = false;
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
        node->parent_->isBlack_ = true;
        node->isBlack_          = false;
        if (node->parent_->left_ != NULL)
          node->parent_->left_->isBlack_ = false;
        return;
      }
      leftRightRotate(node->parent_->parent_);
      node->isBlack_         = true;
      node->right_->isBlack_ = false;
      node->left_->isBlack_  = false;
      return;
    }
  }

  void leftRotate(node_pointer node) {
    std::cout << "leftRotate" << std::endl;
    node_pointer tmp = node->right_;
    node->right_     = tmp->left_;
    if (node->right_ != NULL) {
      node->right_->parent_      = node;
      node->right_->isLeftChild_ = false;
    }
    if (node->parent_ == NULL) {
      // node is root now and new root is tmp.
      root_        = tmp;
      tmp->parent_ = NULL;
    } else {
      tmp->parent_ = node->parent_;
      if (node->isLeftChild_) {
        tmp->isLeftChild_   = true;
        tmp->parent_->left_ = tmp;
      } else {
        tmp->isLeftChild_    = false;
        tmp->parent_->right_ = tmp;
      }
    }
    tmp->left_         = node;
    node->isLeftChild_ = true;
    node->parent_      = tmp;
  }

  void rightRotate(node_pointer node) {
    std::cout << "rightRotate" << std::endl;
    node_pointer tmp = node->left_;
    node->left_      = tmp->right_;
    if (node->left_ != NULL) {
      node->left_->parent_      = node;
      node->left_->isLeftChild_ = true;
    }
    if (node->parent_ == NULL) {
      // node is root now and new root is tmp.
      root_        = tmp;
      tmp->parent_ = NULL;
    } else {
      tmp->parent_ = node->parent_;
      if (node->isLeftChild_) {
        tmp->isLeftChild_   = true;
        tmp->parent_->left_ = tmp;
      } else {
        tmp->isLeftChild_    = false;
        tmp->parent_->right_ = tmp;
      }
    }
    tmp->right_        = node;
    node->isLeftChild_ = false;
    node->parent_      = tmp;
  }

  void leftRightRotate(node_pointer node) {
    leftRotate(node->left_);
    rightRotate(node);
  }

  void rightLeftRotate(node_pointer node) {
    rightRotate(node->right_);
    leftRotate(node);
  }

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

  size_type blackNodes(node_pointer node) {
    if (node == NULL)
      return 1;
    size_type leftBlackNodes  = blackNodes(node->right_);
    size_type rightBlackNodes = blackNodes(node->left_);
    if (leftBlackNodes != rightBlackNodes) {
      throw std::logic_error("this tree is imbalance");
    }
    if (node->isBlack_)
      leftBlackNodes++;
    return leftBlackNodes;
  }

  bool checkConsecutiveRed(node_pointer node) {
    if (node == NULL)
      return true;
    if (!node->isBlack_) {
      if (node->left_ != NULL && !node->left_->isBlack_)
        return false;
      if (node->right_ != NULL && !node->right_->isBlack_)
        return false;
    }
    return checkConsecutiveRed(node->left_) &&
           checkConsecutiveRed(node->right_);
  }

  void deleteAllNodes(node_pointer node) {
    if (node == NULL)
      return;
    deleteAllNodes(node->left_);
    deleteAllNodes(node->right_);
    delete node;
  }

public:
  RBtree() : root_(NULL), size_(0), comp_(Comp()) {}
  ~RBtree() { deleteAllNodes(root_); }

  void add(K key, V value) {
    // FIXME: use allocator
    node_pointer new_node = new node_type(key, value);
    if (root_ == NULL) {
      root_           = new_node;
      root_->isBlack_ = true;
      size_++;
      return;
    }
    add(root_, new_node);
    size_++;
  }

  void outputAllTree() { outputTree(root_); }

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
    if (!root_->isBlack_)
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
