#include <cmath>
#include <complex>
#include <cstdio>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class Polynomial
 * @brief Implements a polynomial which supports multiplication in O(nlog(n))
 * time complexity based on Fast Fourier Transformation (FFT).
 */
class Polynomial {
 public:
  /**
   * @brief Initializes a new instance of polynomial.
   * @param coefficients: The coefficients, coefficients[i] is the coefficient
   * of xi in the polynomial.
   */
  explicit Polynomial(const std::vector<double>& coefficients)
      : coefficients_(coefficients) {}

  /**
   * @brief Multiplies this polynomial with other polynomial. Time complexity:
   * O(nlog(n)).
   * @param other: The other polynomial.
   * @return The product of the two polynomials.
   */
  Polynomial Multiply(const Polynomial& other) {
    std::vector<std::complex<double>> a(coefficients_.begin(),
                                        coefficients_.end());
    std::vector<std::complex<double>> b(other.coefficients_.begin(),
                                        other.coefficients_.end());

    int max_degree = a.size() + b.size() - 1;
    int min_power_2 = GetMinPowerOf2(max_degree);
    a.resize(min_power_2);
    b.resize(min_power_2);

    std::vector<std::complex<double>> a_fft = FFT(a);
    std::vector<std::complex<double>> b_fft = FFT(b);
    std::vector<std::complex<double>> ab_fft(min_power_2);

    for (int i = 0; i < min_power_2; ++i) {
      ab_fft[i] = a_fft[i] * b_fft[i];
    }

    std::vector<std::complex<double>> ab_ifft = IFFT(ab_fft);
    std::vector<double> new_coefficients(max_degree);
    for (int i = 0; i < max_degree; ++i) {
      new_coefficients[i] = ab_ifft[i].real();
    }
    return Polynomial(new_coefficients);
  }

  /**
   * @brief Gets the coefficients.
   * @return The coefficients.
   */
  const std::vector<double>& coefficients() const { return coefficients_; }

 protected:
  std::vector<std::complex<double>> FFT(
      const std::vector<std::complex<double>>& coefficients) {
    int n = coefficients.size();
    if (n == 1) {
      return coefficients;
    }

    std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; ++i) {
      a0[i] = coefficients[i * 2];
      a1[i] = coefficients[i * 2 + 1];
    }

    std::vector<std::complex<double>> a0_fft = FFT(a0);
    std::vector<std::complex<double>> a1_fft = FFT(a1);

    std::vector<std::complex<double>> result(n);
    double step_angle = 2 * Polynomial::kPi / n;
    std::complex<double> w_k(1), step(cos(step_angle), sin(step_angle));

    for (int k = 0; k < n / 2; ++k) {
      result[k] = a0_fft[k] + w_k * a1_fft[k];
      result[k + n / 2] = a0_fft[k] - w_k * a1_fft[k];
      w_k *= step;
    }

    return result;
  }

  std::vector<std::complex<double>> IFFT(
      const std::vector<std::complex<double>>& coefficients) {
    int n = coefficients.size();
    if (n == 1) {
      return coefficients;
    }

    std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; ++i) {
      a0[i] = coefficients[i * 2];
      a1[i] = coefficients[i * 2 + 1];
    }

    std::vector<std::complex<double>> a0_fft = IFFT(a0);
    std::vector<std::complex<double>> a1_fft = IFFT(a1);

    std::vector<std::complex<double>> result(n);
    double step_angle = -2 * Polynomial::kPi / n;
    std::complex<double> w_k(1), step(cos(step_angle), sin(step_angle));

    for (int k = 0; k < n / 2; ++k) {
      result[k] = (a0_fft[k] + w_k * a1_fft[k]);
      // Since I use divide (each divide to 2 parts) and conquer, so here I
      // divide 2. After all calling, the result is equal to dividing by n.
      result[k] /= 2;

      result[k + n / 2] = (a0_fft[k] - w_k * a1_fft[k]);
      // Since I use divide (each divide to 2 parts) and conquer, so here I
      // divide 2. After all calling, the result is equal to dividing by n.
      result[k + n / 2] /= 2;

      w_k *= step;
    }

    return result;
  }

  int GetMinPowerOf2(int n) {
    int result = 1;
    while (result < n) {
      result = result << 1;
    }

    return result;
  }

 private:
  const double kPi = std::acos(-1);

  std::vector<double> coefficients_;
};

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;

int main(void) {
  int T;
  scanf("%d", &T);

  for (int i = 0; i < T; ++i) {
    int coefficient;

    int degree_a;
    scanf("%d", &degree_a);
    std::vector<double> c_a(degree_a + 1);
    for (int j = 0; j < degree_a + 1; ++j) {
      scanf("%d", &coefficient);
      c_a[j] = coefficient;
    }

    int degree_b;
    scanf("%d", &degree_b);
    std::vector<double> c_b(degree_b + 1);
    for (int j = 0; j < degree_b + 1; ++j) {
      scanf("%d", &coefficient);
      c_b[j] = coefficient;
    }

    Polynomial p_a(c_a), p_b(c_b);
    Polynomial product = p_a.Multiply(p_b);

    int degree = product.coefficients().size() - 1;

    printf("%d\n", degree);
    for (int j = 0; j < degree + 1; ++j) {
      if (j != 0) {
        printf(" ");
      }

      int c = round(product.coefficients()[j]);
      printf("%d", c);
    }
  }
}
