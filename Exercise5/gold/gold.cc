#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

int main(void) {
  int W, H;
  scanf("%d %d\n", &W, &H);

  std::vector<std::vector<char>> the_map(H, std::vector<char>(W, '#'));

  std::string line;
  int start_i, start_j;
  for (int i = 0; i < H; ++i) {
    std::getline(std::cin, line);
    for (int j = 0; j < W; ++j) {
      the_map[i][j] = line[j];
      if (line[j] == 'P') {
        start_i = i;
        start_j = j;
      }
    }
  }

  std::vector<std::vector<bool>> in_queue(H, std::vector<bool>(W, false));
  std::queue<std::pair<int, int>> unvisited;
  unvisited.push(std::pair<int, int>(start_i, start_j));
  in_queue[start_i][start_j] = true;

  int gold_count = 0;
  while (!unvisited.empty()) {
    std::pair<int, int> position = unvisited.front();
    unvisited.pop();

    if (the_map[position.first][position.second] == 'G') {
      ++gold_count;
    }

    the_map[position.first][position.second] = '#';

    char top = the_map[position.first - 1][position.second];
    char left = the_map[position.first][position.second - 1];
    char right = the_map[position.first][position.second + 1];
    char bottom = the_map[position.first + 1][position.second];

    if (top == 'T' || left == 'T' || right == 'T' || bottom == 'T') {
      continue;
    }

    if (top != '#' && !in_queue[position.first - 1][position.second]) {
      unvisited.push(std::pair<int, int>(position.first - 1, position.second));
      in_queue[position.first - 1][position.second] = true;
    }

    if (left != '#' && !in_queue[position.first][position.second - 1]) {
      unvisited.push(std::pair<int, int>(position.first, position.second - 1));
      in_queue[position.first][position.second - 1] = true;
    }

    if (right != '#' && !in_queue[position.first][position.second + 1]) {
      unvisited.push(std::pair<int, int>(position.first, position.second + 1));
      in_queue[position.first][position.second + 1] = true;
    }

    if (bottom != '#' && !in_queue[position.first + 1][position.second]) {
      unvisited.push(std::pair<int, int>(position.first + 1, position.second));
      in_queue[position.first + 1][position.second] = true;
    }
  }

  printf("%d\n", gold_count);

  return 0;
}
