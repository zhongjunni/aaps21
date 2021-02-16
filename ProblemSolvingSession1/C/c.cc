#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function that computes the longest increasing subsequence
 * in a given sequence. The algorithm is based on patience sorting. Time
 * complexity: O(nlog(n)).
 * @param sequence: The given sequence.
 * @return The indices of a longest increasing subsequences.
 */
std::vector<int> Lis(const std::vector<int>& sequence) {
  int n = sequence.size();
  std::vector<int> predecessor(n);
  std::vector<std::stack<int>> piles(n);

  int non_empty_piles = 0;

  for (int i = 0; i < n; ++i) {
    // Binary search, find a pile to put current number.
    int left = 0;
    int right = non_empty_piles - 1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (sequence[piles[mid].top()] < sequence[i]) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    piles[left].push(i);
    if (left - 1 >= 0) {
      predecessor[i] = piles[left - 1].top();
    } else {
      predecessor[i] = -1;
    }

    if (left >= non_empty_piles) {
      ++non_empty_piles;
    }
  }

  std::vector<int> result(non_empty_piles);
  int curr = piles[non_empty_piles - 1].top();

  for (int i = non_empty_piles - 1; i >= 0; --i) {
    result[i] = curr;
    curr = predecessor[curr];
  }

  return result;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace std;
using namespace aaps::zhoni04;

int main(void) {
  string s;
  cin >> s;

  int len = s.size();
  vector<int> converted_integers(len);
  for (int i = 0; i < len; ++i) {
    converted_integers[i] = s[i] - 'a';
  }

  vector<int> lis = Lis(converted_integers);

  int missing_len = 26 - lis.size();
  cout << missing_len << endl;

  return 0;
}