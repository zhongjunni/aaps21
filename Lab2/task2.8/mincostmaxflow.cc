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
 * @brief Finds the shortest path from vertex s to vertex t by Dijkstras
 * algorithm. Time complexity is O(V + E*logV), where V is the total number of
 * vertex(nodes), and E is the total number of edges.
 * @param graph: The graph.
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param parent: For storing the edge between a vertex and its parent vertex.
 * @param potential: For storing the potential of each vertex.
 * @return: True if found a path, otherwise false.
 */
bool ShortestPath(GraphType& graph, int s, int t, std::vector<Edge*>* parent,
                  std::vector<WeightType>* potential) {
  int n = graph.size();
  parent->assign(n, nullptr);

  std::vector<WeightType> distance(n, kInfinity);

  using DistanceNodePair = std::pair<WeightType, int>;
  using MinHeap =
      std::priority_queue<DistanceNodePair, std::vector<DistanceNodePair>,
                          std::greater<DistanceNodePair>>;

  MinHeap heap;
  heap.push(std::make_pair(0, s));
  distance[s] = 0;

  while (!heap.empty()) {
    auto p = heap.top();
    heap.pop();

    WeightType d = p.first;
    int u = p.second;

    if (d > distance[u]) {
      continue;
    }

    for (auto& e : graph[u]) {
      if (e.flow < e.capacity &&
          distance[e.to] > d + e.cost + (*potential)[u] - (*potential)[e.to]) {
        distance[e.to] = d + e.cost + (*potential)[u] - (*potential)[e.to];
        (*parent)[e.to] = &e;
        heap.push(std::make_pair(distance[e.to], e.to));
      }
    }
  }

  if (distance[t] != kInfinity) {
    for (int i = 0; i < n; ++i) {
      (*potential)[i] = std::min((*potential)[i] + distance[i], kInfinity);
    }

    return true;
  }

  return false;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements an algorithm for finding the maximum flow with the minimal
 * cost in a graph. This is a generalization of maximum flow where each edge
 * both has a capacity and a cost. The cost of a flow through an edge is the
 * flow multiplied by the cost for that edge. The shortest path search is based
 * on the above Dijkstra algorithm, so the time complexity is O(V*E) * O(V + E*logV),
 * where V is the total number of vertex(nodes), and E is the total number of edges.
 * @param graph: The graph.
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @return: A pair. The first are a pair of the max flow and the min cost. The
 * second is the flow graph.
 */
ResultType MaxFlowMinCost(const GraphType& graph, int s, int t) {
  int n = graph.size();
  std::vector<Edge*> parent(n);
  std::vector<WeightType> potential(n, kInfinity);

  WeightType max_flow = 0;
  WeightType min_cost = 0;
  GraphType flow_graph(graph);

  while (ShortestPath(flow_graph, s, t, &parent, &potential)) {
    WeightType path_flow = kInfinity;
    for (auto e = parent[t]; e != nullptr; e = parent[e->from]) {
      path_flow = std::min(path_flow, e->capacity - e->flow);
    }

    max_flow += path_flow;

    for (auto e = parent[t]; e != nullptr; e = parent[e->from]) {
      e->flow += path_flow;
      flow_graph[e->to][e->rev].flow -= path_flow;

      min_cost += path_flow * e->cost;
    }
  }

  return std::make_pair(std::make_pair(max_flow, min_cost), flow_graph);
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

  printf("%lld %lld\n", maxflow_mincost.first, maxflow_mincost.second);

  return 0;
}