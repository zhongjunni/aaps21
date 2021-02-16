#include <algorithm>
#include <cstdio>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function that computes what to pack in a capacity limited
 * knapsack to maximize the total value of all the items packed. Time
 * complexity: O(n * capcacity)
 * @param capacity: The capacity of the knapsack.
 * @param value: The value of items.
 * @param weight: The weight of items.
 * @return The indices of the chosen items.
 */
std::vector<int> Knapsack(int capacity, const std::vector<int>& value,
                          const std::vector<int>& weight) {
  int n = value.size();
  std::vector<int> row(capacity + 1, 0);
  std::vector<std::vector<int>> dp(n + 1, row);

  for (int i = 1; i < n + 1; ++i) {
    for (int c = 1; c < capacity + 1; ++c) {
      if (weight[i - 1] > c) {
        // Can not put this in the knapsack.
        dp[i][c] = dp[i - 1][c];
      } else {
        dp[i][c] =
            std::max(value[i - 1] + dp[i - 1][c - weight[i - 1]], dp[i - 1][c]);
      }
    }
  }

  // Find path from the result.
  std::vector<int> result;
  int i = n, c = capacity;
  while (dp[i][c] != 0) {
    // This means item i-1 was put in the knapsack.
    if (dp[i][c] != dp[i - 1][c]) {
      result.push_back(i - 1);
      c -= weight[i - 1];
    }
    --i;
  }

  return result;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

int main(void) {
  int C, n;
  while (scanf("%d %d", &C, &n) != EOF) {
    vector<int> value(n);
    vector<int> weight(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d %d", &value[i], &weight[i]);
    }

    vector<int> result = Knapsack(C, value, weight);
    int len = result.size();
    printf("%d\n", len);
    for (int i = 0; i < len; ++i) {
      if (i != 0) {
        printf(" ");
      }
      printf("%d", result[i]);
    }

    if (len != 0) {
      printf("\n");
    }
  }
  return 0;
}
