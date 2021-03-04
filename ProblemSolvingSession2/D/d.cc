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
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aaps {
namespace zhoni04 {

const int kInfinity = 100000000;
const int kInvalidNode = -1;

struct Edge {
  int from;
  int to;
  int weight;
};

using GraphType = std::vector<std::vector<Edge>>;
using ResultType = std::pair<std::vector<int>, std::vector<int>>;

ResultType OptimalPath(const GraphType& graph, int start) {
  int n = graph.size();

  std::vector<int> distance(n, -kInfinity);
  std::vector<int> parent(n, kInvalidNode);

  distance[start] = 0;
  parent[start] = start;

  for (int i = 0; i < n; ++i) {
    bool update = false;

    for (int u = 0; u < n; ++u) {
      if (distance[u] == -kInfinity) {
        continue;
      }

      for (auto& e : graph[u]) {
        if (distance[e.to] < distance[u] + e.weight) {
          distance[e.to] = distance[u] + e.weight;
          parent[e.to] = u;
          update = true;
        }
      }
    }

    if (!update) {
      break;
    }
  }

  return std::make_pair(distance, parent);
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  int V, E;
  scanf("%d %d\n", &V, &E);
  std::vector<bool> is_construction_site(V, false);
  char c;
  for (int i = 0; i < V; ++i) {
    scanf("%c", &c);
    if (c == 'X') {
      is_construction_site[i] = true;
    }
  }

  GraphType graph(V);
  Edge e;

  for (int i = 0; i < E; ++i) {
    scanf("%d %d", &e.from, &e.to);
    if (is_construction_site[e.to]) {
      e.weight = 1;
    } else {
      e.weight = -1;
    }
    graph[e.from].push_back(e);
  }

  auto result = OptimalPath(graph, 0);

  auto& happiness = result.first;
  printf("%d\n", happiness[V - 1] + 1);

  return 0;
}
