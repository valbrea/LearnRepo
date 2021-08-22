/*
编程题＃4：Minecraft
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 65536kB

描述
Minecraft是一个几乎无所不能的沙盒游戏，玩家可以利用游戏内的各种资源进行创造，搭建自己的世界。
在Minecraft中，基本的建筑元素是边长为1个单位的立方体，Tony想用N个这种小立方体搭建一个长方体，并用他珍藏已久的贴纸对其进行装饰。如果一张贴纸可以贴满小立方体的一个面。那么，他需要用掉多少张贴纸呢？

输入
输入的第一行是测试样例的数目C。剩下的C行，每行有一个整数N，表示小明所拥有的小立方体的个数。N不会超过1000。

输出
你需要输出每个测试样例中，小明最少用掉的贴纸有多少张。

样例输入
5
9
10
26
27
100
样例输出
30
34
82
54
130
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

int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w10_4.in", "r", stdin);
#endif

  int c;
  cin >> c;
  while (c--) {
    int n;
    cin >> n;
    int sum(0), min_cube(INF);
    int x, y, z;
    for (x = 1; x <= n; ++x)
      if (n % x == 0)
        for (y = 1; y <= n / x; ++y)
          if (n % (x * y) == 0) {
            z = n / (x * y);
            sum = 2 * (x * y + y * z + x * z);
            if (sum < min_cube)
              min_cube = sum;
          }
    cout << min_cube << endl;
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
