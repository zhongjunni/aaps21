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

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class PrimeSieve
 * @brief Implements a class where the constructor takes n as an argument and
 * allows constant time queries to it whether a particular number between 0 and
 * n is a prime or not.
 */
class PrimeSieve {
 public:
  /**
   * @brief Initializes a new instance of PrimeSieve with an argument n to find
   * all primes that are less than or equal to n.
   * @param n: The n.
   */
  explicit PrimeSieve(int n)
      : count_(0), is_prime_(std::vector<bool>(n + 1, true)) {
    is_prime_[0] = false;
    is_prime_[1] = false;

    int i = 2;
    for (; i * i <= n; ++i) {
      if (is_prime_[i]) {
        ++count_;
        for (int j = i * i; j <= n; j += i) {
          is_prime_[j] = false;
        }
      }
    }

    for (; i <= n; ++i) {
      if (is_prime_[i]) {
        ++count_;
      }
    }
  }

  /**
   * @brief Query if the given value is prime. The given value must be between 0
   * ~ n, otherwise will return false directly.
   * @param value: The value.
   * @return: True if the value is prime, otherwise false.
   */
  bool IsPrime(int value) const {
    if (value < 0 || value >= is_prime_.size()) {
      return false;
    }

    return is_prime_[value];
  }

  /**
   * @brief Gets the count of prime numbers less than or equal to n.
   * @return: The count.
   */
  int count() const { return count_; }

 private:
  int count_;

  std::vector<bool> is_prime_;
};

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n, q;
  cin >> n >> q;

  PrimeSieve prime_sieve(n);
  cout << prime_sieve.count() << endl;

  int x;
  for (int i = 0; i < q; ++i) {
    cin >> x;
    if (prime_sieve.IsPrime(x)) {
      cout << "1" << endl;
    } else {
      cout << "0" << endl;
    }
  }
  return 0;
}
