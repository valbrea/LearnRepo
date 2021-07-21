/*
3. Finding Nemo
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 2000ms 内存限制: 65536kB

描述
Nemo is a naughty boy. One day he went into the deep sea all by himself. Unfortunately, he became lost and couldn't find his way home. Therefore, he sent a signal to his father, Marlin, to ask for help.

After checking the map, Marlin found that the sea is like a labyrinth with walls and doors. All the walls are parallel to the X-axis or to the Y-axis. The thickness of the walls are assumed to be zero.

All the doors are opened on the walls and have a length of 1. Marlin cannot go through a wall unless there is a door on the wall. Because going through a door is dangerous (there may be some virulent medusas near the doors), Marlin wants to go through as few doors as he could to find Nemo.

Figure-1 shows an example of the labyrinth and the path Marlin went through to find Nemo.
*https://d3c33hcgiwev3.cloudfront.net/kKzgSRfgEeWrviIACueUPA_240c0a8cd00474417107ae5b7d4f2a14_Screen-Shot-2015-06-20-at-11.35.44-PM.png?Expires=1626480000&Signature=Nj-3yLOASMRf6AZkl1IWdIgvXH2iGSbVB0S3irHHFJ9~agxQ6dy29DerC0omtXaHLgOV7IHKPFFi20sGp3AGF66TxMvtea2boLk~NjQG3mVahhFN9fTln3G~vuy-7DfWg-Kd20Ue5RDnI0eLmtb42YpBEDyb0qHK9lHwikTfin4_&Key-Pair-Id=APKAJLTNE6QMUY6HBC5A
We assume Marlin's initial position is at (0, 0). Given the position of Nemo and the configuration of walls and doors, please write a program to calculate the minimum number of doors Marlin has to go through in order to reach Nemo.

输入
The input consists of several test cases. Each test case is started by two non-negative integers M and N. M represents the number of walls in the labyrinth and N represents the number of doors. 

Then follow M lines, each containing four integers that describe a wall in the following format: 

x y d t 

(x, y) indicates the lower-left point of the wall, d is the direction of the wall -- 0 means it's parallel to the X-axis and 1 means that it's parallel to the Y-axis, and t gives the length of the wall. 

The coordinates of two ends of any wall will be in the range of [1,199]. 

Then there are N lines that give the description of the doors: 

x y d 

x, y, d have the same meaning as the walls. As the doors have fixed length of 1, t is omitted. 

The last line of each case contains two positive float numbers: 

f1 f2 

(f1, f2) gives the position of Nemo. And it will not lie within any wall or door. 

A test case of M = -1 and N = -1 indicates the end of input, and should not be processed.

输出
For each test case, in a separate line, please output the minimum number of doors Marlin has to go through in order to rescue his son. If he can't reach Nemo, output -1.

样例输入
8 9
1 1 1 3
2 1 1 3
3 1 1 3
4 1 1 3
1 1 0 3
1 2 0 3
1 3 0 3
1 4 0 3
2 1 1
2 2 1
2 3 1
3 1 1
3 2 1
3 3 1
1 2 0
3 3 0
4 3 1
1.5 1.5
4 0
1 1 0 1
1 1 1 1
2 1 1 1
1 2 0 1
1.5 1.7
-1 -1
样例输出
5
-1
*/
#define LOCAL // 本地调试宏定义，提交代码时注释掉此行
#define STL   // STL库，不用时注释掉此行
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
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

using namespace std;
typedef long long ll;

int main() {
#ifdef LOCAL
  freopen(".debug/w8_3.in", "r", stdin);
#endif

  /* code */

#ifdef LOCAL
  cout << endl 
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
