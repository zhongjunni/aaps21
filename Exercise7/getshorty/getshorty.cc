#include <algorithm>
#include <cstdio>
#include <queue>
#include <set>
#include <utility>
#include <vector>

namespace aaps {
namespace zhoni04 {

using WeightType = double;

struct Edge {
 public:
  Edge(int s, int d, WeightType w) {
    src = s;
    dst = d;
    weight = w;
  }

  int src;
  int dst;
  WeightType weight;
};

using GraphType = std::vector<std::vector<Edge>>;

const int kInvalidNode = -1;

int GetNextNode(const std::vector<WeightType>& distance,
                const std::set<int>& candidate_nodes) {
  WeightType max_weight = -1;
  int max_node = kInvalidNode;

  for (auto itr = candidate_nodes.begin(); itr != candidate_nodes.end();
       ++itr) {
    if (distance[*itr] > max_weight) {
      max_weight = distance[*itr];
      max_node = *itr;
    }
  }

  return max_node;
}

void ShortestPath(const GraphType& graph, int start,
                  std::vector<WeightType>* distance) {
  if (distance == nullptr) {
    return;
  }

  int n = graph.size();
  distance->resize(n);
  distance->assign(n, -1);

  std::vector<bool> marked(n, false);
  std::set<int> candidate_nodes;
  (*distance)[start] = 1;
  candidate_nodes.insert(start);

  while (!candidate_nodes.empty()) {
    int curr_node = GetNextNode(*distance, candidate_nodes);
    if (curr_node == kInvalidNode || (*distance)[curr_node] == -1) {
      break;
    }

    marked[curr_node] = true;
    candidate_nodes.erase(curr_node);

    const std::vector<Edge>& edges = graph[curr_node];
    WeightType curr_weight = (*distance)[curr_node];
    int m = edges.size();
    for (int i = 0; i < m; ++i) {
      if (curr_weight * edges[i].weight > (*distance)[edges[i].dst]) {
        (*distance)[edges[i].dst] = curr_weight * edges[i].weight;
      }

      if (!marked[edges[i].dst]) {
        candidate_nodes.insert(edges[i].dst);
      }
    }
  }
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;

int main(void) {
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF) {
    if (n == 0 && m == 0) {
      break;
    }

    GraphType graph(n);

    int x, y;
    double f;
    for (int i = 0; i < m; ++i) {
      scanf("%d %d %lf", &x, &y, &f);
      graph[x].push_back(Edge(x, y, f));
      graph[y].push_back(Edge(y, x, f));
    }

    std::vector<WeightType> distance(n);
    ShortestPath(graph, 0, &distance);

    printf("%.4f\n", distance[n - 1]);
  }

  return 0;
}
