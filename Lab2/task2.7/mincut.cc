#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Finds a route from vertex s to vertex t by BFS.
 * @param graph: The graph, graph[i][j] means there is a vertex from i to
 * graph[i][j].
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param capacity: The capacity, capacity[u][v] stores the capacity for edge u
 * -> v.
 * @param parent: Used for store found route.
 * @return: True if found a route, otherwise false.
 */
bool BFS(const std::vector<std::vector<int>>& graph, int s, int t,
         const std::vector<std::vector<int>>& capacity,
         std::vector<int>* parent) {
  int n = graph.size();
  std::vector<bool> visited(n, false);

  std::queue<int> unvisited;
  unvisited.push(s);
  (*parent)[s] = -1;
  visited[s] = true;

  while (!unvisited.empty()) {
    int u = unvisited.front();
    unvisited.pop();

    for (int i = 0; i < graph[u].size(); ++i) {
      int v = graph[u][i];
      if (!visited[v] && capacity[u][v] > 0) {
        (*parent)[v] = u;
        if (v == t) {
          return true;
        }

        visited[v] = true;
        unvisited.push(v);
      }
    }
  }

  return false;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Updates the capacity and flow of each involved edges by given route.
 * @param parent: The route.
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param capacity: The capacity, capacity[u][v] stores the capacity for edge u
 * -> v.
 * @param flow: The flow, flow[u][v] stores the flow for edge u -> v.
 * @return: Current added flow.
 */
int Update(const std::vector<int>& parent, int s, int t,
           std::vector<std::vector<int>>* capacity,
           std::vector<std::vector<int>>* flow) {
  int this_flow = INT_MAX;
  int v = t;
  int u;
  while (v != s) {
    u = parent[v];
    this_flow = std::min(this_flow, (*capacity)[u][v]);
    v = u;
  }

  v = t;
  while (v != s) {
    u = parent[v];

    (*capacity)[u][v] -= this_flow;
    (*capacity)[v][u] += this_flow;

    (*flow)[u][v] += this_flow;
    (*flow)[v][u] -= this_flow;

    v = u;
  }

  return this_flow;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function that finds the maximum flow in a flow graph
 * based on Edmonds-Karp algorithm.
 * @param graph: The graph, graph[i][j] means there is a vertex from i to
 * graph[i][j].
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param capacity: The capacity, capacity[u][v] stores the capacity for edge u
 * -> v.
 * @param flow: The flow, flow[u][v] stores the flow for edge u -> v.
 * @return: The maximum flow.
 */
int MaxFlow(const std::vector<std::vector<int>>& graph, int s, int t,
            std::vector<std::vector<int>>* capacity,
            std::vector<std::vector<int>>* flow) {
  int n = graph.size();
  std::vector<int> parent(n, -1);
  int max_flow = 0;

  while (BFS(graph, s, t, *capacity, &parent)) {
    max_flow += Update(parent, s, t, capacity, flow);
  }

  return max_flow;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Finds all visited vertexes from a source vertex by BFS.
 * @param graph: The graph, graph[i][j] means there is a vertex from i to
 * graph[i][j].
 * @param s: The source vertex.
 * @param capacity: The capacity, capacity[u][v] stores the capacity for edge u
 * -> v.
 * @param visited: Used for store found vertexes. If vertex i can be visited,
 * then visited[i] is true; otherwise false.
 */
void BFS(const std::vector<std::vector<int>>& graph, int s,
         const std::vector<std::vector<int>>& capacity,
         std::vector<bool>* visited) {
  int n = graph.size();

  std::queue<int> unvisited;
  unvisited.push(s);
  (*visited)[s] = true;

  while (!unvisited.empty()) {
    int u = unvisited.front();
    unvisited.pop();

    for (int i = 0; i < graph[u].size(); ++i) {
      int v = graph[u][i];
      if (!(*visited)[v] && capacity[u][v] > 0) {
        (*visited)[v] = true;
        unvisited.push(v);
      }
    }
  }
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function that finds the minimal cut in a flow graph. A
 * minimal cut is a subset U of the nodes V where the sum of the capacities from
 * U to V\U is minimal.
 * @param graph: The graph, graph[i][j] means there is a vertex from i to
 * graph[i][j].
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param capacity: The capacity, capacity[u][v] stores the capacity for edge u
 * -> v.
 * @return: The subset U of the vertices such that s∈U, t∉U, and the weight of
 * edges from U to V\U is minimized.
 */
std::vector<int> MinCut(const std::vector<std::vector<int>>& graph, int s,
                        int t, std::vector<std::vector<int>>* capacity) {
  int n = graph.size();
  std::vector<std::vector<int>> flow(n, std::vector<int>(n, 0));

  MaxFlow(graph, s, t, capacity, &flow);

  std::vector<bool> visited(n, false);
  BFS(graph, s, *capacity, &visited);

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

int main(void) {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);

  std::vector<std::vector<int>> graph(n);
  std::vector<std::vector<int>> capacity(n, std::vector<int>(n, 0));

  int u, v, w;
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %d", &u, &v, &w);
    graph[u].push_back(v);
    graph[v].push_back(u);

    capacity[u][v] = w;
  }

  std::vector<int> vertices = MinCut(graph, s, t, &capacity);

  printf("%d\n", vertices.size());
  for (int i = 0; i < vertices.size(); ++i) {
    printf("%d\n", vertices[i]);
  }

  return 0;
}
