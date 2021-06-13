// #define LOCAL // 本地调试宏定义，提交代码时注释掉此行
#define STL   // STL库，不用时注释掉此行
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#ifdef STL
#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#endif

using namespace std;
typedef long long ll;

int main() {
#ifdef LOCAL
  freopen(".debug/pdd1_6_7.in", "r", stdin);
#endif

  string str;
  getline(cin, str);
  int start = 0;
  int blank = 0;
  queue<string> q;
  // 输入部分
  for (int i(0); i < str.size(); i++) {
    if (str[i] == ' ') {
      blank = i;
      q.push(str.substr(start, blank - start));
      start = blank + 1;
    } else if (i == str.size() - 1) {
      q.push(str.substr(start, str.size() - start));
    } else {
      continue;
    }
  }

  // 规则1,2
  queue<string> q2;
  while (!q.empty()) {
    string sub = q.front();
    q.pop();
    switch (sub[0]) {
    case 'a':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'e':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'i':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'o':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'u':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'A':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'E':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'I':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'O':
      sub += "pdd";
      q2.push(sub);
      break;
    case 'U':
      sub += "pdd";
      q2.push(sub);
      break;
    default:
      char first = sub[0];
      sub = sub.substr(1, sub.size() - 1);
      sub += first;
      sub += "pdd";
      q2.push(sub);
      break;
    }
  }
  // rule3
  int space = 0;
  while (!q2.empty()) {
    string sub2 = q2.front();
    q2.pop();
    ++space;
    for (int i(0); i < space; ++i) {
      sub2 += "a";
    }
    cout << sub2 << ' ';
  }
#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
