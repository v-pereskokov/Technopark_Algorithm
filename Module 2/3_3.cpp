#include <cstdio>
#include <vector>
#include <algorithm>
#include <assert.h>

struct Point {
  using coordinate = int;
  using location = bool;
  
  Point(const coordinate x = 0, const location begin = false)
  :_x(x), _begin(begin) {}
  
  friend void swap(Point &lhs, Point &rhs) {
    Point temp = lhs;
    lhs = rhs;
    rhs = temp;
  }
  
  coordinate _x;
  location _begin;
};

using Points = std::vector<Point>;
using paintedSize = size_t;
using isColor = bool;

bool less(const Point &lhs, const Point &rhs) {
  return lhs._x < rhs._x;
}

size_t leftChild(size_t i) {
  return (i << 1) + 1;
}

size_t rightChild(size_t i) {
  return (i << 1) + 2;
}

template <class IT, class comparator>
void heapSiftDown(IT begin, size_t size, size_t head, comparator &less) {
  while ((head << 1) + 1 < size) {
    size_t child = 2 * head + 1;
    if (child + 1 < size && less(*(begin + child), *(begin + child + 1))) {
      ++child;
    }
    if (!less(*(begin + head), *(begin + child))) {
      return;
    }
    std::swap(*(begin + head), *(begin + child));
    head = child;
  }
}

template <class IT, class comparator>
void heapMake(IT begin, size_t size, comparator &less) {
  for (size_t child = size - 1; ; child -= 2) {
    heapSiftDown(begin, size, (child - 1) >> 1, less);
    if (child <= 2) {
      break;
    }
  }
}

template <class IT, class comparator>
void heapSort(IT begin, IT end, comparator &less) {
  size_t size = std::distance(begin, end);
  heapMake(begin, size, less);
  while (size > 1) {
    --size;
    std::swap(*begin, *(begin + size));
    heapSiftDown(begin, size, 0, less);
  }
}

paintedSize countPaint(const Points &points) {
  paintedSize paintSize = 0;
  size_t isColor = 0;
  Point begin;
  for (auto it = points.begin(); it != points.end(); ++it) {
    if (it->_begin) {
      if (isColor == 0) {
        begin = *it;
      }
      ++isColor;
    } else {
      --isColor;
    }
    if (isColor == 0) {
      paintSize += (it->_x - begin._x);
    }
  }
  return paintSize;
}

int main() {
  size_t n;
  scanf("%ld", &n);
  Points points;
  for (size_t i = 1; i <= n; ++i) {
    Point begin;
    Point end;
    scanf("%d %d", &begin._x, &end._x);
    if (begin._x < end._x) {
      begin._begin = true;
    } else {
      end._begin = true;
    }
    points.push_back(begin);
    points.push_back(end);
  }
  heapSort(points.begin(), points.end(), less);
  printf("%ld\n", countPaint(points));
  return 0;
}
