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

using ElementType = long long;
using VectorType = std::vector<ElementType>;
using MatrixType = std::vector<VectorType>;

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a function to calculate the value of a mod m. Time
 * complexity: O(1).
 * @param a: The a.
 * @param m: The m.
 * @return: The result. If m is less than or equal to 0, return 0 directly.
 */
ElementType Mod(ElementType a, ElementType m) {
  if (m <= 0) {
    return 0;
  }

  return (a % m + m) % m;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a method to multiply two vectors a and b. The length of two
 * vectors must be the same. Time complexity: O(n), where n is the length of the
 * vector.
 * @param a: The vector a.
 * @param b: The vector b.
 * @param moduli: The moduli.
 * @return: The value of (a[0]*b[0] + a[1]*b[1] + ... + a[n-1]*b[n-1]) % moduli.
 */
ElementType Multiply(const VectorType& a, const VectorType& b,
                     ElementType moduli) {
  ElementType result = 0;
  for (int i = 0; i < a.size(); ++i) {
    result = Mod(result + a[i] * b[i], moduli);
  }

  return result;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a method to multiply a matrix(shape: n rows, m columns) and
 * a vector(length: m). Time complexity: O(n * m).
 * @param a: The matrix.
 * @param b: The vector.
 * @param moduli: The moduli.
 * @return: A vector with length n. The i-th value is equal to Multiply(a[i], b,
 * moduli).
 */
VectorType Multiply(const MatrixType& a, const VectorType& b,
                    ElementType moduli) {
  auto a_row = a.size();
  VectorType result(a_row, 0);
  for (int i = 0; i < a_row; ++i) {
    result[i] = Multiply(a[i], b, moduli);
  }

  return result;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a method to multiply a matrix(shape: i rows, k columns) and
 * another matrix(shape: k rows, j columns). Time complexity: O(i * j * k).
 * @param a: The matrix a.
 * @param b: The matirx b.
 * @param moduli: The moduli.
 * @return: A matrix with shape: i rows, j columns.
 */
MatrixType Multiply(const MatrixType& a, const MatrixType& b,
                    ElementType moduli) {
  auto a_row = a.size();
  auto a_col = a[0].size();
  auto b_col = b[0].size();
  MatrixType result(a_row, VectorType(b_col, 0));
  for (int i = 0; i < a_row; ++i) {
    for (int j = 0; j < b_col; ++j) {
      for (int k = 0; k < a_col; ++k) {
        result[i][j] = Mod(result[i][j] + a[i][k] * b[k][j], moduli);
      }
    }
  }

  return result;
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implements a method to calculate pow of a square matrix(shape: n rows,
 * n columns). Time complexity: O(n^3 * log e), where e is the exponent.
 * @param base_square_matrix: The base square matrix.
 * @param exponent: The exponent.
 * @param moduli: The moduli.
 * @return: A square matrix with shape: n rows, n columns.
 */
MatrixType Pow(const MatrixType& base_square_matrix, ElementType exponent,
               ElementType moduli) {
  MatrixType result(base_square_matrix);
  auto dim = result.size();

  if (exponent == 0) {
    for (int i = 0; i < dim; ++i) {
      for (int j = 0; j < dim; ++j) {
        if (i != j) {
          result[i][j] = 0;
        } else {
          result[i][j] = 1;
        }
      }
    }

    return result;
  }

  if (exponent == 1) {
    for (int i = 0; i < dim; ++i) {
      for (int j = 0; j < dim; ++j) {
        result[i][j] = Mod(result[i][j], moduli);
      }
    }

    return result;
  }

  auto half = Pow(base_square_matrix, exponent / 2, moduli);
  result = Multiply(half, half, moduli);
  if (exponent % 2 == 1) {
    result = Multiply(result, base_square_matrix, moduli);
  }

  return result;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int N;
  cin >> N;

  vector<ElementType> coefficients(N + 1, 0);
  for (int i = 0; i < N + 1; ++i) {
    cin >> coefficients[i];
  }

  vector<ElementType> init_values(N + 1, 1);
  for (int i = 0; i < N; ++i) {
    cin >> init_values[i];
  }
  reverse(init_values.begin(), init_values.end());

  MatrixType base_square_matrix(N + 1, VectorType(N + 1, 0));
  base_square_matrix[0][0] = 1;
  copy(coefficients.begin(), coefficients.end(), base_square_matrix[1].begin());
  for (int i = 2; i < N + 1; ++i) {
    base_square_matrix[i][i - 1] = 1;
  }

  int Q;
  ElementType T, M;
  cin >> Q;
  while (Q--) {
    cin >> T >> M;
    if (T < N) {
      cout << Mod(init_values[N - T], M) << endl;
    } else {
      // Time complexity: O(N^3 * log T).
      auto matrix = Pow(base_square_matrix, T - N + 1, M);
      auto result = Multiply(matrix, init_values, M);
      cout << result[1] << endl;
    }
  }

  return 0;
}
