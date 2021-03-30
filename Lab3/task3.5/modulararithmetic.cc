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
 * @class Modulo
 * @brief Implements a class to support modular arithmetic, i.e. addition,
 * subtraction, multiplication and division (modular inverse) modulo n. The
 * modular inverse is based on Extended Euclidean algorithm:
 * https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
 */
class Modulo {
  using NumberType = long long;

 public:
  /**
   * @brief Initializes a default new instance of Modulo. Both the number and
   * the modulus are 0.
   */
  Modulo() : number_(0), modulus_(0) {}

  /**
   * @brief Initializes a new instance of Modulo with specified number and
   * modulus.
   * @param number: The number.
   * @param modulus: The modulus.
   */
  Modulo(NumberType number, NumberType modulus)
      : number_(number), modulus_(modulus) {
    if (modulus_ > 0) {
      if (number_ < 0) {
        number_ = number_ % modulus_ + modulus_;
      } else {
        number_ = number_ % modulus_;
      }
    }
  }

  Modulo operator+(const Modulo &rhs) {
    Modulo result(this->number_ + rhs.number_, this->modulus_);
    return result;
  }

  Modulo operator-(const Modulo &rhs) {
    Modulo result(this->number_ - rhs.number_, this->modulus_);
    return result;
  }

  Modulo operator*(const Modulo &rhs) {
    Modulo result(this->number_ * rhs.number_, this->modulus_);
    return result;
  }

  Modulo operator/(const Modulo &rhs) {
    auto inverse = rhs.Inverse();
    Modulo result(this->number_ * inverse.number_, inverse.modulus_);
    return result;
  }

  friend std::ostream &operator<<(std::ostream &output, const Modulo &rhs) {
    if (rhs.modulus_ == 0) {
      output << "-1";
    } else {
      output << rhs.number_;
    }

    return output;
  }

 private:
  Modulo Inverse() const {
    NumberType x, y;
    NumberType g = ExtendedGreatestCommonDivisor(number_, modulus_, x, y);

    Modulo result;
    if (g == 1) {
      x = (x % modulus_ + modulus_) % modulus_;
      result.number_ = x;
      result.modulus_ = modulus_;
    }

    return result;
  }

  NumberType ExtendedGreatestCommonDivisor(NumberType a, NumberType b,
                                           NumberType &x, NumberType &y) const {
    if (b == 0) {
      x = 1;
      y = 0;
      return a;
    }

    NumberType x1, y1;
    NumberType d = ExtendedGreatestCommonDivisor(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
  }

  NumberType number_;
  NumberType modulus_;
};

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  long long n;
  int t;

  while (cin >> n >> t) {
    if (n == 0 && t == 0) {
      break;
    }

    long long x, y;
    char op;
    for (int i = 0; i < t; ++i) {
      cin >> x >> op >> y;
      Modulo a(x, n);
      Modulo b(y, n);

      switch (op) {
        case '+':
          cout << a + b << endl;
          break;

        case '-':
          cout << a - b << endl;
          break;

        case '*':
          cout << a * b << endl;
          break;

        case '/':
          cout << a / b << endl;
          break;

        default:
          break;
      }
    }
  }

  return 0;
}
