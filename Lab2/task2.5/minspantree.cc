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
#include <string>
#include <utility>
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
   * @brief Queries if the two given integers are in the same set, assumed both
   * integers are between 0 ~ n-1. Time complexity: O(log(n)).
   * @param a: The first integer.
   * @param b: The second integer.
   * @return: True if in the same set, otherwise false.
   */
  bool Same(int a, int b) const {
    if (a == b) {
      return true;
    }

    return Find(a) == Find(b);
  }

  /**
   * @brief Gets the set count. Time complexity: O(nlog(n)).
   * @return: The set count.
   */
  int Count() const {
    std::set<int> roots;
    for (int i = 0; i < n_; ++i) {
      roots.insert(Find(i));
    }

    return roots.size();
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

using WeightType = long long;

const WeightType kInfinity = 10000000001;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Edge
 * @brief Implements the edge, which consists of 'from' node, 'to' node, and the
 * weight.
 */
struct Edge {
  int from;
  int to;
  WeightType weight;

  /**
   * @brief Compares this weight and the other edge's weight.
   * @param other: The other edge.
   * @return: True if this weight is less than the other's weight, otherwise
   * false.
   */
  bool operator<(const Edge& other) { return weight < other.weight; }
};

using GraphType = std::vector<std::vector<Edge>>;
using ResultType = std::pair<WeightType, std::vector<Edge>>;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements an algorithm for finding a minimum spanning tree. Time
 * complexity: O((|E|+|V|)·log(|V|)), where |E| is count of edges and |V| is
 * count of vertices.
 * @param edges: The total edges of the original graph.
 * @return: A pair. The first is the cost of mst, which sum of weight of mst
 * edges. The second is the edges. If there is no minimum spanning tree, the
 * cost is -kInfinity.
 */
ResultType Mst(const GraphType& graph) {
  std::vector<Edge> edges;
  int n = graph.size();
  for (int i = 0; i < n; ++i) {
    for (auto& e : graph[i]) {
      edges.push_back(e);
    }
  }
  std::sort(edges.begin(), edges.end());

  WeightType cost = 0;
  std::vector<Edge> mst;
  DisjointSet djs(n);

  for (auto& e : edges) {
    if (!djs.Same(e.from, e.to)) {
      cost += e.weight;
      mst.push_back(e);
      djs.Union(e.from, e.to);
    }
  }

  if (djs.Count() != 1) {
    cost = -kInfinity;
  }

  return std::make_pair(cost, mst);
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

bool CompareFunc(const Edge& a, const Edge& b) {
  if (a.from < b.from) {
    return true;
  } else if (a.from == b.from) {
    return a.to < b.to;
  }

  return false;
}

int main(void) {
  int n, m;
  int u, v;
  WeightType w;
  Edge e;

  while (scanf("%d %d", &n, &m) != EOF) {
    if (n == 0 && m == 0) {
      break;
    }

    GraphType graph(n);
    for (int i = 0; i < m; ++i) {
      scanf("%d %d %lld", &u, &v, &w);
      e.from = std::min(u, v);
      e.to = std::max(u, v);
      e.weight = w;
      graph[e.from].push_back(e);
    }

    auto result = Mst(graph);
    auto& cost = result.first;
    auto& edges = result.second;

    if (cost == -kInfinity) {
      printf("Impossible\n");
    } else {
      printf("%lld\n", cost);
      std::sort(edges.begin(), edges.end(), CompareFunc);
      for (auto& e : edges) {
        printf("%d %d\n", e.from, e.to);
      }
    }
  }

  return 0;
}