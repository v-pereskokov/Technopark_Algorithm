#include <cstdio>
#include <cmath>
#include <utility>

using u_int = unsigned int;

u_int get_divide(u_int target) {
  for (std::size_t i = 2; i * i < target; ++i) {
    if (target % i == 0)
      return i;
  }
  return target;
}

std::pair<u_int, u_int> decomposition(u_int target) {
  u_int divider = get_divide(target);
  u_int divide = target / divider;
  return std::pair<u_int, u_int>(divide, divide * (divider - 1));
}

int main() {
  u_int N;
  scanf("%d", &N);
  if (N <= pow(10, 7) && N > 1) {
    auto result = decomposition(N);
    printf("%d %d\n", result.first, result.second);
  }
  return 0;
}
