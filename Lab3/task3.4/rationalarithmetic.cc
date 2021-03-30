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
 * @class RationalNumber
 * @brief Implements a class for rational numbers. This class supports common
 * arithmetic operations, comparison operators, input, and ouput.
 */
class RationalNumber {
  using NumberType = long long;

 public:
  /**
   * @brief Initializes a default new instance of RationalNumber. The numerator
   * is 0 and the denominator is 1.
   */
  RationalNumber() : numerator_(0), denominator_(1) {}

  /**
   * @brief Initializes a new instance of RationalNumber with specified
   * numerator and denominator.
   * @param numerator: The numerator.
   * @param denominator: The denominator.
   */
  RationalNumber(NumberType numerator, NumberType denominator)
      : numerator_(numerator), denominator_(denominator) {
    Convert();
  }

  RationalNumber operator+(const RationalNumber &rhs) {
    RationalNumber result(this->numerator_ * rhs.denominator_ +
                              this->denominator_ * rhs.numerator_,
                          this->denominator_ * rhs.denominator_);
    return result;
  }

  RationalNumber operator-(const RationalNumber &rhs) {
    RationalNumber result(this->numerator_ * rhs.denominator_ -
                              this->denominator_ * rhs.numerator_,
                          this->denominator_ * rhs.denominator_);
    return result;
  }

  RationalNumber operator*(const RationalNumber &rhs) {
    RationalNumber result(this->numerator_ * rhs.numerator_,
                          this->denominator_ * rhs.denominator_);
    return result;
  }

  RationalNumber operator/(const RationalNumber &rhs) {
    RationalNumber result(this->numerator_ * rhs.denominator_,
                          this->denominator_ * rhs.numerator_);
    return result;
  }

  bool operator<(const RationalNumber &rhs) {
    auto res = (*this) - rhs;
    return res.numerator_ < 0;
  }

  bool operator>(const RationalNumber &rhs) {
    auto res = (*this) - rhs;
    return res.numerator_ > 0;
  }

  bool operator<=(const RationalNumber &rhs) {
    auto res = (*this) - rhs;
    return res.numerator_ <= 0;
  }

  bool operator>=(const RationalNumber &rhs) {
    auto res = (*this) - rhs;
    return res.numerator_ >= 0;
  }

  bool operator==(const RationalNumber &rhs) {
    return this->numerator_ == rhs.numerator_ &&
           this->denominator_ == rhs.denominator_;
  }

  bool operator!=(const RationalNumber &rhs) { return !(*this == rhs); }

  friend std::ostream &operator<<(std::ostream &output,
                                  const RationalNumber &rhs) {
    output << rhs.numerator_ << " / " << rhs.denominator_;
    return output;
  }

  friend std::istream &operator>>(std::istream &input, RationalNumber &rhs) {
    input >> rhs.numerator_ >> rhs.denominator_;
    rhs.Convert();
    return input;
  }

 private:
  NumberType GreatestCommonDivisor(NumberType a, NumberType b) {
    if (b == 0) {
      return a;
    } else {
      return GreatestCommonDivisor(b, a % b);
    }
  }

  void Convert() {
    if (numerator_ == 0 || denominator_ == 0) {
      numerator_ = 0;
      denominator_ = 1;
      return;
    }

    bool is_same_sign = (numerator_ > 0 && denominator_ > 0) ||
                        (numerator_ < 0 && denominator_ < 0);

    if (numerator_ < 0) {
      numerator_ = -numerator_;
    }

    if (denominator_ < 0) {
      denominator_ = -denominator_;
    }

    auto gcd = GreatestCommonDivisor(numerator_, denominator_);
    numerator_ /= gcd;
    denominator_ /= gcd;

    if (!is_same_sign) {
      numerator_ = -numerator_;
    }
  }

  NumberType numerator_;
  NumberType denominator_;
};

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int N;
  cin >> N;

  RationalNumber a, b;
  char op;
  for (int i = 0; i < N; ++i) {
    cin >> a >> op >> b;
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

  return 0;
}
