/*
编程题＃2：迷宫问题
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
定义一个二维数组：
int maze[5][5] = {
0, 1, 0, 0, 0,
0, 1, 0, 1, 0,
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
0, 0, 0, 1, 0,
};
它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。

输入
一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一解。

输出
左上角到右下角的最短路径，格式如样例所示。

样例输入
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
样例输出
(0, 0)
(1, 0)
(2, 0)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 4)
(4, 4)

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

int maze[7][7];
int visited[7][7];
struct Pos {
  int x_, y_;
  Pos *parent_;
  Pos(int x = 0, int y = 0, Pos *p = NULL) : x_(x), y_(y), parent_(p) {}
  bool operator==(Pos &b) { return x_ == b.x_ && y_ == b.y_; }
};
queue<Pos *> open; // 存放需要搜索的点
stack<Pos *> ans;  // 存放输出的结果
Pos dir[4] = {Pos(1, 0), Pos(0, 1), Pos(-1, 0), Pos(0, -1)};
void Bfs(Pos end) {
  Pos *cur;
  while (!open.empty()) {
    cur = open.front();
    if (*cur == end) {
      while (cur) {
        ans.push(cur);
        cur = cur->parent_;
      }
      while (!ans.empty()) {
        cur = ans.top();
        cout << "(" << cur->x_ - 1 << ", " << cur->y_ - 1 << ")" << endl;
        ans.pop();
      }
      return;
    } else {
      for (int i(0); i < 4; ++i) {
        // 四个方向
        Pos *child = new Pos(cur->x_ + dir[i].x_, cur->y_ + dir[i].y_, cur);
        if (!maze[child->x_][child->y_] && !visited[child->x_][child->y_]) {
          // 如果该方向可行且没走过，加入队列
          open.push(child);
          visited[child->x_][child->y_] = 1;
        } else {
          delete child; // 删掉不需要的儿子节省内存
        }
      }
      open.pop();
    }
  }
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w8_2.in", "r", stdin);
#endif

  memset(maze, -1, sizeof(maze));
  // 周围一圈监视哨设为-1
  memset(visited, 0, sizeof(visited));
  for (int i(1); i <= 5; ++i)
    for (int j(1); j <= 5; ++j)
      cin >> maze[i][j];
  Pos *start = new Pos(1, 1);
  visited[1][1] = 1;
  open.push(start);

  Bfs(Pos(5, 5));

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
