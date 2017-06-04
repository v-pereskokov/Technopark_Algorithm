#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define methods
#define params

using data_t = int;

template <class T>
class BinaryTree;

template <class T>
struct BinaryTreeNode {
  using keyType = T;
  using keyNode = BinaryTreeNode<keyType>;
  using keyNodePtr = keyNode*;
  
  friend class BinaryTree<keyType>;
  
  public methods:
  BinaryTreeNode(const keyType &key)
  :_key(key) {}
  
  ~BinaryTreeNode() {
    delete _left;
    delete _right;
  }
  
  protected params:
  keyType _key;
  
  private params:
  keyNodePtr _left{nullptr};
  keyNodePtr _right{nullptr};
};

template <class T>
class BinaryTree {
  using keyType = T;
  using keyNode = BinaryTreeNode<keyType>;
  using keyNodePtr = keyNode*;
  using depthSizeType = int;
  
  public methods:
  BinaryTree() = default;
  
  ~BinaryTree() {
    delete _root;
  }
  
  void add(const keyType &key) {
    keyNodePtr appendNode = new keyNode(key);
    if (!_root) {
      _root = appendNode;
      return;
    }
    keyNodePtr current = _root;
    keyNodePtr next = _root;
    while (next) {
      current = next;
      if (key <= current->_key) {
        next = next->_left;
      } else {
        next = next->_right;
      }
    }
    if (key <= current->_key) {
      current->_left = appendNode;
    } else {
      current->_right = appendNode;
    }
  }
  
  depthSizeType maxDepth() {
    return maxDepth(_root);
  }
  
  private methods:
  depthSizeType maxDepth(const keyNodePtr root) {
    if (root) {
      return std::max(maxDepth(root->_left), maxDepth(root->_right)) + 1;
    }
    return 0;
  }
  
  private params:
  keyNodePtr _root{nullptr};
};

template <class T, class P>
class Treap;

template <class T, class P>
class TreapNode {
  using keyType = T;
  using priorityType = P;
  using node = TreapNode<keyType, priorityType>;
  using nodePtr = node*;
  
  friend class Treap<keyType, priorityType>;
  
  public methods:
  TreapNode(const keyType &key, const priorityType &priority)
  :_key(key), _priority(priority) {}
  
  ~TreapNode() {
    delete _left;
    delete _right;
  }
  
  protected params:
  keyType _key;
  priorityType _priority;
  
  private params:
  nodePtr _left{nullptr};
  nodePtr _right{nullptr};
};

template <class T, class P>
class Treap {
  using keyType = T;
  using priorityType = P;
  using node = TreapNode<keyType, priorityType>;
  using nodePtr = node*;
  using depthSizeType = int;
  
  public methods:
  Treap() = default;
  
  ~Treap() {
    delete _root;
  }
  
  void add(const keyType &key, const priorityType &priority) {
    _add(key, priority);
  }
  
  depthSizeType maxDepth() {
    return maxDepth(_root);
  }
  
  private methods:
  void _add(const keyType &key, const priorityType &priority) {
    nodePtr appendNode = new node(key, priority);
    if (!_root) {
      _root = appendNode;
      return;
    }
    nodePtr current = _root;
    nodePtr previously = _root;
    while (current && current->_priority >= priority) {
      previously = current;
      if (key <= current->_key) {
        current = current->_left;
      } else {
        current = current->_right;
      }
    }
    split(current, key, &(appendNode->_left), &(appendNode->_right));
    if (current == _root) {
      _root = appendNode;
    } else {
      if (key <= previously->_key) {
        previously->_left = appendNode;
      } else {
        previously->_right = appendNode;
      }
    }
  }
  
  void split(nodePtr current, const keyType key, nodePtr *left, nodePtr *right) {
    if (current == nullptr) {
      *left = nullptr;
      *right = nullptr;
    } else if (current->_key <= key) {
      split(current->_right, key, &(current->_right), right);
      *left = current;
    }
    else {
      split(current->_left, key, left, &(current->_left));
      *right = current;
    }
  }
  
  depthSizeType maxDepth(const nodePtr root) {
    if (root) {
      return std::max(maxDepth(root->_left), maxDepth(root->_right)) + 1;
    }
    return 0;
  }
  
  private params:
  nodePtr _root{nullptr};
};

int main() {
  BinaryTree<data_t> Binary;
  Treap<data_t, data_t> Treap;
  size_t n;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    data_t key, priority;
    std::cin >> key >> priority;
    Binary.add(key);
    Treap.add(key, priority);
  }
  std::cout << std::abs(Treap.maxDepth() - Binary.maxDepth()) << std::endl;
  return 0;
}
