#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

namespace aaps {
namespace zhoni04 {

const int kInfinity = 100000001;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Finds a path, which has the lowest cost, from vertex s to vertex t.
 * @param graph: The graph, graph[i][j] means there is a vertex from i to
 * graph[i][j].
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param cost: The cost, cost[u][v] stores the cost for edge u -> v.
 * @param capacity: The capacity, capacity[u][v] stores the capacity for edge u
 * -> v.
 * @param parent: Used for store found route.
 * @param potential: Used for store potential of each vertex.
 * @return: True if found a path, otherwise false.
 */
bool ShortestPath(const std::vector<std::vector<int>>& graph, int s, int t,
                  const std::vector<std::vector<int>>& cost,
                  const std::vector<std::vector<int>>& capacity,
                  std::vector<int>* parent, std::vector<int>* potential) {
  int n = graph.size();
  std::vector<int> distance(n, kInfinity);

  using Pair = std::pair<int, int>;
  std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> unvisited;
  unvisited.push(Pair(0, s));
  (*parent)[s] = -1;
  distance[s] = 0;

  while (!unvisited.empty()) {
    Pair p = unvisited.top();
    unvisited.pop();

    int u = p.second;
    if (distance[p.second] < p.first) {
      continue;
    }

    for (int i = 0; i < graph[u].size(); ++i) {
      int v = graph[u][i];
      if (capacity[u][v] > 0 && distance[v] > distance[u] + cost[u][v] +
                                                  (*potential)[u] -
                                                  (*potential)[v]) {
        (*parent)[v] = u;
        distance[v] =
            distance[u] + cost[u][v] + (*potential)[u] - (*potential)[v];

        unvisited.push(Pair(distance[v], v));
      }
    }
  }

  if (distance[t] != kInfinity) {
    for (int i = 0; i < n; ++i) {
      (*potential)[i] += distance[i];
    }
    return true;
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
 * @brief Implements a function that finds the maximum flow with a minmum cost
 * in a flow graph.
 * @param graph: The graph, graph[i][j] means there is a vertex from i to
 * graph[i][j].
 * @param s: The source vertex.
 * @param t: The target (sink) vertex.
 * @param cost: The cost, cost[u][v] stores the cost for edge u -> v.
 * @param capacity: The capacity, capacity[u][v] stores the capacity for edge u
 * -> v.
 * @param flow: The flow, flow[u][v] stores the flow for edge u -> v.
 * @return: A pair of value, the first value is the maximum flow and the second
 * value is minimum cost.
 */
std::pair<int, int> MaxFlow(const std::vector<std::vector<int>>& graph, int s,
                            int t, const std::vector<std::vector<int>>& cost,
                            std::vector<std::vector<int>>* capacity,
                            std::vector<std::vector<int>>* flow) {
  int n = graph.size();
  std::vector<int> parent(n, -1);
  std::vector<int> potential(n, 0);
  std::pair<int, int> maxflow_mincost(0, 0);

  while (ShortestPath(graph, s, t, cost, *capacity, &parent, &potential)) {
    int this_flow = Update(parent, s, t, capacity, flow);
    maxflow_mincost.first += this_flow;
    maxflow_mincost.second += this_flow * potential[t];
  }

  return maxflow_mincost;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;

int main(void) {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);

  std::vector<std::vector<int>> graph(n);
  std::vector<std::vector<int>> capacity(n, std::vector<int>(n, 0));
  std::vector<std::vector<int>> cost(n, std::vector<int>(n, 0));
  std::vector<std::vector<int>> flow(n, std::vector<int>(n, 0));

  int u, v, c, w;
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %d %d", &u, &v, &c, &w);
    graph[u].push_back(v);
    graph[v].push_back(u);

    capacity[u][v] = c;
    cost[u][v] = w;
    cost[v][u] = -w;
  }

  std::pair<int, int> maxflow_mincost =
      MaxFlow(graph, s, t, cost, &capacity, &flow);

  printf("%d %d\n", maxflow_mincost.first, maxflow_mincost.second);

  return 0;
}