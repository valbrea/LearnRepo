/*
3. 食物链
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
动物王国中有三类动物A,B,C，这三类动物的食物链构成了有趣的环形。A吃B，
B吃C，C吃A。

现有N个动物，以1－N编号。每个动物都是A,B,C中的一种，但是我们并不知道它到底是哪一种。

有人用两种说法对这N个动物所构成的食物链关系进行描述：

第一种说法是"1 X Y"，表示X和Y是同类。

第二种说法是"2 X Y"，表示X吃Y。

此人对N个动物，用上述两种说法，一句接一句地说出K句话，这K句话有的是真的，有的是假的。当一句话满足下列三条之一时，这句话就是假话，否则就是真话。

1）	当前的话与前面的某些真的话冲突，就是假话；

2）	当前的话中X或Y比N大，就是假话；

3）	当前的话表示X吃X，就是假话。

你的任务是根据给定的N（1 <= N <= 50,000）和K句话（0 <= K <=
100,000），输出假话的总数。

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
// #define LOCAL // 本地调试宏定义，提交代码时注释掉此行
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

#define MAXN 50001
int par[MAXN * 3]; // A、B、C种类 A吃B，B吃C， C吃A

int Find(int i) {
  // return par[i] == i ? i : Find(par[i]);
  // 下面的是路径压缩的版本
  if (par[i] == i)
    return i;
  else {
    par[i] = Find(par[i]);
    return par[i];
  }
}
int main() {
#ifdef LOCAL
  freopen(".debug/w7_3.in", "r", stdin);
#endif
  // 思路1见w7_3_ref.cc：https://blog.csdn.net/niushuai666/article/details/6981689
  //* 思路2为本程序，种类并查集: https://www.luogu.com.cn/problem/solution/P2024
  int n, k;
  cin >> n >> k;
  for (int i(1); i <= n * 3; ++i) {
    par[i] = i;
    // 先把父节点设为自己
  }
  int d, x, y;
  int lies = 0; // 谎话个数
  while (k--) {
    cin >> d >> x >> y;
    if (x > n || y > n) {
      //  条件2
      lies++;
      continue;
    }

    switch (d) {
    case 1:
      //* 1 x y，表示x和y是同类，则x不能吃y且y不能吃x
      //* B中的y的根 != A中的x的根，B中x的根 != A中y的根
      //* 即，同个种类中的等价类是同类
      //* 即Find(y + n) != Find(x) && Find(x + n) != Find(y)
      if (Find(x) == Find(y + n) || Find(y) == Find(x + n))
        lies++;
      else {
        //要维护三个种类的关系
        // A：find(x) <==> find(y)
        // B: find(x + n) <==> find(y + n)
        // C： find(x + 2 * n) <==> find(y + 2 * n)
        par[Find(x)] = Find(y);
        par[Find(x + n)] = Find(y + n);
        par[Find(x + 2 * n)] = Find(y + 2 * n);
      }
      break;
    case 2:
      //* 2 x y 表示x吃y
      //* 即 Find(y + n)] = Find(x)，A中的x和B中的y是等价类
      if (Find(x) == Find(y) || Find(x + n) == Find(y))
        lies++;
      else {
        par[Find(y + n)] = Find(x);
        par[Find(y + 2 * n)] = Find(x + n);
        par[Find(y)] = Find(x + 2 * n);
      }
      break;
    default:
      cout << "error!" << endl;
      break;
    }
  }
  cout << lies << endl;

#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
