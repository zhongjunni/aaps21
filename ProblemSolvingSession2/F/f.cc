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

const int kInfinity = 1000001;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Edge
 * @brief Implements the edge, which consists of 'from' node, 'to' node, and the
 * weight.
 */
struct Edge {
  int from;
  int to;
  int weight;
};

using GraphType = std::vector<std::vector<Edge>>;

int DFS(const GraphType& graph, int curr, int prev, int prev_weight) {
  bool is_sprinkler = true;
  int downstream_weight = 0;
  for (auto& e : graph[curr]) {
    if (e.to != prev) {
      is_sprinkler = false;
      downstream_weight += DFS(graph, e.to, curr, e.weight);
    }
  }

  if (is_sprinkler) {
    return prev_weight;
  } else {
    return std::min(prev_weight, downstream_weight);
  }
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  int n, c;
  while (scanf("%d %d", &n, &c) != EOF) {
    GraphType graph(n + 1);
    Edge e;
    int u, v, w;
    for (int i = 0; i < n - 1; ++i) {
      scanf("%d %d %d", &u, &v, &w);
      e.from = u;
      e.to = v;
      e.weight = w;

      graph[e.from].push_back(e);

      e.from = v;
      e.to = u;
      graph[e.from].push_back(e);
    }

    int weight = DFS(graph, c, 0, kInfinity);
    printf("%d\n", weight);
  }

  return 0;
}
