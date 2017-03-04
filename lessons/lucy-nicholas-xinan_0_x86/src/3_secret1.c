#include <stdio.h>

int secret(int n) {
  return n == 0 ? 1 : n * secret(n - 1);
}

int main() {
  printf("%d\n", secret(5));
}
