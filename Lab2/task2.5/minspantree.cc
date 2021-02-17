#include <algorithm>
#include <cstdio>
#include <set>
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

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Edge
 * @brief Implements the edge, which consists of source node, destination node,
 * and the weight.
 */
struct Edge {
 public:
  /**
   * @brief Initializes a new instance of edge.
   * @param s: The source node.
   * @param d: The destination node.
   * @param w: The weight.
   */
  Edge(int s, int d, WeightType w) {
    src = s;
    dst = d;
    weight = w;
  }

  /**
   * @brief Compares this weight and the other edge's weight.
   * @param other: The other edge.
   * @return: True if this weight is less than the other's weight, otherwise
   * false.
   */
  bool operator<(const Edge& other) { return weight < other.weight; }

  int src;
  int dst;
  WeightType weight;
};

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements an algorithm for finding a minimum spanning tree. Time
 * complexity: O((|E|+|V|)·log(|V|)), where |E| is count of edges and |V| is
 * count of vertices.
 * @param edges: The total edges of the original graph.
 * @param mst: The found minimum spanning tree.
 * @param djs: The disjoint set to help judge if we can find the mst.
 * @return: The cost of mst, sum of weight of mst edges.
 */
WeightType Mst(const std::vector<Edge>& edges, std::vector<Edge>* mst,
               DisjointSet* djs) {
  if (mst == nullptr || djs == nullptr) {
    return 0;
  }

  std::vector<Edge> local_edges(edges);
  std::sort(local_edges.begin(), local_edges.end());

  WeightType cost = 0;
  int n = local_edges.size();
  for (int i = 0; i < n; ++i) {
    if (djs->Same(local_edges[i].src, local_edges[i].dst)) {
      continue;
    }

    cost += local_edges[i].weight;
    mst->push_back(local_edges[i]);
    djs->Union(local_edges[i].src, local_edges[i].dst);
  }

  return cost;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

bool CompareFunc(const Edge& a, const Edge& b) {
  if (a.src < b.src) {
    return true;
  } else if (a.src == b.src) {
    return a.dst < b.dst;
  }

  return false;
}

int main(void) {
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF) {
    if (n == 0 && m == 0) {
      break;
    }

    std::vector<Edge> edges;
    edges.reserve(m);

    std::vector<Edge> mst;
    mst.reserve(m);

    DisjointSet djs(n);

    int u, v, w;
    for (int i = 0; i < m; ++i) {
      scanf("%d %d %d", &u, &v, &w);
      edges.push_back(Edge(std::min(u, v), std::max(u, v), w));
    }

    WeightType cost = Mst(edges, &mst, &djs);
    if (djs.Count() != 1) {
      printf("Impossible\n");
    } else {
      printf("%lld\n", cost);
      std::sort(mst.begin(), mst.end(), CompareFunc);
      for (auto itr = mst.begin(); itr != mst.end(); ++itr) {
        printf("%d %d\n", itr->src, itr->dst);
      }
    }
  }

  return 0;
}