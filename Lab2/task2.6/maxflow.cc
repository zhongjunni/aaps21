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
 * capacity, the flow and 'rev' to help find the reverse edge.
 */
struct Edge {
  Edge(int _from, int _to, WeightType _capacity, WeightType _flow, int _rev)
      : from(_from), to(_to), capacity(_capacity), flow(_flow), rev(_rev) {}

  int from;
  int to;
  WeightType capacity;
  WeightType flow;
  int rev;
};

using GraphType = std::vector<std::vector<Edge>>;
using ResultType = std::pair<WeightType, GraphType>;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Finds a path from vertex s to vertex t by BFS.
 * @param graph: The graph.
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param parent: For storing the edge between a vertex and its parent vertex.
 * @return: True if found a path, otherwise false.
 */
bool BFS(GraphType& graph, int s, int t, std::vector<Edge*>* parent) {
  int n = graph.size();
  parent->assign(n, nullptr);

  std::queue<int> unvisited;
  unvisited.push(s);

  while (!unvisited.empty()) {
    int u = unvisited.front();
    unvisited.pop();

    for (auto& e : graph[u]) {
      if ((*parent)[e.to] == nullptr && e.to != s && e.flow < e.capacity) {
        (*parent)[e.to] = &e;
        if (e.to == t) {
          return true;
        }

        unvisited.push(e.to);
      }
    }
  }

  return false;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function that finds the maximum flow in a flow graph
 * based on Edmonds-Karp algorithm. The time complexity is O(V*E^2), where V is
 * the total number of vertex(nodes), and E is the total number of edges.
 * Detailed proof can be seen here:
 * https://brilliant.org/wiki/edmonds-karp-algorithm/
 * @param graph: The graph.
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @return: A pair. The first is the max flow. The second is the flow graph.
 */
ResultType MaxFlow(const GraphType& graph, int s, int t) {
  int n = graph.size();
  std::vector<Edge*> parent(n);

  WeightType max_flow = 0;
  GraphType flow_graph(graph);

  while (BFS(flow_graph, s, t, &parent)) {
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

using namespace std;
using namespace aaps::zhoni04;

int main(void) {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);

  GraphType graph(n);

  int u, v;
  WeightType c;
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %lld", &u, &v, &c);
    graph[u].emplace_back(u, v, c, 0, graph[v].size());
    graph[v].emplace_back(v, u, 0, 0, graph[u].size() - 1);
  }

  auto result = MaxFlow(graph, s, t);
  auto& max_flow = result.first;
  auto& flow_graph = result.second;

  int edge_num = 0;
  for (int i = 0; i < n; ++i) {
    for (auto& e : flow_graph[i]) {
      if (e.flow > 0) {
        ++edge_num;
      }
    }
  }

  printf("%d %lld %d\n", n, max_flow, edge_num);

  for (int i = 0; i < n; ++i) {
    for (auto& e : flow_graph[i]) {
      if (e.flow > 0) {
        printf("%d %d %lld\n", i, e.to, e.flow);
      }
    }
  }

  return 0;
}
