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

long long TotalZeros(long long n) {
  long long count = 0;

  long long mid, left, right;
  for (long long i = 1;; i *= 10) {
    mid = n / i;
    right = n % i;
    left = mid / 10;
    mid = mid % 10;

    if (left == 0) {
      break;
    }

    if (mid == 0) {
      count += (left - 1) * i + right + 1;
    } else {
      count += left * i;
    }
  }

  return count;
}

long long Zeros(long long n) {
  long long count = 0;

  do {
    if (n % 10 == 0) {
      ++count;
    }

    n /= 10;
  } while (n > 0);

  return count;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  long long m, n;
  while (cin >> m >> n) {
    if (m < 0) {
      break;
    }

    cout << TotalZeros(n) - TotalZeros(m) + Zeros(m) << endl;
  }

  return 0;
}
