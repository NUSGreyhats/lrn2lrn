#include <stdio.h>

int main() {
  int a, b, c;
  scanf("%d %d", &a, &b);
  if (a > b) {
    c = a - b;
  } else {
    c = a + b;
  }
  printf("%d\n", c);
}
