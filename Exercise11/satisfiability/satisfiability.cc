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

std::vector<std::pair<int, int>> Preprocess(const std::string& line) {
  std::vector<std::pair<int, int>> res;

  std::stringstream ss(line);
  std::string token;
  char delim = ' ';
  while (std::getline(ss, token, delim)) {
    if (token[0] == 'v') {
      continue;
    }

    if (token[0] == '~') {
      res.emplace_back(std::make_pair(std::stoi(token.substr(2)) - 1, 2));
    } else {
      res.emplace_back(std::make_pair(std::stoi(token.substr(1)) - 1, 1));
    }
  }

  return res;
}

bool Solve(int n,
           const std::vector<std::vector<std::pair<int, int>>>& clauses) {
  for (int k = 0; k < (1 << n); ++k) {
    bool find = true;
    for (int i = 0; i < clauses.size(); ++i) {
      bool is_true = false;
      for (int j = 0; j < clauses[i].size(); ++j) {
        if ((clauses[i][j].second == 1 && ((1 << clauses[i][j].first) & k)) ||
            (clauses[i][j].second == 2 && !((1 << clauses[i][j].first) & k))) {
          is_true = true;
          break;
        }
      }

      if (!is_true) {
        find = false;
        break;
      }
    }

    if (find) {
      return true;
    }
  }

  return false;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int cases;
  cin >> cases;
  while (cases--) {
    int n, m;
    cin >> n >> m;

    string line;
    getline(cin, line);
    vector<vector<pair<int, int>>> clauses;

    for (int i = 0; i < m; ++i) {
      getline(cin, line);
      clauses.push_back(Preprocess(line));
    }

    if (Solve(n, clauses)) {
      cout << "satisfiable" << endl;
    } else {
      cout << "unsatisfiable" << endl;
    }
  }

  return 0;
}
