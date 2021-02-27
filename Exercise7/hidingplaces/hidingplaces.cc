#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

#define MAX_V 9

int row_diff[] = {-2, -2, 2, 2, -1, 1, -1, 1};
int col_diff[] = {-1, 1, -1, 1, -2, -2, 2, 2};

using Position = std::pair<int, int>;
using Pair = std::pair<Position, int>;

int main(void) {
  int n;
  std::string line;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::cin >> line;

    std::vector<std::vector<int>> board(MAX_V, std::vector<int>(MAX_V, 65));
    std::vector<std::vector<bool>> visited(MAX_V,
                                           std::vector<bool>(MAX_V, false));

    Position start = Position(8 - (line[1] - '1'), line[0] - 'a' + 1);

    std::queue<Pair> unvisited;
    unvisited.push(Pair(start, 0));
    visited[start.first][start.second] = true;
    board[start.first][start.second] = 0;
    int max_depth = 0;

    while (!unvisited.empty()) {
      Pair curr = unvisited.front();
      unvisited.pop();

      Position pos = curr.first;
      int depth = curr.second;
      if (depth > max_depth) {
        max_depth = depth;
      }

      int row = pos.first;
      int col = pos.second;

      for (int k = 0; k < 8; ++k) {
        int next_row = row + row_diff[k];
        int next_col = col + col_diff[k];

        if (next_row > 0 && next_row < MAX_V && next_col > 0 &&
            next_col < MAX_V && !visited[next_row][next_col]) {
          visited[next_row][next_col] = true;
          board[next_row][next_col] = depth + 1;
          unvisited.push(
              Pair(Position(next_row, next_col), board[next_row][next_col]));
        }
      }
    }

    std::cout << max_depth;
    std::string pos(2, 0);
    for (int row = 1; row < MAX_V; ++row) {
      for (int col = 1; col < MAX_V; ++col) {
        if (board[row][col] == max_depth) {
          pos[0] = 'a' + col - 1;
          pos[1] = '8' - row + 1;
          std::cout << ' ' << pos;
        }
      }
    }
    std::cout << std::endl;
  }

  return 0;
}
