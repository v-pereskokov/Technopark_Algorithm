#include <iostream>
#include <string>
#include <vector>

template <class Type = std::string>
class HashTable {
#define methods
#define params
#define enums
  
  using data_t = std::string;
  
  struct HashTableNode {
    using flag = bool;
    
    HashTableNode(const data_t &data)
    :_data(data), _isDeleted(false) {}
    
    std::string _data;
    flag _isDeleted;
  };
  
  using hash = int;
  using mapSize = size_t;
  using node = HashTableNode;
  using myMap = std::vector<node *>;
  
  const double REHASH = 0.75;
  
  public methods:
  HashTable(const mapSize capacity = 8)
  :_capacity(capacity), _size(0), _map(_capacity, nullptr) {}
  
  ~HashTable() = default;
  
  bool add(const data_t &data) {
    if (static_cast<double>(_size) / static_cast<double>(_capacity) >= REHASH) {
      rehash();
    }
    hash hash1 = hash_a(data, _capacity);
    hash hash2 = hash_b(data, _capacity);
    size_t i = 0;
    int deletedNodeIndex = -1;
    while (_map[hash1] != nullptr && i < _capacity) {
      if (_map[hash1]->_data == data && !_map[hash1]->_isDeleted) {
        return false;
      }
      if (_map[hash1]->_isDeleted && deletedNodeIndex < 0) {
        deletedNodeIndex = hash1;
      }
      hash1 = (hash1 + hash2) % _capacity;
      ++i;
    }
    if (deletedNodeIndex >= 0) {
      _map[deletedNodeIndex]->_data = data;
      _map[deletedNodeIndex]->_isDeleted = false;
    } else {
      _map[hash1] = new node(data);
    }
    ++_size;
    return true;
  }
  
  bool remove(const data_t &data) {
    hash hash1 = hash_a(data, _capacity);
    hash hash2 = hash_b(data, _capacity);
    size_t i = 0;
    while (_map[hash1] != nullptr && i < _capacity) {
      if (_map[hash1]->_data == data && !_map[hash1]->_isDeleted) {
        _map[hash1]->_isDeleted = true;
        --_size;
        return true;
      }
      hash1 = (hash1 + hash2) % _capacity;
      ++i;
    }
    return false;
  }
  
  bool has(const data_t &data) {
    hash hash1 = hash_a(data, _capacity);
    hash hash2 = hash_b(data, _capacity);
    size_t i = 0;
    while (_map[hash1] != NULL && i < _capacity) {
      if (_map[hash1]->_data == data && !_map[hash1]->_isDeleted) {
        return true;
      }
      hash1 = (hash1 + hash2) % _capacity;
      ++i;
    }
    return false;
  }
  
  private methods:
  int hash_a(const data_t &data, const int m) {
    int result = 0;
    for (size_t i = 0; i < data.size(); ++i) {
      result = (result * static_cast<hash>(HashConstants::HASH_1) + data[i]) % m;
    }
    return result;
  }
  
  int hash_b(const data_t &data, const int m) {
    int result = 0;
    for (size_t i = 0; i < data.length(); ++i) {
      result = (result * static_cast<hash>(HashConstants::HASH_2) + data[i]) % m;
    }
    return ((result << 1) + 1) % m;
  }
  
  void rehash() {
    mapSize newSize = _capacity << 1;
    myMap newMap(newSize, nullptr);
    for (size_t i = 0; i < _capacity; ++i) {
      if (_map[i] != nullptr && !_map[i]->_isDeleted) {
        data_t data = _map[i]->_data;
        hash currentHash = hash_a(data, newSize);
        hash otherHash = hash_b(data, newSize);
        size_t j = 0;
        while (newMap[currentHash] != nullptr && j < newSize) {
          currentHash = (currentHash + otherHash) % newSize;
          ++j;
        }
        newMap[currentHash] = new node(data);
      }
    }
    _map = newMap;
    _capacity = newSize;
  }
  
  private params:
  mapSize _capacity;
  mapSize _size;
  myMap _map;
  
  private enums:
  enum class HashConstants {
    HASH_1 = 47,
    HASH_2 = 73,
  };
};

using Table = HashTable<>;

int main() {
  char c;
  std::string str;
  Table table;
  while (std::cin >> c >> str) {
    bool result;
    switch (c) {
      case '+':
        result = table.add(str);
        break;
      case '-':
        result = table.remove(str);
        break;
      case '?':
        result = table.has(str);
        break;
      default:
        result = false;
    }
    std::cout << ((result) ? "OK" : "FAIL") << "\n";
  }
  return 0;
}
