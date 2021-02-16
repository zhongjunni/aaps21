#include <algorithm>
#include <cstdio>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function to compare the order of two intervals.
 * @param a: The interval a.
 * @param b: The interval b.
 * @return True if a is before b, otherwise false.
 */
bool CompareFunc(std::vector<double> a, std::vector<double> b) {
  if (a[0] < b[0]) {
    return true;
  } else if (a[0] == b[0]) {
    return a[1] < b[1];
  }

  return false;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function to find next alternative interval which can
 * cover the give value and has the largest right value.
 * @param start: The given value.
 * @param index: The start index to find.
 * @param intervals: The intervals.
 * @return -1 if not find, otherwise the index of interval.
 */
int FindNextInterval(double start, int index,
                     const std::vector<std::vector<double>>& intervals) {
  int res = -1;
  double max_end = start;
  int len = intervals.size();
  for (int i = index; i < len; ++i) {
    if (intervals[i][0] > start) {
      break;
    }

    if (intervals[i][1] >= max_end) {
      max_end = intervals[i][1];
      res = i;
    }
  }

  return res;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function that given a set of intervals and a target
 * interval returns the smallest number of intervals required to cover the
 * target interval. Time complexity: O(nlog(n)).
 * @param interval: The target interval, length equals to two.
 * @param intervals: The set of intervals, two dimensional vector, shape: n * 2.
 * @return The possible indexes of intervals.
 */
std::vector<int> Cover(const std::vector<double>& interval,
                       const std::vector<std::vector<double>>& intervals) {
  std::vector<std::vector<double>> local_intervals(intervals);

  // Add an element to record original index.
  for (int i = 0; i < local_intervals.size(); ++i) {
    local_intervals[i].push_back(i);
  }

  // Sort operation, time complexity: O(nlog(n)).
  std::sort(local_intervals.begin(), local_intervals.end(), CompareFunc);

  double start = interval[0];
  double end = interval[1];
  std::vector<int> result;
  int index = 0;

  do {
    int next = FindNextInterval(start, index, local_intervals);
    if (next != -1) {
      result.push_back(next);
      start = local_intervals[next][1];
      index = next + 1;
    } else {
      break;
    }
  } while (start < end);

  // Convert to original index;
  for (int i = 0; i < result.size(); ++i) {
    result[i] = (int)local_intervals[result[i]][2];
  }

  return result;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

int main(void) {
  vector<double> interval(2);
  while (scanf("%lf %lf", &interval[0], &interval[1]) != EOF) {
    int n = 0;
    scanf("%d", &n);
    vector<vector<double>> intervals(n);
    for (int i = 0; i < n; ++i) {
      intervals[i].resize(2);
      scanf("%lf %lf", &intervals[i][0], &intervals[i][1]);
    }

    vector<int> result = Cover(interval, intervals);
    int len = result.size();
    if (len == 0 || intervals[result[len - 1]][1] < interval[1]) {
      printf("impossible");
    } else {
      printf("%d\n", len);
      for (int i = 0; i < len; ++i) {
        if (i != 0) {
          printf(" ");
        }
        printf("%d", result[i]);
      }
    }
    printf("\n");
  }

  return 0;
}
