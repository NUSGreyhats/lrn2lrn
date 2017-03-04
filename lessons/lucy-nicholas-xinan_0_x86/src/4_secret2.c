#include <stdio.h>

int main() {
  int n = 10;
  int result = 1;
  for (int i = 1; i <= n; ++i) {
    result *= i;
  }
  printf("%d\n", result);
}
