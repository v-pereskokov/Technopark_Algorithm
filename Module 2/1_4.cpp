#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using Symbol = char;
using cWord = char;
using Word = std::string;
using Words = std::vector<Word>;

bool less(const Symbol lhs, const Symbol rhs) {
  return lhs < rhs;
}

template <class IT, class comparator>
bool cmpString(IT begin1, IT end1, IT begin2, IT end2, const comparator &comp) {
  for (IT it = begin1, jt = begin2; it != end1 && jt != end2; ++it, ++jt) {
    if (comp(*jt, *it)) {
      return false;
    } else if (comp(*it, *jt)) {
      return true;
    }
  }
  return std::distance(begin1, end1) > std::distance(begin2, end2) ? false : true;
}

int StrCmp(const char* a, const char* b) {
  while (*a && *b && *a == *b)
        ++a, ++b;
  return *a - *b;
}

template <class IT, class comparator>
void insertionSort(IT begin, IT end, const comparator &comp) {
  for (auto it = begin + 1; it != end; ++it) {
    for (auto jt = it - 1; jt != begin - 1; --jt) {
//      if (!cmpString(jt->begin(), jt->end(), (jt + 1)->begin(), (jt + 1)->end(), less)) {
      if (StrCmp(jt->c_str(), (jt + 1)->c_str()) > 0) {
        std::swap(*jt, *(jt + 1));
      }
    }
  }
}

int main() {
  std::size_t n;
  scanf("%ld", &n);
  Words words;
  for (std::size_t i = 1; i <= n; ++i) {
    cWord word[255];
    scanf("%s", word);
    words.push_back(word);
  }
  insertionSort(words.begin(), words.end(), less);
  for (auto i : words) {
    printf("%s\n", i.c_str());
  }
  return 0;
}
