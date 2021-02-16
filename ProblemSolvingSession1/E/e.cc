#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main(void) {
  int n;
  scanf("%d", &n);

  vector<int> prices(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &prices[i]);
  }

  sort(prices.begin(), prices.end(), greater<int>());
  long long discount = 0;

  for (int i = 2; i < n; i = i + 3) {
    discount += prices[i];
  }

  printf("%lld\n", discount);

  return 0;
}
