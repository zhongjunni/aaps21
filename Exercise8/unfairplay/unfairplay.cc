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
 * based on Edmonds-Karp algorithm.
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
  int N, M;
  while (scanf("%d", &N) != EOF) {
    if (N == -1) {
      break;
    }

    scanf("%d", &M);

    vector<int> points(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
      scanf("%d", &points[i]);
    }

    int total_vertexes = 2 + M + N;
    int source = 0;
    int sink = total_vertexes - 1;
    GraphType graph(total_vertexes);
    vector<pair<int, int>> matches(M + 1);
    int matches_without_N = M;
    int first, second;
    for (int i = 1; i <= M; ++i) {
      scanf("%d %d", &first, &second);
      matches[i] = make_pair(first, second);

      if (first == N || second == N) {
        points[N] += 2;
        --matches_without_N;
      } else {
        graph[source].emplace_back(source, i, 2, 0, graph[i].size());
        graph[i].emplace_back(i, source, 0, 0, graph[source].size() - 1);

        graph[i].emplace_back(i, first + M, 3000, 0, graph[first + M].size());
        graph[first + M].emplace_back(first + M, i, 0, 0, graph[i].size() - 1);

        graph[i].emplace_back(i, second + M, 3000, 0, graph[second + M].size());
        graph[second + M].emplace_back(second + M, i, 0, 0,
                                       graph[i].size() - 1);
      }
    }

    bool is_possible = true;
    for (int i = 1; i < N; ++i) {
      if (points[i] >= points[N]) {
        is_possible = false;
        break;
      }
    }

    if (!is_possible) {
      printf("NO\n");
      continue;
    }

    for (int i = 1; i < N; ++i) {
      graph[i + M].emplace_back(i + M, sink, points[N] - points[i] - 1, 0,
                                graph[sink].size());
      graph[sink].emplace_back(sink, i + M, 0, 0, graph[i + M].size() - 1);
    }

    auto result = MaxFlow(graph, source, sink);
    auto& max_flow = result.first;
    auto& flow_graph = result.second;
    if (max_flow != 2 * matches_without_N) {
      printf("NO\n");
      continue;
    }

    for (int i = 1; i <= M; ++i) {
      if (i != 1) {
        printf(" ");
      }

      auto& match = matches[i];
      if (match.first == N) {
        printf("0");
      } else if (match.second == N) {
        printf("2");
      } else {
        for (auto& e : flow_graph[i]) {
          if (e.to == match.second + M) {
            printf("%lld", e.flow);
          }
        }
      }
    }

    printf("\n");
  }

  return 0;
}
