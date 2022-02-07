#ifndef FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP
#define FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

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
  _RBtree_color color_;

  _RBnode(K key, V value)
      : key_(key),
        value_(value),
        left_(NULL),
        right_(NULL),
        parent_(NULL),
        color_(e_red) {}

  void outputInfo() {
    std::cout << "------------------------------" << std::endl;
    std::cout << "&this  : " << std::hex << this << std::dec << std::endl;
    std::cout << "key    : " << key_ << std::endl;
    // std::cout << "value  : " << value_ << std::endl;
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

template <typename K, typename V, typename Comp>
class RBtree {
public:
  typedef _RBnode<K, V>                  node_type;
  typedef node_type*                     node_pointer;
  typedef std::allocator<_RBnode<K, V> > node_allocator;
  typedef size_t                         size_type;

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

private:
  node_pointer   header_;
  node_pointer   root_;
  size_t         size_;
  Comp           comp_;
  node_allocator alloc_;

public:
  RBtree() : root_(NULL), size_(0), comp_(Comp()), alloc_(node_allocator()) {
    header_ = new node_type(K(), V());
    setBlack(header_);
  }
  ~RBtree() { destroyTree(header_); }

  void add(K key, V value) {
    node_pointer new_node = alloc_.allocate(1);
    alloc_.construct(new_node, node_type(key, value));
    if (root_ == NULL) {
      root_          = new_node;
      root_->parent_ = header_;
      header_->left_ = root_;
      setBlack(root_);
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

  void checkBlackNodes() { blackNodes(root_); }

  bool isValidTree() {
    if (root_ == NULL)
      return true;
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
template <typename T>
struct RBtree_iterator {
  typedef T  value_type;
  typedef T& reference;
  typedef T* pointer;

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t                  difference_type;

  typedef RBtree_iterator<T> _Self;
  // typedef _RBnode<>*        _Link_type;
};

}  // namespace ft

#endif /* FT_CONTAINERS_INCLUDES_TREE_RBTREE_HPP */
