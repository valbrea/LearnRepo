/*
编程题＃2： Charm Bracelet(经典背包问题)
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
Bessie has gone to the mall's jewelry store and spies a charm bracelet. Of
course, she'd like to fill it with the best charms possible from the N(1 ≤ N≤
3,402) available charms. Each charm i in the supplied list has a weight Wi(1 ≤
Wi≤ 400), a 'desirability' factor Di(1 ≤ Di≤ 100), and can be used at most once.
Bessie can only support a charm bracelet whose weight is no more than M(1 ≤ M≤
12,880).

Given that weight limit as a constraint and a list of the charms with their
weights and desirability rating, deduce the maximum possible sum of ratings.

有 N 件物品和一个容量为 M 的背包。第 i 件物品的重量是 Wi ，价值是 Di 。
求解将哪些物品装入背包可使这些物品的重量总和不超过背包容量，且价值总和最大。
输入
Line 1: Two space-separated integers: N and M
第一行：物品个数 N 和背包大小 M。

Lines 2..N+1: Line i+1 describes charm i with two space-separated integers: Wi
and Di
第二行至第 N+1 行：第 i 个物品的重量 Wi 和价值 Di 。

输出
Line 1: A single integer that is the greatest sum of charm desirabilities that
can be achieved given the weight constraints
输出一行最大价值。

样例输入
4 6
1 4
2 6
3 12
2 7
样例输出
23
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

// const int MAX_N = 3403;
// const int MAX_W = 401;
// const int MAX_D = 101;
// const int MAX_M = 12881;

struct Charm {
  int weight_, desirability_;
  Charm(int w = 0, int d = 0) : weight_(w), desirability_(d) {}
};

int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w5_2.in", "r", stdin);
#endif

  int n, m;
  cin >> n >> m;
  int *s = new int[m + 1];
  memset(s, 0, (m + 1) * sizeof(s));
  cin.ignore();
  int wi, di;
  // s(i, j) 表示有前i个charm时，重量上限为j的最高价值d_sum
  //! 情况1：如果第j个charm不放入背包，s(i, j) = s(i - 1, j)
  //! 情况2：如果第j个charm放入背包， s(i, j) = s(i - 1, j - w[i]) + d[i];
  //! 综上所述，s(i, j) = max{s(i - 1, j), s(i - 1, j - w[i]) + d[i]}
  // for(int i(1); i <= n; ++i)
  //  for(int j(1); j <= m; ++j)
  //    s(i, j) = max(s(i - 1, j), s(i - 1, j - w[i]) + d[i])
  //* 由于第一个循环中，每一个i都仅仅和i-1相关，可以利用滚动数组节省空间，
  //* 只需要数组s[j] = max(s(j), s(j - w[i]) + d[i])
  //* 但要注意在滚动数组时候，j必须从后往前更新，这样才会保证j-w[i]不会被新的值覆盖
  for (int i(1); i <= n; ++i) {
    cin >> wi >> di;
    for (int j = m; j >= wi; --j) {
      // wi必须<=背包剩余容量j，否则这个值就是非法的，跳过即可
      s[j] = max(s[j], s[j - wi] + di);
    }
  }
  

  cout << s[m] << endl;

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
