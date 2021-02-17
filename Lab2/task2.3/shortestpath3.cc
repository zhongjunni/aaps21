#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <vector>

namespace aaps {
namespace zhoni04 {

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

  int src;
  int dst;
  WeightType weight;
};

const WeightType kInfinity = 100000001;
const int kInvalidNode = -1;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implement Bellman-Fords algorithm for finding the shortest path from a
 * node to all other nodes in a graph where edge weights may be negative.
 * @param edges: The edges in the graph.
 * @param n: The count of nodes.
 * @param start: The start node.
 * @param distance: The distance, used for storing the shortest distance of
 * between start node and other node.
 * @param parent: The parent, used for storing the parent node of each node.
 */
void ShortestPath(const std::vector<Edge>& edges, int n, int start,
                  std::vector<WeightType>* distance,
                  std::vector<int>* parent = nullptr) {
  if (distance == nullptr) {
    return;
  }

  distance->resize(n);
  distance->assign(n, kInfinity);
  if (parent != nullptr) {
    parent->resize(n);
    parent->assign(n, -1);
  }

  (*distance)[start] = 0;
  if (parent != nullptr) {
    (*parent)[start] = start;
  }

  int m = edges.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((*distance)[edges[j].src] == kInfinity) {
        continue;
      }

      if ((*distance)[edges[j].src] + edges[j].weight <
          (*distance)[edges[j].dst]) {
        (*distance)[edges[j].dst] =
            std::max(-kInfinity, (*distance)[edges[j].src] + edges[j].weight);

        if (parent != nullptr) {
          (*parent)[edges[j].dst] = edges[j].src;
        }
      }
    }
  }

  // Check negtive cycles, for each node in a negive cycle, assign its distance
  // as -kInfinity.
  std::vector<bool> is_in_negtive_cycle(n, false);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((*distance)[edges[j].src] == kInfinity) {
        continue;
      }

      if (is_in_negtive_cycle[edges[j].src] ||
          (*distance)[edges[j].src] + edges[j].weight <
              (*distance)[edges[j].dst]) {
        is_in_negtive_cycle[edges[j].dst] = true;
        (*distance)[edges[j].dst] = -kInfinity;
      }
    }
  }
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

int main(void) {
  int n, m, q, s;

  while (scanf("%d %d %d %d", &n, &m, &q, &s) != EOF) {
    if (n == 0 && m == 0 && q == 0 && s == 0) {
      break;
    }

    std::vector<Edge> edges;

    int src, dst;
    WeightType weight;
    for (int i = 0; i < m; ++i) {
      scanf("%d %d %lld", &src, &dst, &weight);
      edges.push_back(Edge(src, dst, weight));
    }

    std::vector<WeightType> distance(n);
    ShortestPath(edges, n, s, &distance);

    int qn;
    for (int i = 0; i < q; ++i) {
      scanf("%d", &qn);

      if (distance[qn] == kInfinity) {
        printf("Impossible\n");
      } else if (distance[qn] == -kInfinity) {
        printf("-Infinity\n");
      } else {
        printf("%lld\n", distance[qn]);
      }
    }

    printf(" \n");
  }

  return 0;
}
