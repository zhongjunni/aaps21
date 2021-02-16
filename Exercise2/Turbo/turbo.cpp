#include <cstdio>
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

int main(void) {
  int N;
  scanf("%d", &N);
  FenwickTree tree(N);
  std::vector<int> positions(N + 1, 0);

  int num;
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &num);
    positions[num] = i;
    tree.Add(i - 1, 1);
  }

  int curr_not_chosen_min = 1;
  int curr_not_chosen_max = N;
  int pos;
  int swaps;
  for (int i = 1; i <= N; ++i) {
    if (i % 2 == 1) {
      pos = positions[curr_not_chosen_min];
      swaps = tree.Sum(pos - 1);
      tree.Add(pos - 1, -1);
      ++curr_not_chosen_min;
    } else {
      pos = positions[curr_not_chosen_max];
      swaps = tree.Sum(N) - tree.Sum(pos);
      tree.Add(pos - 1, -1);
      --curr_not_chosen_max;
    }

    printf("%d\n", swaps);
  }

  return 0;
}
