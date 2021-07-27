/*
编程题＃1： 画家问题
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
有一个正方形的墙，由N*N个正方形的砖组成，其中一些砖是白色的，另外一些砖是黄色的。Bob是个画家，想把全部的砖都涂成黄色。但他的画笔不好使。当他用画笔涂画第(i,
j)个位置的砖时， 位置(i-1, j)、 (i+1, j)、 (i, j-1)、 (i,
j+1)上的砖都会改变颜色。请你帮助Bob计算出最少需要涂画多少块砖，才能使所有砖的颜色都变成黄色。
https://d3c33hcgiwev3.cloudfront.net/q_fFQxleEeW4giIAC5XN5A_fed1927db98dbf29b372d890bb2177cd_Screen-Shot-2015-06-22-at-9.15.40-PM.png?Expires=1627516800&Signature=kXUjD6vmUhaFavT4ejQfCYR1vFFOQOdHTnT8Xd3gZIsEXc0FlWhsqZneZTpYFU6UVPw3K-KHFe5BBBnxaESpo7tT5-JGW1QQGQGKzCqn11H8r4LwD62v-zd1JL-OQ55ofvLgfX2z3o38nY~dby2rVOhgBGW6yspQYG2fcDCBd-Q_&Key-Pair-Id=APKAJLTNE6QMUY6HBC5A

输入
第一行是个整数t(1≤t
≤20)，表示要测试的案例数。然后是t个案例。每个案例的首行是一个整数n (1≤n
≤15)，表示墙的大小。接下来的n行表示墙的初始状态。每一行包含n个字符。第i行的第j个字符表示位于位置(i,j)上的砖的颜色。“w”表示白砖，“y”表示黄砖。

输出
每个案例输出一行。如果Bob能够将所有的砖都涂成黄色，则输出最少需要涂画的砖数，否则输出“inf”。

样例输入
2
3
yyy
yyy
yyy
5
wwwww
wwwww
wwwww
wwwww
wwwww
样例输出
0
15
*/
// #define STL // STL库，不用时注释掉此行
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
// #include <string>
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

int t, n;
int wall[16][17], paint[16][17];
bool Guess() {
  // 判断喷涂是否成功
  int column, row;
  // 根据上一样的wall和paint情况,计算下一行是否需要paint，如果上一行是0黄色，下一行就要是0不涂
  for (row = 1; row < n; ++row)             // 第1到n-1行
    for (column = 1; column <= n; ++column) // 第1到n列
      paint[row + 1][column] =
          (wall[row][column] + paint[row - 1][column] + paint[row][column - 1] +
           paint[row][column] + paint[row][column + 1]) %
          2;
  // 如果最后一行的paint结果和wall[i][j]不一样，比如wall是1白色，paint是0不涂，就无法变成白色
  for (column = 1; column <= n; ++column) {
    if ((paint[n - 1][column] + paint[n][column - 1] + paint[n][column] +
         paint[n][column + 1]) %
            2 !=
        wall[n][column])
      return false;
  }
  return true;
}
inline int GetNum() {
  int num(0);
  for (int i(1); i <= n; ++i)
    for (int j(1); j <= n; ++j)
      num += (paint[i][j]);
  return num;
}
void Enum() {
  // 枚举并输出最少的喷涂数
  int column, end(0);
  int least = n * n;
  // 每次枚举前都确保第一行全为0（外面已经做过了）
  // for (column = 1; column < n; ++column)
  //   paint[1][column] = 0;
  while (end <= n) { // 当最后进位的列数大于n时，说明前n列枚举完毕
    if (Guess() == true && GetNum() < least) // 成功的话就计数
      least = GetNum();
    // 失败就找下一个排列
    paint[1][1]++; // 每次失败就向第一个数（最低位）+1
    column = 1;    // 从第一列开始
    while (paint[1][column] > 1) { // 按列进位
      paint[1][column] = 0;        // 低位置0
      column++;                    // 进位
      if (column > end)            // 记录最后一个进位的是第几列
        end = column;
      paint[1][column]++; // 高位+1
    }
  }
  if (least == n * n)
    cout << "inf" << endl;
  else
    cout << least << endl;
  return;
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("/home/asuka/linuxcodes/cpp/mooc_practice/algorithm/.debug/w2_1.in",
          "r", stdin);
#endif

  char china;
  cin >> t;
  cin.ignore();
  while (t--) {
    cin >> n;
    cin.ignore();
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 17; j++) {
        wall[i][j] = 0;
        paint[i][j] = 0;
      }
    }
    for (int i(1); i <= n; ++i) {
      for (int j(1); j <= n; ++j) {
        cin >> china;
        wall[i][j] = (china == 'y' ? 0 : 1);
      }
    }
    Enum();
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
