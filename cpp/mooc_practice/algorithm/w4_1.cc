/*
编程题＃1：集合加法
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 3000ms 内存限制: 65536kB

描述
给出2个正整数集合A = {pi | 1 <= i <= a}，B = {qj | 1 <= j <=
b}和一个正整数s。问题是：使得pi + qj = s的不同的(i, j)对有多少个。

输入
第1行是测试数据的组数n，后面跟着n组测试数据。

每组测试数据占5行，第1行是和s (1 <= s <= 10000)，第2行是一个正整数a (1 <= a <=
10000)，表示A中元素的数目。第3行是a个正整数，每个正整数不超过10000，表示A中的元素。第4行是一个正整数b
(1 <= b <=
10000)，表示B中元素的数目。第5行是b个正整数，每个正整数不超过10000，表示B中的元素。

注意：这里的集合和数学书上定义的集合有一点点区别——集合内可能包含相等的正整数。

输出
n行，每行输出对应一个输入。输出应是一个非负整数。

样例输入
2
99
2
49 49
2
50 50
11
9
1 2 3 4 5 6 7 8 9
10
10 9 8 7 6 5 4 3 2 1
样例输出
4
9
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

const int MAXA(10001), MAXB(10001);
int n, s, a, b;
int p[MAXA], q[MAXB];
int Count() {
  int count(0);
  // sort(p, p + a);
  // sort(q, q + b, greater<int>());
  for (int i(0); i < a; ++i) {
    for (int j(0); j < b; ++j) {
     if (s == p[i] + q[j])
      ++count;
    }
  }
  return count;
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w4_1.in", "r", stdin);
#endif

  cin >> n;
  cin.ignore();
  while (n--) {

    cin >> s >> a;
    for (int i(0); i < a; ++i)
      cin >> p[i];
    cin >> b;
    for (int i(0); i < b; ++i)
      cin >> q[i];
    cout << Count() << endl;
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
