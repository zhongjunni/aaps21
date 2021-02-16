#include <cstdio>

int main(void) {
  double n;
  while (scanf("%lf", &n) == 1) {
    if (n == 0) {
      break;
    }

    bool is_negtive = n < 0;
    if (is_negtive) {
      n = -n;
    }

    int max_p = 1;
    for (double base = 2;; ++base) {
      double pth_power = base * base;
      if (pth_power > n) {
        break;
      }

      int p = 2;
      while (pth_power < n) {
        ++p;
        pth_power *= base;
      }

      if (pth_power == n) {
        if (!is_negtive || p % 2 == 1) {
          max_p = p;
          break;
        }
      }
    }

    printf("%d\n", max_p);
  }

  return 0;
}
