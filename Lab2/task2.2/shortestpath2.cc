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
 * @brief Implements the edge, which supports time table. t0 and P indicate that
 * the edge can be traversed at time t0+t⋅P for all nonnegative integers t. d
 * indicates that it takes d time units to traverse the edge.
 */
struct Edge {
  int from;
  int to;
  int t0;
  int P;
  int d;
};

using GraphType = std::vector<std::vector<Edge>>;
using ResultType = std::pair<std::vector<int>, std::vector<int>>;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Gets the wait time before traversing an edge with t0 and P.
 * @param current_time: The current time.
 * @param t0: The t0.
 * @param P: The P.
 * @return The wait time.
 */
int GetWaitTime(int current_time, int t0, int P) {
  if (current_time <= t0) {
    return t0 - current_time;
  }

  int t = std::ceil((double)(current_time - t0) / P);
  return t0 + t * P - current_time;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implement Dijkstras algorithm to find the shortest path from one
 * node to all other nodes in a graph with non-negative edge weights.
 * @param graph: The graph, which stores edges of each node.
 * @param start: The start node.
 * @return: A pair, the first is the distance vector and the second is the
 * parent vector.
 */
ResultType ShortestPath(const GraphType& graph, int start) {
  int n = graph.size();

  std::vector<int> distance(n, kInfinity);
  std::vector<int> parent(n, kInvalidNode);
  std::vector<bool> found(n, false);

  using DistanceNodePair = std::pair<int, int>;
  using MinHeap =
      std::priority_queue<DistanceNodePair, std::vector<DistanceNodePair>,
                          std::greater<DistanceNodePair>>;

  MinHeap heap;
  heap.push(std::make_pair(0, start));
  distance[start] = 0;
  parent[start] = start;

  while (!heap.empty()) {
    auto p = heap.top();
    heap.pop();

    int d = p.first;
    int u = p.second;

    if (d > distance[u]) {
      continue;
    }

    found[u] = true;

    for (auto& e : graph[u]) {
      if (!found[e.to]) {
        // For P == 0, the edge can be used only at time t0 and never again.
        if (e.P == 0 && d > e.t0) {
          continue;
        }

        int weight = e.d + GetWaitTime(d, e.t0, e.P);
        if (distance[e.to] > d + weight) {
          distance[e.to] = d + weight;
          parent[e.to] = u;

          heap.push(std::make_pair(distance[e.to], e.to));
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
      scanf("%d %d %d %d %d", &e.from, &e.to, &e.t0, &e.P, &e.d);
      graph[e.from].push_back(e);
    }

    auto result = ShortestPath(graph, s);
    auto& distance = result.first;

    int qn;
    for (int i = 0; i < q; ++i) {
      scanf("%d", &qn);

      if (distance[qn] != kInfinity) {
        printf("%d\n", distance[qn]);
      } else {
        printf("Impossible\n");
      }
    }

    printf(" \n");
  }

  return 0;
}
