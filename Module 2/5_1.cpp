#include <vector>
#include <stdint.h>
#include <cstdio>

using bigInt = int64_t;
using data = int;
using container = std::vector<data>;

bool less (const data lhs, const data rhs) {
  return lhs < rhs;
}

template <class IT>
void copy(IT begin, IT end, IT copy_begin) {
  while (begin != end) {
    *copy_begin = *begin;
    ++begin;
    ++copy_begin;
  }
}

template <class Comparator>
void merge(container &result, int left, int mid, int right, const Comparator &cmp) {
  container buffer(right - left + 1);
  size_t itLhs = left;
  size_t itRhs = mid + 1;
  size_t itBuffer = 0;
  while (itLhs <= mid && itRhs <= right) {
    if (result[itLhs] <= result[itRhs]) {
      buffer[itBuffer] = result[itLhs];
      ++itLhs;
    }
    else {
      buffer[itBuffer] = result[itRhs];
      ++itRhs;
    }
    ++itBuffer;
  }
  while (itLhs <= mid) {
    buffer[itBuffer] = result[itLhs];
    ++itBuffer;
    ++itLhs;
  }
  while (itRhs <= right) {
    buffer[itBuffer] = result[itRhs];
    ++itBuffer;
    ++itRhs;
  }
  copy(buffer.begin(), buffer.end(), result.begin() + left);
}

template <class Comparator>
void mergeSort(container &result, int left, int right, const Comparator &cmp) {
  if (left == right) {
    return;
  }
  size_t mid = left + (right - left) / 2;
  mergeSort(result, left, mid, cmp);
  mergeSort(result, mid + 1, right, cmp);
  merge(result, left, mid, right, cmp);
}

template <class Comparator>
void kthElementMerge(container &lhs, container &rhs, bigInt k, size_t i, const Comparator &cmp) {
  container buffer(k);
  size_t itLhs = 0;
  size_t itRhs = 0;
  size_t itBuffer = 0;
  while (itLhs < k && itRhs < i && itBuffer < k) {
    if (cmp(rhs[itRhs], lhs[itLhs])) {
      buffer[itBuffer] = rhs[itRhs];
      ++itRhs;
    }
    else {
      buffer[itBuffer] = lhs[itLhs];
      ++itLhs;
    }
    ++itBuffer;
  }
  while (itLhs < k && itBuffer < k) {
    buffer[itBuffer] = lhs[itLhs];
    ++itBuffer;
    ++itLhs;
  }
  std::copy(buffer.begin(), buffer.end(), lhs.begin());
}

int main() {
  bigInt n ;
  bigInt k;
  scanf ("%lld %lld", &n, &k);
  container result(k);
  container buffer(k);
  for (size_t i = 0; i < k; ++i) {
    scanf("%d", &result[i]);
  }
  mergeSort(result, 0, k - 1, less);
  bigInt j = k;
  while (j < n) {
    size_t i = 0;
    for (i = 0; i < k && j < n; ++i, ++j) {
      scanf("%d", &buffer[i]);
    }
    mergeSort(buffer, 0, i - 1, less);
    kthElementMerge(result, buffer, k, i, less);
  }
  for (auto i : result) {
    printf("%d ", i);
  }
  printf("\n");
  return 0;
}
