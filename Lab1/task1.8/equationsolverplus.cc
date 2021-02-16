#include <cmath>
#include <iostream>
#include <vector>

namespace aaps {
namespace zhoni04 {

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @class EquationSolver
 * @brief Implements an equation solver based on Gauss-Jordan elimination. The
 * main idea comes from here:
 * https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
 */
class EquationSolver {
 public:
  /**
   * @brief Solves a linear algebraic equation like Ax = b. Time complexity:
   * O(n^3).
   * @param A: A two-dimensional vector to represent the coefficients of the
   * linear equation. Row length: n, Column length: m.
   * @param b: A vector to represent the b of the linear equation.
   * @param x: Used for store the solved unknown values.
   * @param where: Used for store the row index of coefficient for each solved
   * value.
   * @return 0 for no solution, 1 for exactly one solution, 2 for infinite
   * number of solutions.
   */
  static int Solve(const std::vector<std::vector<double>> &A,
                   const std::vector<double> &b, std::vector<double> *x,
                   std::vector<int> *where = nullptr) {
    static double epsilon = 1e-9;

    int n = A.size();
    int m = A[0].size();

    std::vector<std::vector<double>> local_A(A);
    std::vector<double> local_b(b);

    std::vector<int> local_where(m, -1);

    int row = 0, col = 0;
    while (row < n && col < m) {
      // Find pivot row.
      int pivot = row;
      for (int i = row; i < n; ++i) {
        if (std::fabs(local_A[i][col]) > std::fabs(local_A[pivot][col])) {
          pivot = i;
        }
      }

      // For current column, can not find a row, which coefficient is not zero.
      if (std::fabs(local_A[pivot][col]) < epsilon) {
        ++col;
        continue;
      }

      for (int j = col; j < m; ++j) {
        std::swap(local_A[pivot][j], local_A[row][j]);
      }
      std::swap(local_b[pivot], local_b[row]);
      local_where[col] = row;

      for (int i = 0; i < n; ++i) {
        if (i == row) {
          continue;
        }

        double ratio = local_A[i][col] / local_A[row][col];
        for (int j = col; j < m; ++j) {
          local_A[i][j] -= local_A[row][j] * ratio;
        }
        local_b[i] -= local_b[row] * ratio;
      }

      ++row;
      ++col;
    }

    std::vector<double> local_x(m, 0);
    for (int j = 0; j < m; ++j) {
      if (local_where[j] == -1) {
        continue;
      }

      local_x[j] = local_b[local_where[j]] / local_A[local_where[j]][j];
    }

    int solution_num = 1;

    for (int i = 0; i < n; ++i) {
      double sum = 0;
      for (int j = 0; j < m; ++j) {
        sum += local_x[j] * local_A[i][j];
      }

      if (std::fabs(sum - local_b[i]) > epsilon) {
        solution_num = 0;
      }
    }

    if (solution_num != 0) {
      for (int j = 0; j < m; ++j) {
        if (local_where[j] == -1) {
          solution_num = 2;
        }
      }
    }

    // After elimination, if an x is independent, its coefficient should not be
    // zero and other coefficients in that row should all be zeros. So, in this
    // step, I mark local_where as -1 for those non-independent x.
    for (int j = 0; j < m; ++j) {
      if (local_where[j] == -1) {
        continue;
      }

      int row = local_where[j];

      for (int k = 0; k < m; ++k) {
        if (k == j) {
          continue;
        }

        if (std::fabs(local_A[row][k]) > epsilon) {
          local_where[j] = -1;
        }
      }
    }

    if (x != nullptr) {
      *x = local_x;
    }

    if (where != nullptr) {
      *where = local_where;
    }

    return solution_num;
  }
};

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;

int main(void) {
  int n;
  while (std::cin >> n && (n != 0)) {
    std::vector<std::vector<double>> A(n);
    std::vector<double> b(n);
    for (int i = 0; i < n; ++i) {
      A[i].resize(n);
      for (int j = 0; j < n; ++j) {
        std::cin >> A[i][j];
      }
    }

    for (int i = 0; i < n; ++i) {
      std::cin >> b[i];
    }

    std::vector<double> x(n);
    std::vector<int> where(n, -1);
    int result = EquationSolver::Solve(A, b, &x, &where);
    if (result == 0) {
      std::cout << "inconsistent" << std::endl;
    } else if (result == 1) {
      for (int i = 0; i < n; ++i) {
        if (i != 0) {
          std::cout << " ";
        }
        std::cout << x[i];
      }
      std::cout << std::endl;

    } else if (result == 2) {
      for (int i = 0; i < n; ++i) {
        if (i != 0) {
          std::cout << " ";
        }

        if (where[i] != -1) {
          std::cout << x[i];
        } else {
          std::cout << "?";
        }
      }
      std::cout << std::endl;
    }
  }

  return 0;
}