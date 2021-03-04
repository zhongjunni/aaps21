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

using GraphType = std::vector<std::vector<int>>;

void DFS(const GraphType& graph, int curr, std::vector<int>* degree,
         std::vector<bool>* marked) {
  if ((*marked)[curr]) {
    return;
  }
  (*marked)[curr] = true;

  for (auto& to : graph[curr]) {
    if ((*degree)[to] > 0) {
      --(*degree)[to];
      if ((*degree)[to] <= graph[to].size() / 2) {
        DFS(graph, to, degree, marked);
      }
    }
  }
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  int C, P, X, L;
  scanf("%d %d %d %d", &C, &P, &X, &L);

  int A, B;
  GraphType graph(C + 1);
  std::vector<int> degree(C + 1);
  for (int i = 0; i < P; ++i) {
    scanf("%d %d", &A, &B);
    graph[A].push_back(B);
    ++degree[A];

    graph[B].push_back(A);
    ++degree[B];
  }

  std::vector<bool> marked(C + 1, false);
  DFS(graph, L, &degree, &marked);

  if (marked[X]) {
    printf("leave\n");
  } else {
    printf("stay\n");
  }

  return 0;
}
