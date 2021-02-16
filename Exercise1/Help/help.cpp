#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <class T>
void split(const string& str, T& splitted, const string& delim = " ") {
  size_t prev = 0;
  size_t curr = str.find_first_of(delim);
  while (curr != string::npos) {
    splitted.push_back(str.substr(prev, curr - prev));
    prev = curr + 1;
    curr = str.find_first_of(delim, prev);
  }
  splitted.push_back(str.substr(prev, curr - prev));
}

void get_matched_phase(vector<string>& pattern_1, vector<string>& pattern_2,
                       vector<string>& matched_phase) {
  size_t length = pattern_1.size();
  bool replaced = false;
  if (pattern_1.size() != pattern_2.size()) {
    goto not_matched;
  }

  do {
    replaced = false;

    for (int i = 0; i < length; ++i) {
      if (pattern_1[i][0] == '<' && pattern_2[i][0] != '<') {
        string to_be_replaced = pattern_1[i];

        for (int j = 0; j < length; ++j) {
          if (pattern_1[j] == to_be_replaced) {
            if (pattern_2[j][0] != '<' && pattern_2[j] != pattern_2[i]) {
              goto not_matched;
            } else {
              pattern_1[j] = pattern_2[i];
              replaced = true;
            }
          }
        }
      }

      if (pattern_2[i][0] == '<' && pattern_1[i][0] != '<') {
        string to_be_replaced = pattern_2[i];

        for (int j = 0; j < length; ++j) {
          if (pattern_2[j] == to_be_replaced) {
            if (pattern_1[j][0] != '<' && pattern_1[j] != pattern_1[i]) {
              goto not_matched;
            } else {
              pattern_2[j] = pattern_1[i];
              replaced = true;
            }
          }
        }
      }
    }
  } while (replaced);

  for (int i = 0; i < length; ++i) {
    if (pattern_1[i][0] != '<' && pattern_2[i][0] != '<' &&
        pattern_1[i] != pattern_2[i]) {
      goto not_matched;
    }
    if (pattern_1[i][0] == '<') {
      matched_phase.push_back("zhoni");
    } else {
      matched_phase.push_back(pattern_1[i]);
    }
  }
  return;

not_matched:
  matched_phase.clear();
  matched_phase.push_back("-");
}

void print_phase(const vector<string>& phase) {
  size_t length = phase.size();
  if (length == 0) {
    return;
  }

  stringstream ss;
  ss << phase[0];

  for (int i = 1; i < length; ++i) {
    ss << " " << phase[i];
  }

  cout << ss.str() << endl;
}

int main(void) {
  int n = 0;
  cin >> n;

  string str_line;
  vector<string> pattern_1;
  vector<string> pattern_2;
  vector<string> matched_phase;

  getline(cin, str_line);

  for (int i = 0; i < n; ++i) {
    getline(cin, str_line);
    pattern_1.clear();
    split(str_line, pattern_1);

    getline(cin, str_line);
    pattern_2.clear();
    split(str_line, pattern_2);

    matched_phase.clear();
    get_matched_phase(pattern_1, pattern_2, matched_phase);
    print_phase(matched_phase);
  }

  return 0;
}