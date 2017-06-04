#include <cstdio>
#include <queue>

using data_t = int;

template <class T>
struct BinaryTreeNode {
  using Node_ptr = BinaryTreeNode<T>*;
  
  BinaryTreeNode(const T &data)
  :_data(data), _left(nullptr), _right(nullptr) {}
  
  ~BinaryTreeNode() {
    delete _left;
    delete _right;
  }
  
  T _data;
  Node_ptr _left;
  Node_ptr _right;
};

template <class T>
class BinaryTree {
#define methods
#define params
  
  using node_ptr = BinaryTreeNode<T>*;
  
  public methods:
  BinaryTree()
  :_root(nullptr) {}
  
  ~BinaryTree() {
    delete _root;
  }
  
  void add(const T &data) {
    node_ptr node = new BinaryTreeNode<T>(data);
    if (_root == nullptr) {
      _root = node;
      return;
    }
    node_ptr nextNode = _root;
    while (true) {
      if (data < nextNode->_data) {
        if (nextNode->_left != nullptr) {
          nextNode = nextNode->_left;
        } else {
          nextNode->_left = node;
          return;
        }
      } else {
        if (nextNode->_right != nullptr) {
          nextNode = nextNode->_right;
        } else {
          nextNode->_right = node;
          return;
        }
      }
    }
  }
  
  void traversLevelOrder() {
    traversLevelOrder(_root);
  }
  
  private methods:
  void visitInt(node_ptr node) {
    printf("%d ", node->_data);
  }
  
  void traversLevelOrder(node_ptr node) {
    std::queue<node_ptr> queue;
    if (!_root) {
      return;
    }
    for (queue.push(_root); !queue.empty(); queue.pop()) {
      node_ptr tmp = queue.front();
      visitInt(tmp);
      if (tmp->_left) {
        queue.push(tmp->_left);
      }
      if (tmp->_right) {
        queue.push(tmp->_right);
      }
    }
  }
  
  private params:
  node_ptr _root;
};

int main() {
  int n;
  scanf("%d", &n);
  if (n != 0) {
    BinaryTree<int> tree;
    for (size_t i = 0; i < n; ++i) {
      data_t value;
      scanf("%d", &value);
      tree.add(value);
    }
    tree.traversLevelOrder();
  }
  return 0;
}
