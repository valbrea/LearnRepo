/*
编程题＃2：拨钟问题
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
有9个时钟，排成一个3*3的矩阵。
        |-------|    |-------|    |-------|
        |       |    |       |    |   |   |
        |---O   |    |---O   |    |   O   |
        |       |    |       |    |       |
        |-------|    |-------|    |-------|
            A            B            C
        |-------|    |-------|    |-------|
        |       |    |       |    |       |
        |   O   |    |   O   |    |   O   |
        |   |   |    |   |   |    |   |   |
        |-------|    |-------|    |-------|
            D            E            F
        |-------|    |-------|    |-------|
        |       |    |       |    |       |
        |   O   |    |   O---|    |   O   |
        |   |   |    |       |    |   |   |
        |-------|    |-------|    |-------|
            G            H            I
                       (图 1)
现在需要用最少的移动，将9个时钟的指针都拨到12点的位置。共允许有9种不同的移动。如下表所示，每个移动会将若干个时钟的指针沿顺时针方向拨动90度。
移动    影响的时钟
 1        ABDE
 2        ABC
 3        BCEF
 4        ADG
 5        BDEFH
 6        CFI
 7        DEGH
 8        GHI
 9        EFHI
    (图 2)
输入
从标准输入设备读入9个整数，表示各时钟指针的起始位置。0=12点、1=3点、2=6点、3=9点。

输出
输出一个最短的移动序列，使得9个时钟的指针都指向12点。按照移动的序号大小，输出结果。

样例输入
3 3 0
2 2 2
2 1 2
样例输出
4 5 8 9
思路：
时钟状态statu: 0, 1, 2, 3
单个顺时针移动 : (statu++) % 4;
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

int main() {
#ifdef LOCAL_DEBUG
  freopen("/home/asuka/linuxcodes/cpp/mooc_practice/algorithm/.debug/w2_2.in",
          "r", stdin);
#endif

  vector<int> clocks(9, 0);
  vector<vector<int>> move = {{0, 1, 3, 4}, {0, 1, 2},       {1, 2, 4, 5},
                              {0, 3, 6},    {1, 3, 4, 5, 7}, {2, 5, 8},
                              {3, 4, 6, 7}, {6, 7, 8},       {4, 5, 7, 8}};
  for (int i(0); i < 9; ++i)
    cin >> clocks[i];

#ifdef LOCAL_DEBUG
  cout << endl << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
