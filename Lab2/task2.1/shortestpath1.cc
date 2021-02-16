#include <climits>
#include <cstdio>
#include <queue>
#include <set>

namespace aaps {
namespace zhoni04 {

using WeightType = long long;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Edge
 * @brief Implements the edge, which consists of source node, destination node,
 * and the weight.
 */
struct Edge {
 public:
  /**
   * @brief Initializes a new instance of edge.
   * @param s: The source node.
   * @param d: The destination node.
   * @param w: The weight.
   */
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

const WeightType kInfinity = LLONG_MAX;
const int kInvalidNode = -1;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Gets the next node from candidate nodes, which has current shortest
 * distance.
 * @param distance: The distance, which stores current shortest distance of
 * between start node and other node.
 * @param candidate_nodes: The candidate nodes.
 * @return The node, which has current shortest distance. If not found, return
 * kInvalidNode.
 */
int GetNextNode(const std::vector<WeightType>& distance,
                const std::set<int>& candidate_nodes) {
  WeightType min_weight = LLONG_MAX;
  int min_node = kInvalidNode;

  for (auto itr = candidate_nodes.begin(); itr != candidate_nodes.end();
       ++itr) {
    if (distance[*itr] < min_weight) {
      min_weight = distance[*itr];
      min_node = *itr;
    }
  }

  return min_node;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implement Dijkstras algorithm to find the shortest path from one node
 * to all other nodes in a graph with non-negative edge weights.
 * @param graph: The graph, which stores edges of each node.
 * @param start: The start node.
 * @param distance: The distance, used for storing the shortest distance of
 * between start node and other node.
 * @param parent: The parent, used for storing the parent node of each node.
 */
void ShortestPath(const GraphType& graph, int start,
                  std::vector<WeightType>* distance,
                  std::vector<int>* parent = nullptr) {
  if (distance == nullptr) {
    return;
  }

  int n = graph.size();
  distance->resize(n);
  distance->assign(n, kInfinity);
  if (parent != nullptr) {
    parent->resize(n);
    parent->assign(n, -1);
  }

  std::vector<bool> marked(n, false);
  std::set<int> candidate_nodes;
  (*distance)[start] = 0;
  candidate_nodes.insert(start);
  if (parent != nullptr) {
    (*parent)[start] = start;
  }

  while (!candidate_nodes.empty()) {
    int curr_node = GetNextNode(*distance, candidate_nodes);
    if (curr_node == kInvalidNode || (*distance)[curr_node] == kInfinity) {
      break;
    }

    marked[curr_node] = true;
    candidate_nodes.erase(curr_node);

    const std::vector<Edge>& edges = graph[curr_node];
    WeightType curr_weight = (*distance)[curr_node];
    int m = edges.size();
    for (int i = 0; i < m; ++i) {
      if (curr_weight + edges[i].weight < (*distance)[edges[i].dst]) {
        (*distance)[edges[i].dst] = curr_weight + edges[i].weight;

        if (parent != nullptr) {
          (*parent)[edges[i].dst] = curr_node;
        }
      }

      if (!marked[edges[i].dst]) {
        candidate_nodes.insert(edges[i].dst);
      }
    }
  }
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

int main(void) {
  int n, m, q, s;

  while (scanf("%d %d %d %d", &n, &m, &q, &s) != EOF) {
    if (n == 0 && m == 0 && q == 0 && s == 0) {
      break;
    }

    GraphType graph(n);

    int src, dst;
    WeightType weight;
    for (int i = 0; i < m; ++i) {
      scanf("%d %d %lld", &src, &dst, &weight);
      graph[src].push_back(Edge(src, dst, weight));
    }

    std::vector<WeightType> distance(n);
    ShortestPath(graph, s, &distance);

    int qn;
    for (int i = 0; i < q; ++i) {
      scanf("%d", &qn);

      if (distance[qn] != kInfinity) {
        printf("%lld\n", distance[qn]);
      } else {
        printf("Impossible\n");
      }
    }

    printf(" \n");
  }

  return 0;
}
