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
  freopen(".debug/pdd3_6_7.in", "r", stdin);
#endif

  int n, k;
  cin >> n >> k;
  cin.ignore();
  ll a[100000];
  for (int i(0); i < n; ++i) {
    cin >> a[i];
  }
  // 要计算n-k + 1个子数组
  ll sum = 0;
  for (int i = 0; i < n - k + 1; ++i) {
    ll sub[k];
    for (int j = 0; j < k; ++j)
      sub[j] = a[i + j];
    sort(sub, sub + k);
    int left = 0;
    int right = k - 1;
    ll mid = (left + right) / 2;
    sum += sub[mid];
  }
  cout << sum << endl;
#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
