#include <algorithm>
#include <cstdio>

using namespace std;

#define MAX_M 41
#define MAX_DISTANCE 1001

int distances[MAX_M];
int lowest_height[MAX_M][MAX_DISTANCE];
char direction[MAX_M][MAX_DISTANCE];

void find_optimal_solution(int steps, int total_distance) {
  for (int i = 0; i < steps; ++i) {
    for (int j = 0; j < total_distance; ++j) {
      lowest_height[i][j] = MAX_DISTANCE;
    }
  }
}

int main(void) {
  int N, M, total_distance;
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &M);
    total_distance = 0;

    for (int j = 0; j < M; ++j) {
      scanf("%d", &distances[j]);
      total_distance += distances[j];
    }

    find_optimal_solution(M, total_distance);
  }

  return 0;
}