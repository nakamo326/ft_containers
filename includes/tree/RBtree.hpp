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

  K             key_;
  V             value_;
  node_pointer  left_;
  node_pointer  right_;
  node_pointer  parent_;
  bool          isLeftChild_;
  _RBtree_color color_;

  _RBnode(K key, V value)
      : key_(key),
        value_(value),
        left_(NULL),
        right_(NULL),
        parent_(NULL),
        isLeftChild_(false),
        color_(e_red) {}

  void outputInfo() {
    std::cout << "------------------------------" << std::endl;
    std::cout << "&this  : " << std::hex << this << std::dec << std::endl;
    std::cout << "key    : " << key_ << std::endl;
    // std::cout << "value  : " << value_ << std::endl;
    std::cout << "parent : " << std::hex << parent_ << std::dec << std::endl;
    std::cout << "left   : " << std::hex << left_ << std::dec << std::endl;
    std::cout << "right  : " << std::hex << right_ << std::dec << std::endl;
    std::cout << "isLeft : " << std::boolalpha << isLeftChild_ << std::endl;
    std::cout << "color  : ";
    if (color_)
      std::cout << BLU << "black" << NC << std::endl;
    else
      std::cout << RED << "red" << NC << std::endl;
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

  // == add ==
  // after adding node, we need to fix tree if there're imbalance
  void add(node_pointer parent, node_pointer new_node) {
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
    if (node == root_) {
      if (isRed(node))
        setBlack(node);
      return;
    }
    if (isRed(node) && isRed(node->parent_))
      correctTree(node);
    if (node->parent_ != NULL)
      checkColor(node->parent_);
  }

  // black uncle rotate, red uncle color flip
  void correctTree(node_pointer node) {
    if (isUncleNodeBlack(node))
      return rotate(node);
    flipColor(node);
  }

  bool isUncleNodeBlack(node_pointer node) {
    if (node->parent_->isLeftChild_)
      return isBlack(node->parent_->parent_->right_);
    return isBlack(node->parent_->parent_->left_);
  }

  void flipColor(node_pointer node) {
    setRed(node->parent_->parent_);
    setBlack(node->parent_->parent_->left_);
    setBlack(node->parent_->parent_->right_);
  }

  // == rotate ==
  void rotate(node_pointer node) {
    node_pointer new_parent;
    if (node->isLeftChild_) {
      if (node->parent_->isLeftChild_)
        new_parent = rightRotate(node->parent_->parent_);
      else
        new_parent = rightLeftRotate(node->parent_->parent_);
    } else {
      if (!node->parent_->isLeftChild_)
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

  node_pointer leftRotate(node_pointer node) {
    node_pointer tmp = node->right_;
    node->right_     = tmp->left_;
    if (node->right_ != NULL) {
      node->right_->parent_      = node;
      node->right_->isLeftChild_ = false;
    }
    if (node->parent_ == NULL) {
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
    return tmp;
  }

  node_pointer rightRotate(node_pointer node) {
    node_pointer tmp = node->left_;
    node->left_      = tmp->right_;
    if (node->left_ != NULL) {
      node->left_->parent_      = node;
      node->left_->isLeftChild_ = true;
    }
    if (node->parent_ == NULL) {
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
    return tmp;
  }

  node_pointer leftRightRotate(node_pointer node) {
    leftRotate(node->left_);
    return rightRotate(node);
  }

  node_pointer rightLeftRotate(node_pointer node) {
    rightRotate(node->right_);
    return leftRotate(node);
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

  // FIXME: use allocator
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
      root_ = new_node;
      setBlack(root_);
      size_++;
      return;
    }
    add(root_, new_node);
    size_++;
  }

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

  void checkBlackNodes() { blackNodes(root_); }

  bool isValidTree() {
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
