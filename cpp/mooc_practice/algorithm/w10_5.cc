/*
编程题＃5：猴子吃桃
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 3000ms 内存限制: 65536kB

描述
    海滩上有一堆桃子，N只猴子来分。第一只猴子把这堆桃子平均分为N份，多了一个，这只猴子把多的一个扔入海中，拿走了一份。第二只猴子接着把剩下的桃子平均分成N份，又多了一个，它同样把多的一个扔入海中，拿走了一份。第三、第四、……，第N只猴子仍是最终剩下的桃子分成N份，扔掉多了的一个，并拿走一份。

    编写程序，输入猴子的数量N，输出海滩上最少的桃子数，使得每只猴子都可吃到桃子。

输入
一组整数，最后一个整数是0，表示输入结束，其余整数均大于1。

输出
对输入的每个整数N，输出当猴子数量为N时海滩上最少的桃子数。所输出的每个整数占一行。结果保证在int型范围内。

样例输入
2 4 0
样例输出
7
253
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
int n;
bool Div(int count, int p) {
  // 有count只猴子拿了桃子，还剩p个桃子
  if (count == n)
    return true;
  if (p < n || p % n != 1)
    return false;
  p -= (p / n + 1);
  return Div(++count, p);
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w10_5.in", "r", stdin);
#endif

  while (cin >> n && n != 0) {
    int peach(INF);
    for (int i(n);; ++i) {
      //  n只猴子至少n个桃子，没有上限
      if (Div(0, i)) {
        cout << i << endl;
        break;
      }
    }
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
