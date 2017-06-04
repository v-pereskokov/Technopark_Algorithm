#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

using u_int = unsigned int;

template <class IT>
IT binarySearch(IT begin, IT end, int element) {
  if (begin == end)
    return end;
  IT first = begin;
  IT last = end;
  --last;
  while (first < last) {
    IT mid = first + ((last - first) / 2);
    if (element <= *mid)
      last = mid;
    else
      first = mid + 1;
  }
  return (first == end || *first != element ) ? end : first;
}

template <class IT>
std::pair<IT, IT> findEdge(IT begin, IT end, int element) {
  if (begin == end)
    return {begin, end};
  IT first = begin;
  IT last = end;
  --last;
  std::size_t i = 0;
  IT preEdge = first;
  while (first < last) {
    if (element <= *first) {
      return {preEdge, first + 1};
    }
    preEdge = first;
    first += pow(2, i++);
  }
  return {preEdge, last + 1};
}

void search(std::vector<int> *a, std::vector<int> *b, std::vector<int> *c) {
  auto begin_a = a->begin();
  auto end_a = a->end();
  auto index = begin_a;
  auto pre_index = index;
  for (auto it = b->begin(); it < b->end(); ++it) {
    auto edge = findEdge(begin_a, end_a, *it);
    index = binarySearch(edge.first, edge.second, *it);
    if (index == edge.second) {
      index = pre_index;
      continue;
    }
    pre_index = index;
    c->push_back(*it);
    index += 1;
  }
}

int main() {
  u_int n, m;
  scanf("%d %d", &n, &m);
  if (n > 0 && m > 0 && n <= 10000 && m <= 10000 && n > m) {
    int element;
    std::vector<int> a;
    for (std::size_t i = 1; i <= n; ++i) {
      scanf("%d", &element);
      a.push_back(element);
    }
    std::vector<int> b;
    for (std::size_t i = 1; i <= m; ++i) {
      scanf("%d", &element);
      b.push_back(element);
    }
    std::vector<int> c;
    search(&a, &b, &c);
    for (auto i : c)
      printf("%d ", i);
    printf("\n");
    return 0;
  }
}