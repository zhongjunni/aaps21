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

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Since maybe several edges are existed between vertexes, I use multiset
 * to store the 'to' vertexes.
 */
using GraphType = std::vector<std::multiset<int>>;
using ResultType = std::pair<bool, std::vector<int>>;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements an algorithm for finding an Euler path through a graph, if
 * one exists.
 * @param graph: The graph.
 * @return: A pair. The first is a bool value to indicate if found, true if
 * found, otherwise false. The second is the found path.
 */
ResultType EulerianPath(GraphType* graph) {
  int n = graph->size();
  std::vector<int> in_degree(n, 0);
  std::vector<int> out_degree(n, 0);

  int edges_num = 0;
  int start = 0;
  for (int i = 0; i < n; ++i) {
    out_degree[i] = (*graph)[i].size();
    if (out_degree[i] != 0) {
      start = i;
    }

    edges_num += out_degree[i];

    for (auto& to : (*graph)[i]) {
      ++in_degree[to];
    }
  }

  int in_out_degree_not_equal_num = 0;
  for (int i = 0; i < n; ++i) {
    if (in_degree[i] + 1 == out_degree[i]) {
      start = i;
    }

    if (in_degree[i] != out_degree[i]) {
      ++in_out_degree_not_equal_num;
    }
  }

  std::vector<int> path;
  std::stack<int> s;
  s.push(start);
  while (!s.empty()) {
    int curr = s.top();
    if (!(*graph)[curr].empty()) {
      auto itr = (*graph)[curr].begin();
      s.push(*itr);
      (*graph)[curr].erase(itr);
    } else {
      path.push_back(curr);
      s.pop();
    }
  }

  bool find = false;

  // A directed graph has an eulerian path if and only if it is connected and
  // each vertex except 2 have the same in-degree as out-degree, and one of
  // those 2 vertices has out-degree with one greater than in-degree (this is
  // the start vertex), and the other vertex has in-degree with one greater than
  // out-degree (this is the end vertex).
  if (path.size() == edges_num + 1 &&
      (in_out_degree_not_equal_num == 0 || in_out_degree_not_equal_num == 2)) {
    find = true;
    std::reverse(path.begin(), path.end());
  }

  return std::make_pair(find, path);
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  int n, m;

  while (scanf("%d %d", &n, &m) != EOF) {
    if (n == 0 && m == 0) {
      break;
    }

    GraphType graph(n);

    int u, v;
    for (int i = 0; i < m; ++i) {
      scanf("%d %d", &u, &v);
      graph[u].insert(v);
    }

    auto result = EulerianPath(&graph);
    if (!result.first) {
      printf("Impossible\n");
    } else {
      for (int i = 0; i < result.second.size(); ++i) {
        if (i != 0) {
          printf(" ");
        }
        printf("%d", result.second[i]);
      }
      printf("\n");
    }
  }
  return 0;
}
