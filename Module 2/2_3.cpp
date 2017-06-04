#include <cstdio>
#include <assert.h>

struct Train {
  using time_type = int;
  friend void swap(Train &lhs, Train &rhs) {
    Train temp = lhs;
    lhs = rhs;
    rhs = temp;
  }
  
  time_type _arrival;
  time_type _departure;
};

class PriorityQueue {
  using pTrain = Train *;
  using queueSize = size_t;
  using index = int;
  
public:
  PriorityQueue(size_t qSize = 10)
  :_table(new Train[qSize]), _qSize(qSize), _top(-1) {}
  
  ~PriorityQueue() {
    delete[] _table;
  }
  
  void push(Train element) {
    if (_top + 1 >= _qSize) {
      grow();
    }
    _table[++_top] = element;
    heapSiftUp(_top);
  }
  
  Train getMin() const {
    return _table[0];
  }
  
  Train pop() {
    assert(_top >= 0);
    Train result = _table[0];
    _table[0] = _table[_top];
    heapSiftDown(0);
    --_top;
    return result;
  }
  
  bool isEmpty() const {
    return _top < 0;
  }
  
  index getTop() const {
    return _top;
  }
  
private:
  void grow() {
    queueSize newQSize = _qSize << 1;
    Train *temp = new Train[newQSize];
    for (index i = 0; i < _qSize; ++i) {
      temp[i] = _table[i];
    }
    delete[] _table;
    _table = temp;
    _qSize = newQSize;
  }
  
  void heapSiftDown(index i) {
    index left = leftChild(i);
    index right = rightChild(i);
    index largest = i;
    if (left < _top + 1 && _table[left]._departure < _table[i]._departure) {
      largest = left;
    }
    if (right < _top + 1 && _table[right]._departure < _table[largest]._departure) {
      largest = right;
    }
    if (largest != i) {
      swap(_table[i], _table[largest]);
      heapSiftDown(largest);
    }
  }
  
  index leftChild(index i) {
    return (i << 1) + 1;
  }
  
  index rightChild(index i) {
    return (i << 1) + 2;
  }
  
  void heapSiftUp(index i) {
    while (i > 0) {
      index parent_ = parent(i);
      if (_table[i]._departure >= _table[parent_]._departure) {
        return;
      }
      swap(_table[i], _table[parent_] );
      i = parent_;
    }
  }
  
  index parent(index i) {
    return i >> 1;
  }
  
private:
  pTrain _table;
  queueSize _qSize;
  index _top;
};

int main()
{
  size_t n;
  scanf("%ld", &n);
  PriorityQueue queue;
  size_t max = 0;
  for (size_t i = 1; i <= n; ++i) {
    Train train;
    scanf("%d %d", &train._arrival, &train._departure);
    if (!queue.isEmpty()) {
      while (queue.getMin()._departure < train._arrival) {
        queue.pop();
      }
    }
    queue.push(train);
    size_t top = queue.getTop();
    if (top + 1 > max) {
      max = top + 1;
    }
  }
  printf("%ld\n", max);
  return 0;
}
