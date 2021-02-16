#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function to compare the order of two intervals.
 * @param a: The interval a.
 * @param b: The interval b.
 * @return True if a is before b, otherwise false.
 */
bool CompareFunc(std::vector<int> a, std::vector<int> b) {
  if (a[0] < b[0]) {
    return true;
  } else if (a[0] == b[0]) {
    return a[1] < b[1];
  }

  return false;
}

bool IsIntersect(int L1, int U1, int L2, int U2) {
  if (U1 < L2 || U2 < L1) {
    return false;
  }

  return true;
}

int main(void) {
  int N;
  scanf("%d", &N);

  vector<int> interval(2);
  vector<vector<int>> intervals;
  intervals.reserve(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d %d", &interval[0], &interval[1]);
    intervals.push_back(interval);
  }

  // Sort operation, time complexity: O(nlog(n)).
  std::sort(intervals.begin(), intervals.end(), CompareFunc);

  int count = 1;
  int L = intervals[0][0], U = intervals[0][1];
  for (int i = 1; i < N; ++i) {
    if (IsIntersect(L, U, intervals[i][0], intervals[i][1])) {
      L = max(L, intervals[i][0]);
      U = min(U, intervals[i][1]);
    } else {
      ++count;
      L = intervals[i][0];
      U = intervals[i][1];
    }
  }

  printf("%d\n", count);

  return 0;
}
