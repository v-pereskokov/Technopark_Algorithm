#include <cstring>
#include <stack>
#include <utility>

template <class Type>
int findPivot(Type *target, int begin, int end) {
  begin = rand() % (end - begin + 1) + begin;
  int middle = rand() % (end - begin + 1) + begin;
  end = rand() % (end - begin + 1) + begin;
  if (target[middle] < target[begin]) {
    std::swap(middle, begin);
  }
  if (target[end] < target[begin]) {
    std::swap(end, begin);
  }
  if (target[end] < target[middle]) {
    std::swap(end, middle);
  }
  std::swap(target[middle], target[end]);
  return end;
}

template <class Type>
size_t partition(Type *target, int begin, int end) {
  int pivotIndex = findPivot(target, begin, end);
  std::swap(target[begin], target[pivotIndex]);
  int it = begin + 1;
  int jt = end;
  while (true) {
    while (target[it] < target[begin]) {
      ++it;
    }
    while (target[jt] > target[begin]) {
      --jt;
    }
    if (it < jt) {
      std::swap(target[it], target[jt]);
      ++it, --jt;
    } else {
      --it;
      std::swap(target[begin], target[it]);
      return it;
    }
  }
}

template<class Type>
void insertionSort(Type *target, int begin, int end) {
  for (size_t i = begin + 1; i < end; i++) {
    size_t left = 0;
    size_t right = i;
    if (target[i] < target[i - 1]) {
      while (left < right) {
        int middle = left + (right - left) / 2;
        if (target[i] > target[middle]) {
          left = middle + 1;
        }
        else {
          right = middle;
        }
      }
      if (right < i - 1) {
        Type temp = target[i];
        memmove(&target[right + 1], &target[right], (i - right) * sizeof(Type));
        target[right] = temp;
      } else {
        std::swap(target[i], target[i - 1]);
      }
    }
  }
}

template <class Type>
void qsort(Type *target, int begin, int end) {
  std::stack<std::pair<int, int> > stack;
  stack.push(std::make_pair(begin, end));
  while (!stack.empty()) {
    std::pair<int, int> top = stack.top();
    begin = top.first;
    end = top.second;
    stack.pop();
    if (end - begin <= 1050) {
      insertionSort(target + begin, 0, end - begin + 1);
      continue;
    }
    int pivot = partition(target, begin, end);
    if (pivot - 1 > begin) {
      stack.push(std::make_pair(begin, pivot - 1));
    }
    if (pivot + 1 < end) {
      stack.push(std::make_pair(pivot + 1, end));
    }
  }
}

void sort(BlackInt *begin, BlackInt *end) {
  srand(12);
  qsort(begin, 0, end - begin - 1);
}
