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

#define LOCAL_DEBUG // 本地调试宏定义，提交代码时注释掉此行
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
  double value_;
  Charm(int w = 0, int d = 0)
      : weight_(w), desirability_(d), value_((double)d / (double)w) {}
  friend bool operator<(Charm a, Charm b) {
    if (a.value_ != b.value_)
      // 依据单位重量的渴望度排序
      return a.value_ < b.value_;
    else
      // 否则按渴望度排序
      return a.desirability_ < b.desirability_;
  }
};

int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w5_2_2.in", "r", stdin);
#endif

  //! 这里用贪心，结果出错了
  //! 原因是如果背包剩3，有一个w = 2，d = 5,另一个w = 3, d = 6
  //! 贪心算法在计算的时候会优先把w = 2的放入背包，因为它的单位价值更高
  //! 但是结果却并不正确！！！
  int n, m;
  cin >> n >> m;
  priority_queue<Charm> max_value;
  cin.ignore();
  int wi, di;
  for (int i(1); i <= n; ++i) {
    cin >> wi >> di;
    max_value.push(Charm(wi, di));
  }
  int w_sum = 0, d_sum = 0;
  while (!max_value.empty()) {
    w_sum += max_value.top().weight_;
    d_sum += max_value.top().desirability_;
    if (w_sum < m)
      max_value.pop();
    else if (w_sum == m)
      break;
    else {
      w_sum -= max_value.top().weight_;
      d_sum -= max_value.top().desirability_;
      max_value.pop();
    }
    if (d_sum == 27210)
    cout << " ";
  }
  cout << d_sum << endl;

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
