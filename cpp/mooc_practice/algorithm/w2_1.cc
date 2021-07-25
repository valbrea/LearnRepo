/*
编程题＃1： 画家问题
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
有一个正方形的墙，由N*N个正方形的砖组成，其中一些砖是白色的，另外一些砖是黄色的。
Bob是个画家，想把全部的砖都涂成黄色。但他的画笔不好使。
当他用画笔涂画第(i, j)个位置的砖时，
位置(i-1, j)、 (i+1, j)、 (i, j-1)、 (i, j+1)上的砖都会改变颜色。
请你帮助Bob计算出最少需要涂画多少块砖，才能使所有砖的颜色都变成黄色。
https://d3c33hcgiwev3.cloudfront.net/q_fFQxleEeW4giIAC5XN5A_fed1927db98dbf29b372d890bb2177cd_Screen-Shot-2015-06-22-at-9.15.40-PM.png?Expires=1627257600&Signature=Oy189oJSE~QuHdBEYxGX59DgYqEqHJ2IKEVwSY8NTD6AxU1RqCMvRjxTK2pke6EiecniYC7neWepulCUJIWF438FT1xOdK9wb-VXVTtrneoAV2Kf~YeKER8P90bIkGxP5dvFXmWVKwJ1N4FUJoxk8jlprXbLdaYz7vjO2cQsZ1c_&Key-Pair-Id=APKAJLTNE6QMUY6HBC5A
输入
第一行是个整数t(1≤t ≤20)，表示要测试的案例数。然后是t个案例。
每个案例的首行是一个整数n (1≤n ≤15)，表示墙的大小。接下来的n行表示墙的初始状态。
每一行包含n个字符。第i行的第j个字符表示位于位置(i,j)上的砖的颜色。“w”表示白砖，“y”表示黄砖。

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
#define STL   // STL库，不用时注释掉此行
#include <cmath>
#include <cstdio>
#include <cstdlib>
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
  freopen("/home/asuka/linuxcodes/cpp/mooc_practice/algorithm/.debug/w2_1.in", "r", stdin);
#endif

  /* code */

#ifdef LOCAL_DEBUG
  cout << endl 
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
