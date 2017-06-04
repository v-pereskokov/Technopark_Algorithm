#include <cstdio>
#include <vector>
#include <algorithm>

using data = unsigned long long int;
using container = std::vector<data>;

data findMax(container &target) {
  data max = target[0];
  for (int i = 1; i < target.size(); i++)
    if (target[i] > max)
      max = target[i];
  return max;
};

void countSort(container &target, data radix) {
  container buffer(target.size());
  container count(10, 0);
  int i;
  for (i = 0; i < target.size(); i++) {
    count[(target[i] / radix) % 10]++;
  }
  for (i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }
  for (i = target.size() - 1; i >= 0; i--) {
    buffer[--count[(target[i] / radix) % 10]] = target[i];
  }
  for (i = 0; i < target.size(); i++) {
    target[i] = buffer[i];
  }
};

void radixSort(container &target) {
  data max = findMax(target);
  for (data radix = 1; max / radix > 0; radix *= 10) {
    countSort(target, radix);
  }
}

int main() {
  size_t n;
  scanf("%lu", &n);
  std::vector<data> v;
  for (size_t i = 1; i <= n; ++i) {
    data element;
    scanf("%lld", &element);
    v.push_back(element);
  }
  std::sort(v.begin(), v.end());
  for (auto i : v) {
    printf("%lld\n", i);
  }
  return 0;
}
