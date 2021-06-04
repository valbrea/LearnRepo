/*
3. 食物链
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
动物王国中有三类动物A,B,C，这三类动物的食物链构成了有趣的环形。A吃B， B吃C，C吃A。

现有N个动物，以1－N编号。每个动物都是A,B,C中的一种，但是我们并不知道它到底是哪一种。

有人用两种说法对这N个动物所构成的食物链关系进行描述：

第一种说法是"1 X Y"，表示X和Y是同类。

第二种说法是"2 X Y"，表示X吃Y。

此人对N个动物，用上述两种说法，一句接一句地说出K句话，这K句话有的是真的，有的是假的。当一句话满足下列三条之一时，这句话就是假话，否则就是真话。

1）	当前的话与前面的某些真的话冲突，就是假话；

2）	当前的话中X或Y比N大，就是假话；

3）	当前的话表示X吃X，就是假话。

你的任务是根据给定的N（1 <= N <= 50,000）和K句话（0 <= K <= 100,000），输出假话的总数。

输入
第一行是两个整数N和K，以一个空格分隔。

以下K行每行是三个正整数 D，X，Y，两数之间用一个空格隔开，其中D表示说法的种类。

若D=1，则表示X和Y是同类。

若D=2，则表示X吃Y。

输出
只有一个整数，表示假话的数目。

样例输入
100 7
1 101 1
2 1 2
2 2 3
2 3 3
1 1 3
2 3 1
1 5 5

样例输出
3
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
struct Node{
  int parent_;
  int relationship_;
} node[50001];
void InitNode(int n) {
  for (int i(1); i <= n; ++i) {
    node[i].parent_ = i;  // 初始化时集合编号设为自身
    node[i].relationship_ = 0; // 自己和自己的关系是同类
    // relationship_ = 0 ---- 同类
    // relationship_ = 1 ---- 被根节点吃
    // relationship_ = 2 ---- 吃根节点
  }
}
int Find(int x) {
  
}
int main() {
#ifdef LOCAL
  freopen(".debug/w7_3.in", "r", stdin);
#endif
  // 思路见：https://blog.csdn.net/niushuai666/article/details/6981689
  int n, k;  
  cin >> n >> k;
  int d, x, y;
  int error = 0;
  while (k--) {
    // d:说法的种类， 1，x和y是同类，2是x吃y
    cin >> d >> x >> y;
    if (x > n || y > n)
      error++;
    if (x == y && d == 2)
      error++;
  }

#ifdef LOCAL
  cout << endl 
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
