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

int CountSubstrings(const std::unordered_set<std::string>& dictionary,
                    const std::string& message) {
  std::vector<std::pair<int, int>> intervals;

  for (auto& word : dictionary) {
    int start = 0;
    while (true) {
      start = message.find(word, start);
      if (start == -1) {
        break;
      }

      intervals.emplace_back(std::make_pair(start + word.size() - 1, start));
      ++start;
    }
  }

  std::sort(intervals.begin(), intervals.end());

  int count = 0;
  int pos = -1;
  for (auto& item : intervals) {
    if (item.second > pos) {
      pos = item.first;
      ++count;
    }
  }

  return count;
}

}  // namespace zhoni04
}  // namespace aaps

using namespace aaps::zhoni04;
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  unordered_set<string> dict;
  string word;

  while (cin >> word) {
    if (word == "#") {
      break;
    }

    dict.insert(word);
  }

  stringstream ss;
  string line;
  while (cin >> line) {
    if (line == "#") {
      break;
    }

    ss << line;
    if (line.back() == '|') {
      cout << CountSubstrings(dict, ss.str()) << endl;
      ss.str(string());
    }
  }

  return 0;
}
