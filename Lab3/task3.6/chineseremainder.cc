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
   * @brief Implements a function to calculate the value of (a + b) mod m.
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
   * @brief Implements a function to calculate the value of (a - b) mod m.
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
   * @brief Implements a function to calculate the value of (a * b) mod m.
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
   * is modular inverse of b, if the modular does not exist, return -1.
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
   * @brief Implements a function to calculate the value of a mod m.
   * @param a: The a.
   * @param m: The m.
   * @return: The result. If m is less than or equal to 0, return 0 directly. If
   * a is less than 0, return (a % m + m); otherwise return (a % m).
   */
  static NumberType Mod(NumberType a, NumberType m) {
    if (m <= 0) {
      return 0;
    }

    return a < 0 ? (a % m + m) : (a % m);
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to solve the modular multiplicative
   * inverse x of an integer a and modulo m such that ax = 1 (mod m).
   * @param a: The a.
   * @param m: The m.
   * @return: The modular multiplicative inverse.
   */
  static bool ModularInverse(NumberType a, NumberType m, NumberType &res) {
    NumberType x, y;
    NumberType d = ExtendedGcd(a, m, x, y);

    if (d == 1) {
      res = (x % m + m) % m;
      return true;
    }

    return false;
  }

  /**
   * @author Zhongjun Ni (LiU-ID: zhoni04)
   * @brief Implements a function to computes, in addition to the greatest
   * common divisor (gcd) of integers a and b, also the coefficients of Bézout's
   * identity, which are integers x and y such that ax + by = gcd(a, b).
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
   * and m are relative prime.
   * @param a: The a.
   * @param n: The n.
   * @param b: The b.
   * @param m: The m.
   * @return: The unique solution x such that 0 ≤ x < n · m.
   */
  static NumberType ChineseRemainder(NumberType a, NumberType n, NumberType b,
                                     NumberType m) {
    return -1;
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
    cout << ModularArithmetic::ChineseRemainder(a, n, b, m) << " " << n * m
         << endl;
  }
  return 0;
}
