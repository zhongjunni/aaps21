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
 * @class ModularArithmetic
 * @brief Implements a class to support modular arithmetic, i.e. addition,
 * subtraction, multiplication and division (modular inverse) modulo n. The
 * modular inverse is based on Extended Euclidean algorithm:
 * https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
 */
class ModularArithmetic {
  using NumberType = long long;

 public:
  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to calculate the value of (a + b) mod m. Time
   * complexity: O(1).
   * @param a: The a.
   * @param b: The b.
   * @param m: The m.
   * @return: The result.
   */
  static NumberType Add(NumberType a, NumberType b, NumberType m) {
    return Mod(a + b, m);
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to calculate the value of (a - b) mod m. Time
   * complexity: O(1).
   * @param a: The a.
   * @param b: The b.
   * @param m: The m.
   * @return: The result.
   */
  static NumberType Subtract(NumberType a, NumberType b, NumberType m) {
    return Mod(a - b, m);
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to calculate the value of (a * b) mod m. Time
   * complexity: O(1).
   * @param a: The a.
   * @param b: The b.
   * @param m: The m.
   * @return: The result.
   */
  static NumberType Multiply(NumberType a, NumberType b, NumberType m) {
    return Mod(a * b, m);
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to calculate the value of (a*b^-1) mod m. b^-1
   * is modular inverse of b, if the modular does not exist, return -1. Time
   * complexity: O(log(min(b,m))).
   * @param a: The a.
   * @param b: The b.
   * @param m: The m.
   * @return: The result.
   */
  static NumberType Divide(NumberType a, NumberType b, NumberType m) {
    NumberType inversed;
    if (!ModularInverse(b, m, inversed)) {
      return -1;
    }

    return Mod(a * inversed, m);
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to calculate the value of a mod m. Time
   * complexity: O(1).
   * @param a: The a.
   * @param m: The m.
   * @return: The result. If m is less than or equal to 0, return 0 directly.
   */
  static NumberType Mod(NumberType a, NumberType m) {
    if (m <= 0) {
      return 0;
    }

    return (a % m + m) % m;
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to solve the modular multiplicative
   * inverse x of an integer a and modulo m such that ax = 1 (mod m). Time
   * complexity: O(log(min(a,m))).
   * @param a: The a.
   * @param m: The m.
   * @return: The modular multiplicative inverse.
   */
  static bool ModularInverse(NumberType a, NumberType m, NumberType &res) {
    NumberType x, y;
    NumberType d = ExtendedGcd(a, m, x, y);

    if (d == 1) {
      res = Mod(x, m);
      return true;
    }

    return false;
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to computes, in addition to the greatest
   * common divisor (gcd) of integers a and b, also the coefficients of B??zout's
   * identity, which are integers x and y such that ax + by = gcd(a, b). Time
   * complexity: O(log(min(a,b))).
   * @param a: The a.
   * @param b: The b.
   * @param x: The x.
   * @param y: The y.
   * @return: The greatest common divisor.
   */
  static NumberType ExtendedGcd(NumberType a, NumberType b, NumberType &x,
                                NumberType &y) {
    if (b == 0) {
      x = 1;
      y = 0;
      return a;
    }

    NumberType x1, y1;
    NumberType d = ExtendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implement a function to solve x = a (mod n), x = b (mod m) where n
   * and m are relative prime. Time complexity: O(log(min(n,m))).
   * @param a: The a.
   * @param n: The n.
   * @param b: The b.
   * @param m: The m.
   * @return: The unique solution x such that 0 ??? x < n ?? m.
   */
  static NumberType ChineseRemainder(NumberType a, NumberType n, NumberType b,
                                     NumberType m) {
    // For x = a (mod n), we assume that x = k0 * n + a.
    // For x = b (mod m), we assume that x = k1 * m + b.
    // So, k0 * n + a = k1 * m + b, which means k0 * n + (-k1) * m = b - a.
    // And we also know k2 * n + k3 * m = gcd(n, m) = 1. So we can caculate k2,
    // k3 firstly, then caculate k0.
    NumberType k2, k3;
    ExtendedGcd(n, m, k2, k3);

    NumberType k0 = Mod((b - a) * k2, m);
    NumberType x = k0 * n + a;

    return Mod(x, n * m);
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implement a function to solve x = a (mod n), x = b (mod m) where n
   * and m does not have to be relative prime. Time complexity:
   * O(log(min(n,m))).
   * @param a: The a.
   * @param n: The n.
   * @param b: The b.
   * @param m: The m.
   * @param x: The x.
   * @param K: The lcm(n,m).
   * @return: True if there exists solution, otherwise false.
   */
  static bool GeneralChineseRemainder(NumberType a, NumberType n, NumberType b,
                                      NumberType m, NumberType &x,
                                      NumberType &K) {
    // For x = a (mod n), we assume that x = k0 * n + a.
    // For x = b (mod m), we assume that x = k1 * m + b.
    // So, k0 * n + a = k1 * m + b, which means k0 * n + (-k1) * m = b - a.
    // And we also know k2 * n + k3 * m = gcd(n, m) = 1. So we can caculate k2,
    // k3 firstly, then caculate k0.
    NumberType k2, k3;
    auto d = ExtendedGcd(n, m, k2, k3);
    if (Mod(b - a, d) != 0) {
      return false;
    }

    NumberType k0 = Mod((b - a) * k2 / d, m);
    x = k0 * n + a;

    K = (n * m) / d;
    x = Mod(x, K);

    return true;
  }
};

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int T;
  cin >> T;

  long long a, n, b, m;
  for (int i = 0; i < T; ++i) {
    cin >> a >> n >> b >> m;

    long long x, K;
    if (!ModularArithmetic::GeneralChineseRemainder(a, n, b, m, x, K)) {
      cout << "no solution" << endl;
    } else {
      cout << x << " " << K << endl;
    }
  }
  return 0;
}
