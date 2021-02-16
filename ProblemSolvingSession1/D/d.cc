#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class FenwickTree
 * @brief Implements a Fenwick Tree based on array, this class supports
 * operations of two types: (a) increment an element in the array or (b) query
 * the prefix sum of a portion of the array.
 */
class FenwickTree {
 public:
  /**
   * @brief Initializes a new instance of Fenwick Tree.
   * @param n: The length of the array, assumed to be positive.
   */
  explicit FenwickTree(int n) : n_(n + 1), arr_(n_, 0) {}

  /**
   * @brief Increases array value at index with delta. Time complexity:
   * O(log(n)).
   * @param index: The index, assumed to be between 0 ~ n-1 (both inclusive).
   * @param delta: The delta.
   */
  void Add(int index, int delta) {
    int i = index + 1;

    while (i <= n_) {
      arr_[i] += delta;
      i += i & -i;
    }
  }

  /**
   * @brief Computes the sum of array value from index 0 to index-1. Time
   * complexity: O(log(n)).
   * @param index: The index, assumed to be between 0 ~ n (both inclusive).
   * @return The sum.
   */
  long long Sum(int index) const {
    long long sum = 0;

    while (index > 0) {
      sum += arr_[index];
      index -= index & -index;
    }

    return sum;
  }

 private:
  int n_;
  std::vector<long long> arr_;
};

}  // namespace zhoni04
}  // namespace aaps

using FenwickTree = aaps::zhoni04::FenwickTree;
using namespace std;

#define MAX_N 100000

int main(void) {
  int n;
  scanf("%d", &n);

  std::vector<int> pos(2 * MAX_N);
  for (int i = 0; i < n; ++i) {
    int m, r;
    scanf("%d %d", &m, &r);

    // Use a bigger fenwick tree.
    // The first half used for store operations.
    FenwickTree tree(2 * MAX_N);
    for (int j = 0; j < m; ++j) {
      tree.Add(MAX_N + j, 1);
      pos[j] = MAX_N + j;
    }

    int a;
    for (int j = 0; j < r; ++j) {
      scanf("%d", &a);
      if (j != 0) {
        printf(" ");
      }
      printf("%lld", tree.Sum(pos[a - 1]));
      tree.Add(pos[a - 1], -1);
      pos[a - 1] = MAX_N - j - 1;
      tree.Add(pos[a - 1], 1);
    }
    printf("\n");
  }

  return 0;
}
