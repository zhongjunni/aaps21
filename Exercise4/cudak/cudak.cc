#include <cstdio>
#include <cstdlib>
#include <vector>

#define MAX_DIGITS_NUM 16
#define MAX_S 136

long long dp[MAX_DIGITS_NUM][MAX_S];
long long pow10[MAX_DIGITS_NUM];

long long A, B;
int S;

void Initialize() {
  pow10[0] = 1;
  for (int i = 1; i < MAX_DIGITS_NUM; ++i) {
    pow10[i] = pow10[i - 1] * 10;
  }

  dp[0][0] = 1;
  for (int i = 1; i < MAX_DIGITS_NUM; ++i) {
    for (int j = 0; j < MAX_S; ++j) {
      if (i == 1 && j < 10) {
        dp[i][j] = 1;
        continue;
      }

      for (int k = 0; k < 10; ++k) {
        if (j - k >= 0) {
          dp[i][j] += dp[i - 1][j - k];
        }
      }
    }
  }
}

void GetDigitsNumAndFirstDigit(long long number, int* digits_num,
                               int* first_digit) {
  if (number == 0) {
    *digits_num = 1;
    *first_digit = 0;
    return;
  }

  int num = 0;
  int digit = 0;

  while (number != 0) {
    ++num;
    digit = number % 10;
    number /= 10;
  }

  *digits_num = num;
  *first_digit = digit;
}

long long GetCountByNumber(long long number, int sum) {
  if (sum < 0) {
    return 0;
  }

  if (number == 0) {
    return sum == 0;
  }

  if (number < 10) {
    return number >= sum;
  }

  int digits_num = 0;
  int first_digit = 0;
  GetDigitsNumAndFirstDigit(number, &digits_num, &first_digit);

  long long count = 0;
  for (int i = 0; i < first_digit; ++i) {
    if (sum - i >= 0) {
      count += dp[digits_num - 1][sum - i];
    }
  }

  if (sum - first_digit >= 0) {
    count += GetCountByNumber(number - first_digit * pow10[digits_num - 1],
                              sum - first_digit);
  }

  return count;
}

void Solve() {
  long long count = GetCountByNumber(B, S) - GetCountByNumber(A - 1, S);
  printf("%lld\n", count);

  if (count == 0) {
    return;
  }

  long long target_count = GetCountByNumber(A - 1, S) + 1;

  long long left = A;
  long long right = B;

  while (left <= right) {
    long long mid = (left + right) / 2;

    if (GetCountByNumber(mid, S) < target_count) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  printf("%lld\n", left);
}

int main(void) {
  scanf("%lld %lld %d", &A, &B, &S);

  Initialize();

  Solve();

  return 0;
}
