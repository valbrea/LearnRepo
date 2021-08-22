/*
编程题＃3：简单的整数划分问题
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 100ms 内存限制: 65536kB

描述
将正整数n 表示成一系列正整数之和，n=n1+n2+…+nk, 其中n1>=n2>=…>=nk>=1 ，k>=1 。

正整数n 的这种表示称为正整数n 的划分。正整数n 的不同的划分个数称为正整数n
的划分数。

输入
标准的输入包含若干组测试数据。每组测试数据是一个整数N(0 < N <= 50)。

输出
对于每组测试数据，输出N的划分数。

样例输入
5
样例输出
7

提示
5, 4+1, 3+2, 3+1+1, 2+2+1, 2+1+1+1, 1+1+1+1+1
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

int foo(int n, int k) {
  // n 划分处的最大数不超过k
  if (n == 1 || k == 1)
    return 1;
  else if (n < k)
    return foo(n, n);
  else if (n == k)
    return 1 + foo(n, k - 1);
  else
  // 划分中包含k， 则{k, foo(m - k, k)}
  // 划分中不包含k，则所有数都小于k, 即foo(n, k - 1);
    return foo(n - k, k) + foo(n, k - 1);
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w10_3.in", "r", stdin);
#endif

  int n;
  cin >> n;
  cout << foo(n, n) << endl;

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
