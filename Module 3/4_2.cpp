#include <iostream>
#include <queue>

#define methods
#define params

template <class T>
class AVL_Tree;

template <class T>
class Node {
  using key_type = T;
  using height_type = int;
  using node_ptr = Node*;
  
  friend class AVL_Tree<key_type>;
  
  public methods:
  Node(const key_type &key)
  :_key(key) {}
  
  ~Node() {
    delete _left;
    delete _right;
  }
  
  protected params:
  key_type _key;
  height_type _height{1};
  node_ptr _left{nullptr};
  node_ptr _right{nullptr};
};

template <class T>
class AVL_Tree {
  using key_type = T;
  using height_type = int;
  using node_ptr = Node<key_type>*;
  using index_type = int;
  
  public methods:
  AVL_Tree() = default;
  
  ~AVL_Tree() {
    delete _root;
  }
  
  constexpr height_type get_height() const {
    return get_height(_root);
  }
  
  void add(const key_type &key) {
    add(_root, key);
  }
  
  void remove(const key_type &key) {
    remove(_root, key);
  }
  
  void traversLevelOrder() {
    traversLevelOrder(_root);
  }
  
  key_type kth_element(const index_type index) {
    return kth_element(_root, index);
  }
  
  private methods:
  constexpr height_type get_height(const node_ptr node) const {
    return node ? node->_height : 0;
  }
  
  constexpr height_type height_different(const node_ptr node) const {
    return get_height(node->_right) - get_height(node->_left);
  }
  
  void correct_height(node_ptr &node) {
    height_type left_height = get_height(node->_left);
    height_type right_height = get_height(node->_right);
    node->_height = (left_height > right_height ? left_height : right_height) + 1;
  }
  
  node_ptr right_rotate(node_ptr &node) {
    node_ptr left = node->_left;
    node->_left = left->_right;
    left->_right = node;
    correct_height(node);
    correct_height(left);
    node = left;
    return node;
  }
  
  node_ptr left_rotate(node_ptr &node) {
    node_ptr right = node->_right;
    node->_right = right->_left;
    right->_left = node;
    correct_height(node);
    correct_height(right);
    node = right;
    return node;
  }
  
  node_ptr big_right_rotate(node_ptr &node) {
    node->_right = right_rotate(node->_right);
    return left_rotate(node);
  }
  
  node_ptr big_left_rotate(node_ptr &node) {
    node->_left = left_rotate(node->_left);
    return right_rotate(node);
  }
  
  node_ptr balance(node_ptr &node) {
    correct_height(node);
    if (height_different(node) == 2) {
      if (height_different(node->_right) < 0) {
        return big_right_rotate(node);
      }
      return left_rotate(node);
    }
    if (height_different(node) == -2) {
      if (height_different(node->_left) > 0) {
        return big_left_rotate(node);
      }
      return right_rotate(node);
    }
    return node;
  }
  
  node_ptr add(node_ptr &node, const key_type key) {
    if (!node) {
      node = new Node<key_type>(key);
      return node;
    }
    if (key < node->_key) {
      node->_left = add(node->_left, key);
    } else {
      node->_right = add(node->_right, key);
    }
    node = balance(node);
    return node;
  }
  
  node_ptr find_min(const node_ptr node) {
    return node->_left ? find_min(node->_left) : node;
  }
  
  node_ptr remove_min(node_ptr &node) {
    if (node->_left == nullptr) {
      return node->_right;
    }
    node->_left = remove_min(node->_left);
    node = balance(node);
    return node;
  }
  
  node_ptr remove(node_ptr &node, const key_type key) {
    if (!node) {
      return nullptr;
    }
    if (key < node->_key) {
      node->_left = remove(node->_left, key);
    } else if (key > node->_key) {
      node->_right = remove(node->_right, key);
    } else {
      node_ptr left = node->_left;
      node_ptr right = node->_right;
      node = nullptr;
      if (!right) {
        node = left;
        return node;
      }
      node_ptr min = find_min(right);
      min->_right = remove_min(right);
      min->_left = left;
      node = balance(min);
      return node;
    }
    node = balance(node);
    return node;
  }
  
  void visit(const node_ptr node) {
    std::cout << node->_key << " ";
  }
  
  size_t traversLevelOrder(const node_ptr node, const bool is_visit = false) {
    if (!node) {
      return 0;
    }
    std::queue<node_ptr> queue;
    size_t count = 0;
    for (queue.push(node); !queue.empty(); queue.pop()) {
      node_ptr tmp = queue.front();
      if (is_visit) {
        visit(tmp);
      }
      ++count;
      if (tmp->_left) {
        queue.push(tmp->_left);
      }
      if (tmp->_right) {
        queue.push(tmp->_right);
      }
    }
    return count;
  }
  
  key_type kth_element(node_ptr node, index_type index) {
    while (node) {
      height_type left_height = traversLevelOrder(node->_left);
      if (left_height == index) {
        return node->_key;
      }
      node = left_height > index ? node->_left : node->_right;
      if (left_height < index) {
        index -= left_height + 1;
      }
    }
    return -1;
  }
  
  private params:
  node_ptr _root{nullptr};
};

int main() {
  AVL_Tree<int> tree;
  int n;
  std::cin >> n;
  for (size_t i = 1; i <= n; ++i) {
    int added;
    int index;
    std::cin >> added >> index;
    if (added >= 0) {
      tree.add(added);
    } else {
      added = -added;
      tree.remove(added);
    }
    std::cout << tree.kth_element(index) << std::endl;
  }
//  tree.traversLevelOrder();
  return 0;
}
