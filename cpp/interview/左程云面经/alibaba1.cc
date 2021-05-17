#include <algorithm>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
int main() {
  string str;
  getline(cin, str);
  int x;
  cin >> x;
  cin.ignore();
  int len = str.size();

  int raw[26]; // 1
  int a[len];   // 2
  int b[len];   // 3
  int out[len]; // 4
  for (int i(0); i < 26; ++i) {
    raw[i] = i;
  }
  for (int i (0); i < len; ++i) {
    a[i] = b[i] = out[i] = 0;
  }

  a[0] = x;
  b[0] = x % 26;
  for (int i(1); i < len; ++i) {
    a[i] += raw[i] + a[i - 1];
    b[i] = a[i] % 26;
  }

  for (int i(0); i < 26; ++i) {
    out[b[i]] = i;
  }
  int input[100];
  for (int i(0); i < str.size(); ++i)
    input[i] = str[i] - 97;
  

      return 0;
}