#include <cstdio>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class DisjointSet
 * @brief Implements a disjoint set, this class supports operations of merging
 * and querying. To optimize merge and query, this class maintains a set size
 * for each root node. When merging two sets, the class will link root of
 * smaller set to root of larger set.
 */
class DisjointSet {
 public:
  /**
   * @brief Initializes a new instance of disjoint set with distinct integers
   * from 0 ~ n-1.
   * @param n: The number of elements in the set.
   */
  explicit DisjointSet(int n) : n_(n), parent_(n), set_size_(n, 1) {
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  /**
   * @brief Merges the sets containing the two given integers, assumed both
   * integers are between 0 ~ n-1. Time complexity: O(log(n)).
   * @param a: The first integer.
   * @param b: The second integer.
   */
  void Union(int a, int b) {
    if (a == b) {
      return;
    }

    int root_a = Find(a);
    int root_b = Find(b);
    if (root_a == root_b) {
      return;
    }

    if (set_size_[root_a] < set_size_[root_b]) {
      set_size_[root_b] += set_size_[root_a];
      parent_[root_a] = root_b;
    } else {
      set_size_[root_a] += set_size_[root_b];
      parent_[root_b] = root_a;
    }
  }

  /**
   * @brief Query if the two given integers are in the same set, assumed both
   * integers are between 0 ~ n-1. Time complexity: O(log(n)).
   * @param a: The first integer.
   * @param b: The second integer.
   */
  bool Same(int a, int b) const {
    if (a == b) {
      return true;
    }

    return Find(a) == Find(b);
  }

 private:
  int Find(int a) const {
    while (a != parent_[a]) {
      a = parent_[a];
    }

    return a;
  }

  int n_;
  std::vector<int> parent_;
  std::vector<int> set_size_;
};

}  // namespace zhoni04
}  // namespace aaps

using DisjointSet = aaps::zhoni04::DisjointSet;

int main(void) {
  int N, Q;
  scanf("%d %d", &N, &Q);

  DisjointSet set(N);

  char operation;
  int a, b;
  for (int i = 0; i < Q; ++i) {
    scanf(" %c %d %d", &operation, &a, &b);
    if (operation == '?') {
      if (set.Same(a, b)) {
        printf("yes\n");
      } else {
        printf("no\n");
      }
    } else if (operation == '=') {
      set.Union(a, b);
    }
  }

  return 0;
}
