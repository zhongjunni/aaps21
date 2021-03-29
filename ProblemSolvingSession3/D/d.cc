#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aaps {
namespace zhoni04 {

#define MAX_N 301
#define MAX_W 53

int N, W;
int dp[MAX_N][MAX_W];

int revenue, price;

void Init() {
  for (int i = 0; i < MAX_N; ++i) {
    for (int j = 0; j < MAX_W; ++j) {
      if (i == 0) {
        dp[i][j] = 0;
      } else {
        dp[i][j] = -1;
      }
    }
  }
}

int MaxRevenue(
    const std::vector<std::vector<std::pair<int, int>>>& weekly_price_seat,
    int n, int w) {
  if (n <= 0 || w < 0) {
    return 0;
  }

  if (dp[n][w] != -1) {
    return dp[n][w];
  }

  int this_max = -1;
  int this_price = -1;
  for (int i = 0; i < weekly_price_seat[w].size(); ++i) {
    int r = MaxRevenue(weekly_price_seat, n - weekly_price_seat[w][i].second,
                       w - 1) +
            weekly_price_seat[w][i].first *
                std::min(weekly_price_seat[w][i].second, n);
    if (r > this_max) {
      this_max = r;
      this_price = weekly_price_seat[w][i].first;
    } else if (r == this_max) {
      if (this_price > weekly_price_seat[w][i].first) {
        this_price = weekly_price_seat[w][i].first;
      }
    }
  }

  dp[n][w] = this_max;
  if (n == N && w == W) {
    revenue = this_max;
    price = this_price;
  }

  return this_max;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin >> N >> W;

  vector<vector<pair<int, int>>> weekly_price_seat(W + 1);
  int K;
  for (int i = W; i >= 0; --i) {
    cin >> K;
    weekly_price_seat[i].assign(K, make_pair(0, 0));

    int p;
    for (int j = 0; j < K; ++j) {
      cin >> p;
      weekly_price_seat[i][j].first = p;
    }

    int s;
    for (int j = 0; j < K; ++j) {
      cin >> s;
      weekly_price_seat[i][j].second = s;
    }
  }

  Init();
  MaxRevenue(weekly_price_seat, N, W);

  cout << revenue << endl;
  cout << price << endl;

  return 0;
}
