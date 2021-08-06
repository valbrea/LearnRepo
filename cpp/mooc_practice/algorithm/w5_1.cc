/*
编程题＃1：UNIMODAL PALINDROMIC DECOMPOSITIONS
?单调回文分解
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
A sequence of positive integers is Palindromic if it reads the same forward and
backward. For example:

23 11 15 1 37 37 1 15 11 23

1 1 2 3 4 7 7 10 7 7 4 3 2 1 1

*A Palindromic sequence is Unimodal Palindromic if the values do not decrease up
*to the middle value and then (since the sequence is palindromic) do not increase
from the middle to the end For example, the first example sequence above is NOT
Unimodal Palindromic while the second example is.

A Unimodal Palindromic sequence is a Unimodal Palindromic Decomposition of an
integer N, if the sum of the integers in the sequence is N. For example, all of
the Unimodal Palindromic Decompositions of the first few integers are given
below:

1: (1)

2: (2), (1 1)

3: (3), (1 1 1)

4: (4), (1 2 1), (2 2), (1 1 1 1)

5: (5), (1 3 1), (1 1 1 1 1)

6: (6), (1 4 1), (2 2 2), (1 1 2 1 1), (3 3),

(1 2 2 1), ( 1 1 1 1 1 1)

7: (7), (1 5 1), (2 3 2), (1 1 3 1 1), (1 1 1 1 1 1 1)

8: (8), (1 6 1), (2 4 2), (1 1 4 1 1), (1 2 2 2 1),

(1 1 1 2 1 1 1), ( 4 4), (1 3 3 1), (2 2 2 2),

(1 1 2 2 1 1), (1 1 1 1 1 1 1 1)

todo: Write a program, which computes the number of Unimodal Palindromic
todo: Decompositions of an integer.

输入
Input consists of a sequence of positive integers, one per line ending with a 0
(zero) indicating the end.

输出
For each input value except the last, the output is a line containing the input
value followed by a space, then the number of Unimodal Palindromic
Decompositions of the input value. See the example on the next page.

样例输入
2
3
4
5
6
7
8
10
23
24
131
213
92
0
样例输出
2 2
3 2
4 4
5 3
6 7
7 5
8 11
10 17
23 104
24 199
131 5010688
213 1055852590
92 331143
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

int AllPerm(int n) {
  int m = 1;
  if (n == 1)
    return 1;
  else {
    for (int i(0); i < n; ++i) {
      P
    }
  }
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w5_1.in", "r", stdin);
#endif

  int n;
  while (cin >> n && n != 0) {
    cin.ignore();
    AllPerm(n);
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
