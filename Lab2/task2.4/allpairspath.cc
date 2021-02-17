#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <vector>

namespace aaps {
namespace zhoni04 {

using WeightType = long long;
using GraphType = std::vector<std::vector<WeightType>>;

const WeightType kInfinity = 100000001;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements Floyd-Warshalls algorithm for finding the shortest distance
 * between all pairs of nodes in a graph with edge weights.
 * @param graph: The graph, which stores weight between all pairs of nodes.
 * @return The shortest distance between all pairs of nodes, represented by a
 * two-dimensional vector.
 */
GraphType ShortestPathAllPairs(const GraphType& graph) {
  int n = graph.size();

  GraphType distance(graph);

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (distance[i][k] < kInfinity && distance[k][j] < kInfinity)
          distance[i][j] =
              std::min(distance[i][j], distance[i][k] + distance[k][j]);
      }
    }
  }

  // Check negtive cycles, for each node in a negive cycle, assign its distance
  // as -kInfinity.
  std::vector<bool> is_in_negtive_cycle(n, false);
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (distance[i][k] == kInfinity || distance[k][j] == kInfinity) {
          continue;
        }

        if (is_in_negtive_cycle[i] ||
            distance[i][k] + distance[k][j] < distance[i][j]) {
          is_in_negtive_cycle[j] = true;
          distance[i][j] = -kInfinity;
        }
      }
    }
  }

  return distance;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

int main(void) {
  int n, m, q;

  while (scanf("%d %d %d", &n, &m, &q) != EOF) {
    if (n == 0 && m == 0 && q == 0) {
      break;
    }

    GraphType graph(n, std::vector<WeightType>(n, kInfinity));
    for (int i = 0; i < n; ++i) {
      graph[i][i] = 0;
    }

    int u, v;
    WeightType w;
    for (int i = 0; i < m; ++i) {
      scanf("%d %d %lld", &u, &v, &w);
      graph[u][v] = std::min(w, graph[u][v]);
    }

    GraphType distance = ShortestPathAllPairs(graph);
    for (int i = 0; i < q; ++i) {
      scanf("%d %d", &u, &v);
      if (distance[u][v] == kInfinity) {
        printf("Impossible\n");
      } else if (distance[u][v] == -kInfinity) {
        printf("-Infinity\n");
      } else {
        printf("%lld\n", distance[u][v]);
      }
    }

    printf(" \n");
  }

  return 0;
}
