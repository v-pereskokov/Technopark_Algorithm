#include <iostream>
#include <cassert>
#include <string>

#define methods
#define parametres

template <class T>
class Stack {
public methods:
  explicit Stack(const int size)
  :_size(size), _top(-1) {
    _buffer = new T[_size];
  }
  
  ~Stack() {
    delete [] _buffer;
  }
  
  void push(const T value) {
    assert(_top + 1 < _size);
    _buffer[++_top] = value;
  }
  
  void pop() {
    assert(_top != -1);
    _buffer[_top--];
  }
  
  T top() const {
    assert(_top != -1);
    return _buffer[_top];
  }
  
  bool isEmpty() const {
    return _top == -1;
  }
  
  int size() const {
    return _top;
  }
  
private parametres:
  T *_buffer;
  int _size;
  int _top;
};

bool isBracket(const char bracket) {
  switch (bracket) {
    case '{':
    case '}':
    case '[':
    case ']':
    case '(':
    case ')':
      return true;
    default:
      return false;
  }
}

bool isClosed(const char lhs, const char rhs) {
  std::string cmp = "";
  cmp += lhs; cmp += rhs;
  return cmp == "()" || cmp == "[]" || cmp == "{}";
}

bool isOpen(const char bracket) {
  return bracket == '(' || bracket == '[' || bracket == '{';
}

bool otherSide_(const char lhs, const char rhs) {
  
  return !isOpen(lhs) && isOpen(rhs);
}

bool oneSide(const char lhs, const char rhs) {
  if (isOpen(lhs) && isOpen(rhs)) {
    return true;
  } else if (!isOpen(lhs) && !isOpen(rhs)) {
    return true;
  }
  return false;
}

char inverseBracket(const char bracket) {
  switch (bracket) {
    case '(':
      return ')';
    case ')':
      return '(';
    case '[':
      return ']';
    case ']':
      return '[';
    case '{':
      return '}';
    case '}':
      return '{';
    default:
      return ' ';
  }
}

std::string bracket(std::string *target) {
  Stack<char> brackets(target->size());
  for (std::size_t i = 0; i < target->size(); ++i) {
    char bracket = (*target)[i];
    if (isBracket(bracket)) {
      if (brackets.size() > -1) {
        char topBracket = brackets.top();
        if (isClosed(topBracket, bracket)) {
          brackets.pop();
        } else if (oneSide(topBracket, bracket) || otherSide_(topBracket, bracket)) {
          brackets.push(bracket);
        } else {
          return "IMPOSSIBLE";
        }
      } else {
        brackets.push(bracket);
      }
    } else {
      return "IMPOSSIBLE";
    }
  }
  std::string before = "";
  while (brackets.size() > -1) {
    char bracket = brackets.top();
    if (isOpen(bracket)) {
      *target += inverseBracket(bracket);
    } else {
      before += inverseBracket(bracket);
    }
    brackets.pop();
  }
  before += *target;
  return before;
}

int main() {
  std::string target;
  std::string result = "";
  int i = 0;
  while (std::cin >> target) {
    result += target;
  }
  if (result.size() > 0) {
    result = bracket(&result);
    std::cout << result << std::endl;
  } else {
    std::cout << "IMPOSSIBLE" << std::endl;
  }
  return 0;
}
