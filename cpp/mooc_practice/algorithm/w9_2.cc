/*
编程题＃2：Yogurt factory
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB


描述
The cows have purchased a yogurt factory that makes world-famous Yucky Yogurt.
Over the next N (1 <= N <= 10,000) weeks, the price of milk and labor will
fluctuate weekly such that it will cost the company C_i (1 <= C_i <= 5,000)
cents to produce one unit of yogurt in week i. Yucky's factory, being
well-designed, can produce arbitrarily many units of yogurt each week.

Yucky Yogurt owns a warehouse that can store unused yogurt at a constant fee of
S (1 <= S <= 100) cents per unit of yogurt per week. Fortuitously, yogurt does
not spoil. Yucky Yogurt's warehouse is enormous, so it can hold arbitrarily many
units of yogurt.

Yucky wants to find a way to make weekly deliveries of Y_i (0 <= Y_i <= 10,000)
units of yogurt to its clientele (Y_i is the delivery quantity in week i). Help
Yucky minimize its costs over the entire N-week period. Yogurt produced in week
i, as well as any yogurt already in storage, can be used to meet Yucky's demand
for that week.

输入
* Line 1: Two space-separated integers, N and S.

* Lines 2..N+1: Line i+1 contains two space-separated integers: C_i and Y_i.

输出
* Line 1: Line 1 contains a single integer: the minimum total cost to satisfy
the yogurt schedule. Note that the total might be too large for a 32-bit
integer.

样例输入
4 5
88 200
89 400
97 300
91 500
样例输出
126900

提示
OUTPUT DETAILS:

In week 1, produce 200 units of yogurt and deliver all of it. In week 2, produce
700 units: deliver 400 units while storing 300 units. In week 3, deliver the 300
units that were stored. In week 4, produce and deliver 500 units.

来源
USACO 2005 March Gold
*/
#define STL // STL库，不用时注释掉此行
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

// #define LOCAL_DEBUG // 本地调试宏定义，提交代码时注释掉此行
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll INF_LL = 0x3f3f3f3f3f3f3f3f;
// todo: N为周数 [1, 10000]， S为固定的仓储价格/盒/周 [1, 100]
// todo: Ci为该周成本/盒 [1, 5000]， Yi为每周销售量 [0, 10000]
// todo：求最小化的N周总花费
const int max_n = 10001;
int n, s;
int c[max_n], y[max_n];
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w9_2.in", "r", stdin);
#endif

  cin >> n >> s;
  ll total(0);
  // 贪心， 每周的最低成本 == 生产+存储到这周最低的成本
  for (int i(0); i < n; ++i) {
    cin >> c[i] >> y[i];
    int min_cost = c[i]; // 最低成本初始化为本周生产成本
    for (int j(0); j < i; ++j) {
      // 寻找之前几周的最低成本
      min_cost = min(c[j] + s * (i - j), min_cost);
    }
    total += min_cost * y[i];
  }
  cout << total << endl;

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
