#include <algorithm>
#include <cstdio>

using namespace std;

#define MAX_N 100001
uint64_t wanted[MAX_N];

int main(void) {
  uint64_t M;
  int N;
  uint64_t total_wanted = 0;

  scanf("%lld %d", &M, &N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &wanted[i]);
    total_wanted += wanted[i];
  }

  sort(wanted, wanted + N);

  uint64_t taken_away = 0;
  uint64_t diff = total_wanted - M;
  for (int i = 0; i < N; ++i) {
    int left_children = N - i;
    uint64_t avg = diff / left_children;

    if (wanted[i] >= avg) {
      wanted[i] -= avg;
      diff -= avg;
      taken_away += avg * avg;
    } else {
      taken_away += wanted[i] * wanted[i];
      diff -= wanted[i];
      wanted[i] = 0;
    }
  }

  printf("%lld\n", taken_away);

  return 0;
}