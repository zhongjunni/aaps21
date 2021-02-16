#include <cstdio>

int correct_number[7] = {0, 1, 2, 5, 6, 8, 9};
int display_mapping[10] = {0, 1, 2, -1, -1, 5, 9, -1, 8, 6};

void show(int n) {
  if (n < 0) {
    return;
  }

  do {
    printf("%d", display_mapping[correct_number[n % 7]]);
    n /= 7;
  } while (n > 0);

  printf("\n");
}

int main(void) {
  int n;
  while (scanf("%d", &n) != EOF) {
    show(n);
  }

  return 0;
}
