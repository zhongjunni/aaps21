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

const int kInfinity = 100000000;
const int kInvalidNode = -1;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Edge
 * @brief Implements the edge, which consists of 'from' node, 'to' node, and the
 * weight.
 */
struct Edge {
  int from;
  int to;
  int weight;
};

using GraphType = std::vector<std::vector<Edge>>;
using ResultType = std::pair<std::vector<int>, std::vector<int>>;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implement Bellman-Fords algorithm for finding the shortest path from a
 * node to all other nodes in a graph where edge weights may be negative. Since
 * there may exist negative cycles, the main loop may iterate V (the number of
 * nodes) times. So, the time complexity is O(V*E), where V is the total number
 * of vertex(nodes), and E is the total number of edges.
 * @param graph: The graph, which stores edges of each node.
 * @param start: The start node.
 * @return: A pair, the first is the distance vector and the second is the
 * parent vector.
 */
ResultType ShortestPath(const GraphType& graph, int start) {
  int n = graph.size();

  std::vector<int> distance(n, kInfinity);
  std::vector<int> parent(n, kInvalidNode);

  distance[start] = 0;
  parent[start] = start;

  for (int i = 0; i < n; ++i) {
    bool update = false;

    for (int u = 0; u < n; ++u) {
      if (distance[u] == kInfinity) {
        continue;
      }

      for (auto& e : graph[u]) {
        if (distance[e.to] > distance[u] + e.weight) {
          distance[e.to] = distance[u] + e.weight;
          parent[e.to] = u;
          update = true;
        }
      }
    }

    if (!update) {
      break;
    }
  }

  // Check negtive cycles, for each node in a negive cycle, assign its distance
  // as -kInfinity.
  std::vector<bool> is_in_negtive_cycle(n, false);
  for (int i = 0; i < n; ++i) {
    for (int u = 0; u < n; ++u) {
      if (distance[u] == kInfinity) {
        continue;
      }

      for (auto& e : graph[u]) {
        if (is_in_negtive_cycle[u] || distance[e.to] > distance[u] + e.weight) {
          is_in_negtive_cycle[e.to] = true;
          distance[e.to] = -kInfinity;
        }
      }
    }
  }

  return std::make_pair(distance, parent);
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

int main(void) {
  int n, m, q, s;
  Edge e;

  while (scanf("%d %d %d %d", &n, &m, &q, &s) != EOF) {
    if (n == 0 && m == 0 && q == 0 && s == 0) {
      break;
    }

    GraphType graph(n);

    for (int i = 0; i < m; ++i) {
      scanf("%d %d %d", &e.from, &e.to, &e.weight);
      graph[e.from].push_back(e);
    }

    auto result = ShortestPath(graph, s);
    auto& distance = result.first;

    int qn;
    for (int i = 0; i < q; ++i) {
      scanf("%d", &qn);

      if (distance[qn] == kInfinity) {
        printf("Impossible\n");
      } else if (distance[qn] == -kInfinity) {
        printf("-Infinity\n");
      } else {
        printf("%d\n", distance[qn]);
      }
    }

    printf(" \n");
  }

  return 0;
}
