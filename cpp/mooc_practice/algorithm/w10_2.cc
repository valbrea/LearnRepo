/*
编程题＃2：最大公约数
来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 65536kB

描述
输入两个整数M, N，输出它们的最大公约数。

输入
输入包含若干组测试数据（不多于40000组），每行一组数据包含两个非0整数M, N

输出
对于每一组数据输出M、N的最大公约数

样例输入
2364 456
样例输出
12

提示
若M不是N的因子，则M, N的公约数必是N mod M的因子。

输入可以使用如下形式

while(cin >> M >> N) {

}
*/
#define STL   // STL库，不用时注释掉此行
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

int Gcd(int m, int n) {
  if (n == 0)
    return m;
  return Gcd (n, m % n);
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w10_2.in", "r", stdin);
#endif

  int m, n;
  while (cin >> m >> n && m != 0 && n != 0) 
    cout << Gcd(m, n) << endl;
 

#ifdef LOCAL_DEBUG
  cout << endl << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}

