#include <stdio.h>

int add_three(int a, int b, int c) {
  int x = a;
  int y = b;
  int z = c;
  return x + y + z;
}

int main() {
  int sum = add_three(1, 2, 3);
  printf("%d\n", sum);
}
