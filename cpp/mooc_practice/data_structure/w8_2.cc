/*
2. 拓扑排序
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 10000ms 内存限制: 65536kB

描述
给出一个图的结构，输出其拓扑排序序列，要求在同等条件下，编号小的顶点在前

输入
若干行整数，第一行有2个数，分别为顶点数v和弧数a，接下来有a行，每一行有2个数，分别是该条弧所关联的两个顶点编号

输出
若干个空格隔开的顶点构成的序列(用小写字母)

样例输入
6 8
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5
样例输出
v1 v3 v2 v6 v4 v5
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

int main() {
#ifdef LOCAL
  freopen(".debug/w8_2.in", "r", stdin);
#endif
  enum { kUnvisited, kVisited };
  int v, e;
  cin >> v >> e;
  vector<vector<int> > matrix(v, vector<int>(v, 0));
  vector<int> in_degree(v, 0);
  while (e--) {
    int a, b;
    cin >> a >> b;
    matrix[a - 1][b - 1] = 1;
    ++in_degree[b - 1];
  }
  int *mark = new int[v];
  priority_queue<int, vector<int>, greater<int> > q; // 要求在同等条件下，编号小的顶点在前，所以要用priority_queue
  for (int i = 0; i < v; ++i) {
    mark[i] = kUnvisited;
    if (in_degree[i] == 0) // 入度为0的顶点入队
      q.push(i);
  }
  while (!q.empty()) {
    int u = q.top(); // 获得顶部元素
    q.pop();
    mark[u] = kVisited; // 标记为visited

    for (int j(0); j < v; ++j) {
      if (matrix[u][j] != 0) {
        // matrix[u][j] = 0;
        --in_degree[j]; // 把u节点所有的出边删去，相邻顶点的入度-1；
        if (in_degree[j] == 0) {
          q.push(j); // 如果这时入度为0， 入队
        }
      }
    }
    // for (int i = 0; i < v; ++i) {
    //   if (mark[i] == kUnvisited) { // 判断图中是否有环
    //     cout << "此图有环"; // 如果有环，环中所有节点入度都不为0， 不会被访问
    //     break;
    //   }
    // }
    cout << "v" << u + 1 << ' ';
  }

#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
