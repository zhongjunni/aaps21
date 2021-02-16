#include <cstdio>

// For each number n, we can represent it as 2^a * 5^b * c.
int main(void) {
  int n;
  scanf("%d", &n);

  int result = 1;
  int total_2 = 0;
  int total_5 = 0;

  for (int i = 1; i <= n; ++i) {
    int value = i;
    while (value % 10 == 0) {
      ++total_2;
      ++total_5;
      value /= 10;
    }

    while (value % 2 == 0) {
      ++total_2;
      value /= 2;
    }

    while (value % 5 == 0) {
      ++total_5;
      value /= 5;
    }

    result *= value % 1000;
    result %= 1000;
  }

  int diff = 0;
  int base = 0;

  if (total_2 > total_5) {
    diff = total_2 - total_5;
    base = 2;
  } else if (total_5 > total_2) {
    diff = total_5 - total_2;
    base = 5;
  }

  while (diff != 0) {
    result *= base;
    result %= 1000;
    --diff;
  }

  printf("%d\n", result);

  return 0;
}
