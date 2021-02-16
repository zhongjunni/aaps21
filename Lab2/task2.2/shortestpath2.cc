#include <climits>
#include <cmath>
#include <cstdio>
#include <queue>
#include <set>

namespace aaps {
namespace zhoni04 {

using WeightType = long long;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Edge
 * @brief Implements the edge, which supports time table.
 */
struct Edge {
 public:
  /**
   * @brief Initializes a new instance of edge by given the source node, the
   * destination node, t0 and P to indicate that the edge can be traversed at
   * time t0+t⋅P for all nonnegative integers t, and d to indicate that it takes
   * d time units to traverse the edge.
   * @param _u: The source node.
   * @param _v: The destination node.
   * @param _t0: The t0.
   * @param _p: The P.
   * @param _d: The d.
   */
  Edge(int _u, int _v, int _t0, int _p, int _d) {
    src = _u;
    dst = _v;
    t0 = _t0;
    P = _p;
    d = _d;
  }

  int src;
  int dst;
  int t0;
  int P;
  int d;
};

using GraphType = std::vector<std::vector<Edge>>;

const WeightType kInfinity = LLONG_MAX;
const int kInvalidNode = -1;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Gets the next node from candidate nodes, which has current shortest
 * distance.
 * @param distance: The distance, which stores current shortest distance of
 * between start node and other node.
 * @param candidate_nodes: The candidate nodes.
 * @return The node, which has current shortest distance. If not found, return
 * kInvalidNode.
 */
int GetNextNode(const std::vector<WeightType>& distance,
                const std::set<int>& candidate_nodes) {
  WeightType min_weight = LLONG_MAX;
  int min_node = kInvalidNode;

  for (auto itr = candidate_nodes.begin(); itr != candidate_nodes.end();
       ++itr) {
    if (distance[*itr] < min_weight) {
      min_weight = distance[*itr];
      min_node = *itr;
    }
  }

  return min_node;
}

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
 * @brief Implement Dijkstras algorithm to find the shortest path from one node
 * to all other nodes in a graph with non-negative edge weights.
 * @param graph: The graph, which stores edges of each node.
 * @param start: The start node.
 * @param distance: The distance, used for storing the shortest distance of
 * between start node and other node.
 * @param parent: The parent, used for storing the parent node of each node.
 */
void ShortestPath(const GraphType& graph, int start,
                  std::vector<WeightType>* distance,
                  std::vector<int>* parent = nullptr) {
  if (distance == nullptr) {
    return;
  }

  int n = graph.size();
  distance->resize(n);
  distance->assign(n, kInfinity);
  if (parent != nullptr) {
    parent->resize(n);
    parent->assign(n, -1);
  }

  std::vector<bool> marked(n, false);
  std::set<int> candidate_nodes;
  (*distance)[start] = 0;
  candidate_nodes.insert(start);
  if (parent != nullptr) {
    (*parent)[start] = start;
  }

  while (!candidate_nodes.empty()) {
    int curr_node = GetNextNode(*distance, candidate_nodes);
    if (curr_node == kInvalidNode || (*distance)[curr_node] == kInfinity) {
      break;
    }

    marked[curr_node] = true;
    candidate_nodes.erase(curr_node);

    const std::vector<Edge>& edges = graph[curr_node];
    WeightType curr_weight = (*distance)[curr_node];
    int m = edges.size();
    for (int i = 0; i < m; ++i) {
      // For P == 0, the edge can be used only at time t0 and never again.
      if (edges[i].P == 0 && curr_weight > edges[i].t0) {
        continue;
      }

      WeightType weight =
          edges[i].d + GetWaitTime(curr_weight, edges[i].t0, edges[i].P);

      if (curr_weight + weight < (*distance)[edges[i].dst]) {
        (*distance)[edges[i].dst] = curr_weight + weight;

        if (parent != nullptr) {
          (*parent)[edges[i].dst] = curr_node;
        }
      }

      if (!marked[edges[i].dst]) {
        candidate_nodes.insert(edges[i].dst);
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

    GraphType graph(n);

    int u, v, t0, P, dt;
    for (int i = 0; i < m; ++i) {
      scanf("%d %d %d %d %d", &u, &v, &t0, &P, &dt);
      graph[u].push_back(Edge(u, v, t0, P, dt));
    }

    std::vector<WeightType> distance(n);
    ShortestPath(graph, s, &distance);

    int qn;
    for (int i = 0; i < q; ++i) {
      scanf("%d", &qn);

      if (distance[qn] != kInfinity) {
        printf("%lld\n", distance[qn]);
      } else {
        printf("Impossible\n");
      }
    }

    printf(" \n");
  }

  return 0;
}
