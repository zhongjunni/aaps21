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

int BFS(const GraphType& graph) {
  int count = 0;

  GraphType visited(graph);
  int N = graph.size();
  int M = graph[0].size();
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      visited[i][j] = false;
    }
  }

  std::queue<std::pair<int, int>> unvisited;
  unvisited.push(std::make_pair(0, 0));
  visited[0][0] = true;
  while (!unvisited.empty()) {
    auto grid = unvisited.front();
    unvisited.pop();

    if (grid.first - 1 >= 0 && !visited[grid.first - 1][grid.second]) {
      if (graph[grid.first - 1][grid.second] == 1) {
        ++count;
      } else {
        unvisited.push(std::make_pair(grid.first - 1, grid.second));
        visited[grid.first - 1][grid.second] = true;
      }
    }

    if (grid.first + 1 < N && !visited[grid.first + 1][grid.second]) {
      if (graph[grid.first + 1][grid.second] == 1) {
        ++count;
      } else {
        unvisited.push(std::make_pair(grid.first + 1, grid.second));
        visited[grid.first + 1][grid.second] = true;
      }
    }

    if (grid.second - 1 > 0 && !visited[grid.first][grid.second - 1]) {
      if (graph[grid.first][grid.second - 1] == 1) {
        ++count;
      } else {
        unvisited.push(std::make_pair(grid.first, grid.second - 1));
        visited[grid.first][grid.second - 1] = true;
      }
    }

    if (grid.second + 1 < M && !visited[grid.first][grid.second + 1]) {
      if (graph[grid.first][grid.second + 1] == 1) {
        ++count;
      } else {
        unvisited.push(std::make_pair(grid.first, grid.second + 1));
        visited[grid.first][grid.second + 1] = true;
      }
    }
  }

  return count;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;

  GraphType graph(N + 2);
  graph[0].assign(M + 2, 0);
  string line;
  getline(cin, line);
  
  for (int i = 0; i < N; ++i) {
    getline(cin, line);
    graph[i + 1].assign(M + 2, 0);
    for (int j = 0; j < M; ++j) {
      graph[i + 1][j + 1] = line[j] - '0';
    }
  }
  graph[N + 1].assign(M + 2, 0);

  cout << BFS(graph) << endl;

  return 0;
}
