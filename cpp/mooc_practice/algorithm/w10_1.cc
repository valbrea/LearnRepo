/*
编程题＃1：垃圾炸弹
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 65536kB

描述

    2014年巴西世界杯（2014 FIFA World
Cup）开踢啦！为了方便球迷观看比赛，里约街道上很多路口都放置了的直播大屏幕，但是人群散去后总会在这些路口留下一堆垃圾。为此巴西政府决定动用一种最新发明——“垃圾炸弹”。这种“炸弹”利用最先进的量子物理技术，爆炸后产生的冲击波可以完全清除波及范围内的所有垃圾，并且不会产生任何其他不良影响。炸弹爆炸后冲击波是以正方形方式扩散的，炸弹威力（扩散距离）以d给出，表示可以传播d条街道。

    例如下图是一个d=1的“垃圾炸弹”爆炸后的波及范围。

https://d3c33hcgiwev3.cloudfront.net/imageAssetProxy.v1/AVzjeSi-EeWr0xKBkRvsQQ_291dea043d78c8237e522f46a237cf54_Screen-Shot-2015-07-12-at-10.46.41-AM.png?expiry=1629763200000&hmac=rHNKVL6BBx3_PXjiVWGf7bLR0itVdZ1sYmjyE3TJI48

    假设里约热内卢市的布局为严格的1025*1025的网格状，由于财政问题市政府只买得起一枚“垃圾炸弹”，希望你帮他们找到合适的投放地点，使得一次清除的垃圾总量最多（假设垃圾数量可以用一个非负整数表示，并且除设置大屏幕的路口以外的地点没有垃圾）。

输入
输入第一行是整数T (1 <= T <= 10)，表明有T组测试数据。

对于每一组测试数据，第一行给出“炸弹”威力d(1 <= d <= 50)。第二行给出一个数组n(1
<= n <= 20)表示设置了大屏幕(有垃圾)的路口数目。接下来n行每行给出三个数字x, y, i,
分别代表路口的坐标(x, y)以及垃圾数量i. 点坐标(x,
y)保证是有效的（区间在0到1024之间），同一坐标只会给出一次。

输出
对于每组测试数据，输出能清理垃圾最多的投放点数目，以及能够清除的垃圾总量。

样例输入
1
1
2
4 4 10
6 6 20
样例输出
1 30
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


int t, d, n;

struct Node {
  int x_, y_, g_;
} rio[21];

int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w10_1.in", "r", stdin);
#endif

  cin >> t;
  while (t--) {
    cin >> d;
    cin >> n;
    int max_x(0), max_y(0);
    for (int i(0); i < n; ++i) {
      cin >> rio[i].x_ >> rio[i].y_ >> rio[i].g_;
    }

    int max_c(0), count(0);
    for (int i(0); i < 1025; ++i)
      for (int j(0); j < 1025; ++j) {
        // 爆炸点为i,j
        int clean(0);
        for (int k(0); k < n; ++k) {
          if (i - d <= rio[k].x_ && rio[k].x_ <= i + d && j - d <= rio[k].y_ &&
              rio[k].y_ <= j + d)
            clean += rio[k].g_;
        }
        if (clean > max_c) {
          count = 1;
          max_c = clean;
        } else if (clean == max_c) {
          count++;
        }
      }
    cout << count << " " << max_c << endl;
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
