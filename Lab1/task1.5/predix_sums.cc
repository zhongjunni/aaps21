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
  int N, Q;
  scanf("%d %d", &N, &Q);

  FenwickTree tree(N);

  char operation;
  int index, delta;
  for (int i = 0; i < Q; ++i) {
    scanf(" %c", &operation);
    if (operation == '+') {
      scanf("%d %d", &index, &delta);
      tree.Add(index, delta);
    } else if (operation == '?') {
      scanf("%d", &index);
      printf("%lld\n", tree.Sum(index));
    }
  }

  return 0;
}
