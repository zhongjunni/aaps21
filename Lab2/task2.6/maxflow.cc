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

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;

int main(void) {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);

  std::vector<std::vector<int>> graph(n);
  std::vector<std::vector<int>> capacity(n, std::vector<int>(n, 0));
  std::vector<std::vector<int>> flow(n, std::vector<int>(n, 0));

  int u, v, c;
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %d", &u, &v, &c);
    graph[u].push_back(v);
    graph[v].push_back(u);

    capacity[u][v] = c;
  }

  int max_flow = MaxFlow(graph, s, t, &capacity, &flow);

  std::vector<std::pair<int, int>> edges;
  for (u = 0; u < n; ++u) {
    for (v = 0; v < n; ++v) {
      if (flow[u][v] > 0) {
        edges.push_back(std::pair<int, int>(u, v));
      }
    }
  }

  printf("%d %d %d\n", n, max_flow, edges.size());

  for (int i = 0; i < edges.size(); ++i) {
    u = edges[i].first;
    v = edges[i].second;
    printf("%d %d %d\n", u, v, flow[u][v]);
  }

  return 0;
}
