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

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Finds all visited vertexes from a source vertex by BFS.
 * @param graph: The graph, graph[i][j] means there is a vertex from i to
 * graph[i][j].
 * @param s: The source vertex.
 * @param visited: Used for store found vertexes. If vertex i can be visited,
 * then visited[i] is true; otherwise false.
 */
void BFS(const GraphType& graph, int s, std::vector<bool>* visited) {
  int n = graph.size();

  std::queue<int> unvisited;
  unvisited.push(s);
  (*visited)[s] = true;

  while (!unvisited.empty()) {
    int u = unvisited.front();
    unvisited.pop();

    for (auto& e : graph[u]) {
      if (!(*visited)[e.to] && e.flow < e.capacity) {
        (*visited)[e.to] = true;
        unvisited.push(e.to);
      }
    }
  }
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function that finds the minimal cut in a flow graph. A
 * minimal cut is a subset U of the nodes V where the sum of the capacities from
 * U to V\U is minimal. The implenmentation is based on max flow algorithm
 * according to the max-flow min-cut theorem. The time complexity is O(V*E^2),
 * where V is the total number of vertex(nodes), and E is the total number of
 * edges.
 * @param graph: The graph.
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @return: The subset U of the vertices such that s∈U, t∉U, and the weight of
 * edges from U to V\U is minimized.
 */
std::vector<int> MinCut(const GraphType& graph, int s, int t) {
  int n = graph.size();
  auto result = MaxFlow(graph, s, t);

  std::vector<bool> visited(n, false);
  BFS(result.second, s, &visited);

  std::vector<int> vertices;
  for (int i = 0; i < n; ++i) {
    if (visited[i]) {
      vertices.push_back(i);
    }
  }

  return vertices;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);

  GraphType graph(n);

  int u, v;
  WeightType w;
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %lld", &u, &v, &w);
    graph[u].emplace_back(u, v, w, 0, graph[v].size());
    graph[v].emplace_back(v, u, 0, 0, graph[u].size() - 1);
  }

  auto vertices = MinCut(graph, s, t);

  printf("%d\n", vertices.size());
  for (auto& vertice : vertices) {
    printf("%d\n", vertice);
  }

  return 0;
}
