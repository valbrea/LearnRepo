/*
编程题＃2： 滑雪
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
Michael喜欢滑雪百这并不奇怪，
因为滑雪的确很刺激。可是为了获得速度，滑的区域必须向下倾斜，而且当你滑到坡底，你不得不再次走上坡或者等待升降机来载你。Michael想知道载一个区域中最长的滑坡。区域由一个二维数组给出。数组的每个数字代表点的高度。下面是一个例子
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
一个人可以从某个点滑向上下左右相邻四个点之一，当且仅当高度减小。在上面的例子中，一条可滑行的滑坡为24-17-16-1。当然25-24-23-...-3-2-1更长。事实上，这是最长的一条。

输入
输入的第一行表示区域的行数R和列数C(1 <= R,C <=
100)。下面是R行，每行有C个整数，代表高度h，0<=h<=10000。

输出
输出最长区域的长度。

样例输入
5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
样例输出
25
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

const int MAX = 103;

int r, c, h;
int height[MAX][MAX], step[MAX][MAX];
struct Point {
  int x_, y_, height_;
  Point(int r, int c, int h) : x_(r), y_(c), height_(h) {}
  friend bool operator<(const Point &a, const Point &b) {
    return a.height_ < b.height_;
  }
};
int Step(Point &p) {
  int x = p.x_, y = p.y_;
  priority_queue<int> max_step;
  if (p.height_ > height[x - 1][y])
    max_step.push(step[x - 1][y]);
  if (p.height_ > height[x + 1][y])
    max_step.push(step[x + 1][y]);
  if (p.height_ > height[x][y - 1])
    max_step.push(step[x][y - 1]);
  if (p.height_ > height[x][y + 1])
    max_step.push(step[x][y + 1]);
  if (!max_step.empty())
  // 如果非空，则其中的点都低于p点，则选取其中最大的step并+1作为新点的step
    return max_step.top() + 1;
  else
  // 如果是空的证明该点不高于周围所有点，返回1
    return 1;
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w4_2.in", "r", stdin);
#endif

  vector<Point> points;
  cin >> r >> c;
  for (int i(0); i < r + 2; ++i)
    for (int j(0); j < c + 2; ++j) {
      height[i][j] = INF; // 周围增加了一圈边界点，高度设为最高
    }

  for (int i(1); i < r + 1; ++i)
    for (int j(1); j < c + 1; ++j) {
      cin >> h;
      height[i][j] = h;
      step[i][j] = 1;
    }
  for (int i(0); i < r + 2; ++i)
    for (int j(0); j < c + 2; ++j) {
      points.push_back(Point(i, j, height[i][j]));
    }

  sort(points.begin(), points.end());
  int max_all(0);
  for (int i(0); i < r * c; ++i) {
    // 按照高度排序后，前面r*c个元素就是正常元素
    step[points[i].x_][points[i].y_] = Step(points[i]);
    if (step[points[i].x_][points[i].y_] > max_all)
      max_all = step[points[i].x_][points[i].y_];
  }
  cout << max_all << endl;

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
