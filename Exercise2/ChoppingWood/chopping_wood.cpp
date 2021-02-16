#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define MAX_N 200002
int vertex[MAX_N];
int frequency[MAX_N];

int main(void) {
  int n;
  scanf("%d", &n);

  int max_integer = n + 1;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &vertex[i]);
    ++frequency[vertex[i]];
  }

  if (vertex[n - 1] != max_integer) {
    printf("Error\n");
    return 0;
  }

  priority_queue<int, vector<int>, greater<int>> leaves;
  for (int i = 1; i < max_integer; ++i) {
    if (!frequency[i]) {
      leaves.push(i);
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%d\n", leaves.top());
    leaves.pop();

    --frequency[vertex[i]];
    if (frequency[vertex[i]] == 0) {
      leaves.push(vertex[i]);
    }
  }

  return 0;
}