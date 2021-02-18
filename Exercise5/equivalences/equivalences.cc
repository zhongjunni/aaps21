#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

#define MAX_N 20001

std::vector<int> graph[MAX_N];

// Transposed graph.
std::vector<int> t_graph[MAX_N];

std::vector<bool> visited;
std::vector<int> order;
std::vector<int> component;

void dfs(int v) {
  visited[v] = true;
  for (int i = 0; i < graph[v].size(); ++i) {
    if (!visited[graph[v][i]]) {
      dfs(graph[v][i]);
    }
  }
  order.push_back(v);
}

void t_dfs(int v) {
  visited[v] = true;
  component.push_back(v);
  for (int i = 0; i < t_graph[v].size(); ++i) {
    if (!visited[t_graph[v][i]]) {
      t_dfs(t_graph[v][i]);
    }
  }
}

void in_out_degree(int *in_degree, int *out_degree) {
  int in = 0;
  int out = 0;

  std::set<int> c_set(component.begin(), component.end());

  for (int i = 0; i < component.size(); ++i) {
    for (int j = 0; j < graph[component[i]].size(); ++j) {
      if (c_set.find(graph[component[i]][j]) == c_set.end()) {
        ++out;
      }
    }

    for (int j = 0; j < t_graph[component[i]].size(); ++j) {
      if (c_set.find(t_graph[component[i]][j]) == c_set.end()) {
        ++in;
      }
    }
  }

  *in_degree = in;
  *out_degree = out;
}

int main(void) {
  int cases;
  scanf("%d", &cases);
  for (int i = 0; i < cases; ++i) {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int j = 0; j < n; ++j) {
      graph[j].clear();
      t_graph[j].clear();
    }

    order.clear();
    component.clear();

    int s1, s2;
    for (int j = 0; j < m; ++j) {
      scanf("%d %d", &s1, &s2);
      graph[s1 - 1].push_back(s2 - 1);
      t_graph[s2 - 1].push_back(s1 - 1);
    }

    visited.assign(n, false);
    for (int j = 0; j < n; ++j) {
      if (!visited[j]) {
        dfs(j);
      }
    }

    int component_with_zero_in_degree = 0;
    int component_with_zero_out_degree = 0;
    int component_count = 0;
    visited.assign(n, false);
    for (int j = 0; j < n; ++j) {
      int v = order[n - 1 - j];
      if (!visited[v]) {
        t_dfs(v);

        int in_degree, out_degree;
        in_out_degree(&in_degree, &out_degree);
        if (in_degree == 0) {
          ++component_with_zero_in_degree;
        }

        if (out_degree == 0) {
          ++component_with_zero_out_degree;
        }

        component.clear();
        ++component_count;
      }
    }

    if (component_count == 1) {
      printf("0\n");
    } else {
      printf("%d\n", std::max(component_with_zero_in_degree,
                              component_with_zero_out_degree));
    }
  }

  return 0;
}
