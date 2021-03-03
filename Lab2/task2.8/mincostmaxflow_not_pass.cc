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

using WeightType = long long;

const WeightType kInfinity = 1000000001;
const int kInvalidNode = -1;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Edge
 * @brief Implements the edge, which consists of 'from' node, 'to' node, the
 * capacity, the flow, the cost, and 'rev' to help find the reverse edge.
 */
struct Edge {
  Edge(int _from, int _to, WeightType _capacity, WeightType _flow,
       WeightType _cost, int _rev)
      : from(_from),
        to(_to),
        capacity(_capacity),
        flow(_flow),
        cost(_cost),
        rev(_rev) {}

  int from;
  int to;
  WeightType capacity;
  WeightType flow;
  WeightType cost;
  int rev;
};

using GraphType = std::vector<std::vector<Edge>>;
using ResultType = std::pair<std::pair<WeightType, WeightType>, GraphType>;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Finds a path from vertex s to vertex t by BFS.
 * @param graph: The graph.
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param parent: For storing the edge between a vertex and its parent vertex.
 * @return: True if found a path, otherwise false.
 */
bool ShortestPath(GraphType& graph, int s, int t, std::vector<Edge*>* parent) {
  int n = graph.size();
  parent->assign(n, nullptr);

  std::vector<WeightType> distance(n, kInfinity);
  std::vector<bool> found(n, false);

  using DistanceNodePair = std::pair<int, int>;
  using MinHeap =
      std::priority_queue<DistanceNodePair, std::vector<DistanceNodePair>,
                          std::greater<DistanceNodePair>>;

  MinHeap heap;
  heap.push(std::make_pair(0, s));
  distance[s] = 0;

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
      //

      heap.push(std::make_pair(distance[e.to], e.to));
    }
  }

  return false;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements an algorithm for finding the maximum flow with the minimal
 * cost in a graph. This is a generalization of maximum flow where each edge
 * both has a capacity and a cost. The cost of a flow through an edge is the
 * flow multiplied by the cost for that edge.
 * @param graph: The graph.
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @return: A pair. The first is the max flow. The second is the flow graph.
 */
ResultType MaxFlowMinCost(const GraphType& graph, int s, int t) {
  int n = graph.size();
  std::vector<Edge*> parent(n);

  WeightType max_flow = 0;
  WeightType min_cost = 0;
  GraphType flow_graph(graph);

  while (ShortestPath(flow_graph, s, t, &parent)) {
    WeightType path_flow = kInfinity;
    for (auto e = parent[t]; e != nullptr; e = parent[e->from]) {
      path_flow = std::min(path_flow, e->capacity - e->flow);
    }

    max_flow += path_flow;

    for (auto e = parent[t]; e != nullptr; e = parent[e->from]) {
      e->flow += path_flow;
      flow_graph[e->to][e->rev].flow -= path_flow;
    }
  }

  return std::make_pair(max_flow, flow_graph);
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);

  GraphType graph(n);

  int u, v, c, w;
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %d %d", &u, &v, &c, &w);
    graph[u].emplace_back(u, v, c, 0, w, graph[v].size());
    graph[v].emplace_back(v, u, 0, 0, -w, graph[u].size() - 1);
  }

  auto result = MaxFlowMinCost(graph, s, t);
  auto& maxflow_mincost = result.first;

  printf("%d %d\n", maxflow_mincost.first, maxflow_mincost.second);

  return 0;
}