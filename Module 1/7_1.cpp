#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

using ulli = unsigned long long int;

struct Athlete {
  Athlete(const ulli m, const ulli s)
  : _m(m),  _s(s) {}
  
  ulli _m;
  ulli _s;
};

std::size_t __maxPyramid__(const std::vector<Athlete> &athletes) {
  std::vector<Athlete> result{ athletes[0] };
  ulli sum = athletes[0]._m;
  for (std::size_t i = 1; i < athletes.size(); ++i) {
    Athlete current = athletes[i];
    if (sum <= current._s) {
      result.push_back(current);
      sum += current._m;
    }
  }
  return result.size();
}

std::size_t maxPyramid(std::vector<Athlete> *athletes) {
  std::sort(athletes->begin(), athletes->end(), [](const Athlete &lhs, const Athlete &rhs){ return lhs._s < rhs._s; });
  std::stable_sort(athletes->begin(), athletes->end(), [](const Athlete &lhs, const Athlete &rhs){ return lhs._m < rhs._m; });
  return __maxPyramid__(*athletes);
}

int main() {
  ulli m, s;
  std::size_t n = 0;
  std::vector<Athlete> athletes;
  while (n++ <= 100000 && scanf("%lld %lld", &m, &s) == 2) {
    assert(m > 0 && s > 0 && m <= 2000000 && s <= 2000000);
    athletes.push_back(Athlete(m, s));
  }
  if (n > 1) {
    printf("%lu\n", maxPyramid(&athletes));
  }
  return 0;
}