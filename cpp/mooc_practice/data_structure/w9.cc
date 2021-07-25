// #define LOCAL // 本地调试宏定义，提交代码时注释掉此行
#define STL // STL库，不用时注释掉此行
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

void test(int &sum) {
  int x;
  scanf(x);
  if (x == 0)
    test(sum);
  sum = 0;
  else {
    test(sum);
    sum += x;
  }
  printf(sum);
}
int main() {
#ifdef LOCAL
  freopen(".debug/data.in", "r", stdin);
#endif
  int n, s, k, j;
  n = 10;
  s = 0;
  for (k = 1; k < n - 1; k++)
    for (j = n; j >= k; j--)
      s = s + 1;
  cout << s << endl;
#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
