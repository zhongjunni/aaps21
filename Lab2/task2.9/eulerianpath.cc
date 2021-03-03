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

using GraphType = std::vector<std::unordered_set<int>>;
using ResultType = std::pair<bool, std::vector<int>>;

ResultType EulerianPath(GraphType* graph) {
  int n = graph->size();
  std::vector<int> in_degree(n, 0);
  std::vector<int> out_degree(n, 0);

  int edges_num = 0;
  for (int i = 0; i < n; ++i) {
    out_degree[i] = (*graph)[i].size();
    edges_num += out_degree[i];
    for (auto& to : (*graph)[i]) {
      ++in_degree[to];
    }
  }

  int in_out_equal_num = 0;
  int v1 = -1;
  int v2 = -1;
  for (int i = 0; i < n; ++i) {
    if (in_degree[i] == out_degree[i]) {
      ++in_out_equal_num;
    } else if (in_degree[i] + 1 == out_degree[i]) {
      v1 = i;
    } else if (in_degree[i] == out_degree[i] + 1) {
      v2 = i;
    }
  }

  bool find = false;
  std::vector<int> path;
  if (in_out_equal_num == n && edges_num != 0 ||
      in_out_equal_num == n - 2 && v1 != -1 && v2 != -1) {
    find = true;
  }

  if (!find) {
    return std::make_pair(find, path);
  }

  std::stack<int> s;
  int curr = v1 != -1 ? v1 : 0;

  while (curr != -1) {
    while (!(*graph)[curr].empty()) {
      s.push(curr);
      auto itr = (*graph)[curr].begin();
      int next = *itr;
      (*graph)[curr].erase(itr);
      curr = next;
    }

    path.push_back(curr);
    curr = -1;

    if (!s.empty()) {
      curr = s.top();
      s.pop();
    }
  }

  if (edges_num + 1 != path.size()) {
    find = false;
  }

  std::reverse(path.begin(), path.end());
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
