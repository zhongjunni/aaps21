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

int SwapToPalindrome(std::string& s) {
  int len = s.size();
  int l = 0, r = len - 1;
  int swaps = 0;

  while (l < r) {
    if (s[l] == s[r]) {
      ++l;
      --r;
      continue;
    }

    int ll = l + 1;
    bool find = false;
    while (ll < r) {
      if (s[ll] == s[r]) {
        find = true;
        break;
      }

      ++ll;
    }

    if (find) {
      for (int i = ll - 1; i >= l; --i) {
        char tmp = s[i + 1];
        s[i + 1] = s[i];
        s[i] = tmp;
        ++swaps;
      }

      continue;
    }

    int rr = r - 1;
    while (rr > l) {
      if (s[rr] == s[l]) {
        find = true;
        break;
      }

      --rr;
    }

    if (find) {
      for (int i = rr + 1; i <= r; ++i) {
        char tmp = s[i - 1];
        s[i - 1] = s[i];
        s[i] = tmp;
        ++swaps;
      }

      continue;
    }

    return -1;
  }

  return swaps;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  string s;
  getline(cin, s);

  for (int i = 0; i < n; ++i) {
    getline(cin, s);

    auto swaps = SwapToPalindrome(s);
    if (swaps == -1) {
      cout << "Impossible" << endl;
    } else {
      cout << swaps << endl;
    }
  }

  return 0;
}
