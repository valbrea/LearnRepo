/*
编程题＃1： 完美覆盖
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
一张普通的国际象棋棋盘，它被分成 8 乘 8 (8 行 8 列) 的 64 个方格。设有
形状一样的多米诺牌，每张牌恰好覆盖棋盘上相邻的两个方格，即一张多米诺牌是一
张 1 行 2 列或者 2 行 1 列的牌。那么，是否能够把 32 张多米诺牌摆放到棋盘
上，使得任何两张多米诺牌均不重叠，每张多米诺牌覆盖两个方格，并且棋盘上所有的
方格都被覆盖住？我们把这样一种排列称为棋盘被多米诺牌完美覆盖。这是一个简单的
排列问题，同学们能够很快构造出许多不同的完美覆盖。但是，计算不同的完美覆盖的
总数就不是一件容易的事情了。不过，同学们 发挥自己的聪明才智，还是有可能做到的。

现在我们通过计算机编程对 3 乘 n 棋盘的不同的完美覆盖的总数进行计算。
https://d3c33hcgiwev3.cloudfront.net/nEQ6chlgEeW9xiIAC9pDjg_88db5e2d9603c4dddebde2dde3926a69_Screen-Shot-2015-06-22-at-9.30.23-PM.png?Expires=1627776000&Signature=Jw6KRmr7scHG3bq-CJ9i-QDSLa-FWkLhZhy8E-FJqFAHg4BnqOaliBoFtVPkmlEFZjiEETjVITErfBadRrxqOU-tclkU1Gx8E0i4of4P2tdXOK49S~dQ2t0i0a7VTzC5ndIXayC5pjSY5QaUQCEvG4y8yEURiNg545WY2XZrawc_&Key-Pair-Id=APKAJLTNE6QMUY6HBC5A

任务

对 3 乘 n 棋盘的不同的完美覆盖的总数进行计算。

输入
一次输入可能包含多行，每一行分别给出不同的 n 值 ( 即 3 乘 n 棋盘的列数 )。当输入
-1 的时候结束。

n 的值最大不超过 30.

输出
针对每一行的 n 值，输出 3 乘 n 棋盘的不同的完美覆盖的总数。

样例输入
2
8
12
-1
样例输出
3
153
2131
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

int F(int);
int G(int);
int F(int n) {
  // n 必为偶数
  if (n == 0)
    return 1;
  else if (n == 2)
    return 3;
  else
    return F(n - 2) + 2 * G(n - 1);
}
int G(int n) {
  // n必为奇数
  if (n == 1)
    return 1;
  return F(n - 1) + G(n - 2);
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("/home/asuka/linuxcodes/cpp/mooc_practice/algorithm/.debug/w3_1.in",
          "r", stdin);
#endif

  // !思路见https://www.zhihu.com/question/27293430/answer/36199410
  int n;
  while (cin >> n && n != -1) {
    if (n % 2 != 0)
      cout << "0" << endl;
    else
      cout << F(n) << endl;
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
