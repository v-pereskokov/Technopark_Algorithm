#include <stdio.h>
#include <vector>
#include <iostream>

typedef long long int lli;

lli fillTable(std::vector<std::vector<lli>> *table, int search) {
  for (int i = 1; i < table->size(); ++i) {
    for (int j = 1; j < table->size(); ++j) {
      lli k = 0;
      if (i - j > 0) {
        k = (*table)[i - j - 1][j];
      } else if (i == j) {
        k = 1;
      }
      (*table)[i][j] = (*table)[i][j - 1] + k;
    }
  }
  return (*table)[1][1];
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::vector<lli>> pyramid(n, std::vector<lli>(n, 1));
  printf("%lli\n", fillTable(&pyramid, n));
  return 0;
}
