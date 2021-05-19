#define LOCAL // 本地调试宏定义，提交代码时注释掉此行
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
  freopen(".debug/data.in", "r", stdin);
#endif

  int a, b;
  cin >> a >> b;
  cout << a << " " << b << endl;

#ifdef LOCAL
  cout << endl << "Runtime: " << (double)clock() / CLOCKS_PER_SEC << "s\n";
#endif

  return 0;
}
