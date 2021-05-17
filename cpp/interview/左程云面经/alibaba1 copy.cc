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
  int a[len];
  int b[len];
  int c[len];

  for (int i(0); i < len; ++i) {
    a[i] = int(str[i] - 97);
    c[i] = a[i] % 26 + x;
  }

      return 0;
}