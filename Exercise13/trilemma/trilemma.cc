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
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aaps {
namespace zhoni04 {

int DistanceSquare(int x1, int y1, int x2, int y2) {
  int x_diff = x1 - x2;
  int y_diff = y1 - y2;

  return x_diff * x_diff + y_diff * y_diff;
}

bool IsInSameLine(int x1, int y1, int x2, int y2, int x3, int y3) {
  return (y2 - y1) * (x3 - x2) == (y3 - y2) * (x2 - x1);
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int N;
  cin >> N;

  for (int i = 1; i <= N; ++i) {
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    cout << "Case #" << i << ": ";

    if (IsInSameLine(x1, y1, x2, y2, x3, y3)) {
      cout << "not a triangle" << endl;
      continue;
    }

    vector<int> distance_square(3);
    distance_square[0] = DistanceSquare(x1, y1, x2, y2);
    distance_square[1] = DistanceSquare(x2, y2, x3, y3);
    distance_square[2] = DistanceSquare(x1, y1, x3, y3);
    std::sort(distance_square.begin(), distance_square.end());

    if (distance_square[0] == distance_square[1] ||
        distance_square[1] == distance_square[2]) {
      cout << "isosceles ";
    } else {
      cout << "scalene ";
    }

    int sum = distance_square[0] + distance_square[1];
    if (sum > distance_square[2]) {
      cout << "acute triangle";
    } else if (sum < distance_square[2]) {
      cout << "obtuse triangle";
    } else {
      cout << "right triangle";
    }

    cout << endl;
  }

  return 0;
}
