void compress_string(const std::string &source, std::string &compressed) {
  compressed = source;
}
void decompress_string(const std::string &compressed, std::string &result)
{
  result = compressed;
}

#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <sstream>
#include <istream>

#define methods
#define params

template <class T>
class Tree_Node {
  using count = size_t;
  using byte = char;
  using node_ptr = Tree_Node*;
  
  public methods:
  Tree_Node(const node_ptr left, const node_ptr right)
  :_left(left), _right(right), _byte('\0') {
    _count = _left->_count + _right->_count;
  }
  
  Tree_Node(const count count, const byte byte)
  :_count(count), _byte(byte) {}
  
  ~Tree_Node {
    delete _left;
    delete _right;
  }
  
  friend constexpr bool operator<(const node_ptr &lhs, const node_ptr &rhs) const {
    return lhs->_count == rhs->_count ? lhs->_byte < rhs->_byte : lhs->_count < rhs->_count;
  }
  
  static constexpr bool cmp(const node_ptr lhs, const node_ptr rhs) const {
    return *lhs < *rhs;
  }
  
  private params:
  node_ptr _left{nullptr};
  node_ptr _right{nullptr};
  count _count;
  byte _byte{'\0'};
};

class Haffman {
  using byte_map_t = std::unordered_map<Tree_Node::byte, Tree_Node::count>;
  using code_t = std::vector<bool>;
  using code_map_t = std::unordered_map<Tree_Node::byte, code_t>;
  
  
  private params:
  
};
