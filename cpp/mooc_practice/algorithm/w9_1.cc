/*
编程题＃1：Aggressive cows
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
Farmer John has built a new long barn, with N (2 <= N <= 100,000) stalls. The
stalls are located along a straight line at positions x1,...,xN (0 <= xi <=
1,000,000,000).

His C (2 <= C <= N) cows don't like this barn layout and become aggressive
towards each other once put into a stall. To prevent the cows from hurting each
other, FJ want to assign the cows to the stalls, such that the minimum distance
between any two of them is as large as possible. What is the largest minimum
distance?

输入
* Line 1: Two space-separated integers: N and C

* Lines 2..N+1: Line i+1 contains an integer stall location, xi

输出
* Line 1: One integer: the largest minimum distance

样例输入
5 3
1
2
8
4
9
样例输出
3

提示
OUTPUT DETAILS:

FJ can put his 3 cows in the stalls at positions 1, 4 and 8, resulting in a
minimum distance of 3.

Huge input data,scanf is recommended.

来源
USACO 2005 February Gold

todo:
N个牛棚排一条直线，C头牛，位置xi，求如何安置牛，使得任意两头牛之间的最小间距最大，并求出最大的最小间距
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
const int max_n = 100001;
int n, c;
int x[max_n];

bool Check(int gap) {
  for (int i(1); i < n; ++i) {
    if (x[i] - x[i - 1] < gap)
      return false;
    // 如果有比gap还小的间距，那就不叫作最小间距了
  }
  return true;
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w9_1.in", "r", stdin);
#endif

  cin >> n >> c;

  for (int i(0); i < n; ++i)
    cin >> x[i];
  sort(x, x + n); //从小到大排序

  // 二分，最小间距的下限是1，上限是左右两端距离/间隔数（c头牛均匀分布，只有c-1个间隔)
  int left = 1, right, mid, min_dis;
  right = x[n - 1] - x[0] / (c - 1);
  while (left <= right) {
    // 这种情况发生于当left, mid,
    // right指向同一个数时，这个数还不是目标值，则整个查找结束。
    mid = left + ((right - left) >> 1);
    if (Check(mid)) {
      // min_dis = mid;
      // 如果成功就记录一下当前间距，并往大扩展
      left = mid + 1;
    } else
      right = mid - 1;
  }
  // 终止前，如果Check(mid) == 1， 则min_dis = mid，接着left>=right
  // 如果Check(mid) == 0， 则min_dis = left - 1(上一个成功的mid);
  min_dis = left - 1;
  cout << min_dis << endl;
#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
