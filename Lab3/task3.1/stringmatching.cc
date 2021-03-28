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
 * @brief Implements a function for finding a vector pi of length n, where pi[i]
 * is the length of the longest proper prefix of the substring s[0…i]
 * which is also a suffix of this substring. This implementation refers
 * algorithm from here: https://cp-algorithms.com/string/prefix-function.html
 * @param s: The string.
 * @param pi: The found vector.
 */
void PrefixFunction(const std::string& pattern, std::vector<int>* pi) {
  int len = pattern.size();
  for (int i = 1; i < len; ++i) {
    int j = (*pi)[i - 1];
    while (pattern[i] != pattern[j] && j > 0) {
      j = (*pi)[j - 1];
    }

    if (pattern[i] == pattern[j]) {
      (*pi)[i] = j + 1;
    } else {
      (*pi)[i] = 0;
    }
  }
}

/**
 * @author Zhongjun Ni (LiU-ID: zhoni04)
 * @brief Implement a function based on KMP algorithm that given a text string
 * and a pattern finds all matches of the pattern in the text string. Time
 * complexity: O(text + pattern).
 * @param pattern: The pattern string.
 * @param text: The text string.
 * @return: All matched positions in the text string.
 */
std::vector<int> Find(const std::string& pattern, const std::string& text) {
  std::vector<int> result;
  int len_p = pattern.size();
  int len_t = text.size();

  if (len_p > len_t) {
    return result;
  }
  result.reserve(len_t - len_p + 1);

  std::vector<int> pi(len_p, 0);
  PrefixFunction(pattern, &pi);

  int p_idx = 0;
  for (int i = 0; i < len_t;) {
    if (pattern[p_idx] == text[i]) {
      ++i;
      ++p_idx;

      if (p_idx == len_p) {
        result.push_back(i - p_idx);
        p_idx = pi[p_idx - 1];
      }
    } else {
      if (p_idx == 0) {
        ++i;
      } else {
        p_idx = pi[p_idx - 1];
      }
    }
  }

  return result;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  string pattern, text;
  while (getline(cin, pattern)) {
    getline(cin, text);
    auto positions = Find(pattern, text);
    for (int i = 0; i < positions.size(); ++i) {
      if (i != 0) {
        cout << " ";
      }
      cout << positions[i];
    }
    cout << endl;
  }

  return 0;
}
