/*
编程题＃2：A Knight's Journey
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
Background

The knight is getting bored of seeing the same black and white squares again and
again and has decided to make a journey around the world. Whenever a knight
moves, it is two squares in one direction and one square perpendicular to this.
The world of a knight is the chessboard he is living on. Our knight lives on a
chessboard that has a smaller area than a regular 8 * 8 board, but it is still
rectangular. Can you help this adventurous knight to make travel plans?

https://d3c33hcgiwev3.cloudfront.net/ialZGBlrEeW4giIAC5XN5A_dac192a4848cfdda7f01b12ca72adf43_Screen-Shot-2015-06-22-at-10.47.10-PM.png?Expires=1628726400&Signature=PHb6posBnlQuiw-UV1F~~LM3vk3IPOzWUbzq1Z0sQ6DOUsTClnvN9Tg4x1a~JzfsJYzazA7r~iFIekM~Mq7Sj1Gn-LFSEzSTBxfLG~fYMcmIJqOUueHxwAngVssyh~ilHCnrFKcG7yrnwLWMeCI6HP4R60z3T1sCP3Nwhx8L00s_&Key-Pair-Id=APKAJLTNE6QMUY6HBC5A

Problem

Find a path such that the knight visits every square once. The knight can start
and end on any square of the board.

输入
The input begins with a positive integer n in the first line. The following
lines contain n test cases. Each test case consists of a single line with two
positive integers p and q, such that 1 <= p * q <= 26. This represents a p * q
chessboard, where p describes how many different square numbers 1, . . . , p
exist, q describes how many different square letters exist. These are the first
q letters of the Latin alphabet: A, . . .

输出
The output for every scenario begins with a line containing "Scenario #i:",
where i is the number of the scenario starting at 1. Then print a single line
containing the lexicographically first path that visits all squares of the
chessboard with knight moves followed by an empty line. The path should be given
on a single line by concatenating the names of the visited squares. Each square
name consists of a capital letter followed by a number.

If no such path exist, you should output impossible on a single line.

样例输入
3
1 1
2 3
4 3
样例输出
Scenario #1:
A1

Scenario #2:
impossible

Scenario #3:
A1B3C1A2B4C2A3B1C3A4B2C4
*/

//! 思路见：https://www.cnblogs.com/llhthinker/p/4924654.html
//! 或：https://blog.csdn.net/lyy289065406/article/details/6647666
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

const int max_pq = 9;
int p, q;
int visited[max_pq][max_pq];
struct Coordinate {
  // p方向x， q方向y
  int x_, y_;
  Coordinate(int x, int y) : x_(x), y_(y) {}
  Coordinate() : x_(0), y_(0) {}
  Coordinate &operator+=(const Coordinate &d) {
    x_ += d.x_;
    y_ += d.y_;
    return *this;
  }
  Coordinate &operator-=(const Coordinate &d) {
    x_ -= d.x_;
    y_ -= d.y_;
    return *this;
  }
  bool Legal() {
    return 0 <= x_ && x_ < p && 0 <= y_ && y_ < q && !visited[x_][y_];
  }
  // 检查是否合法
};
stack<Coordinate> path;
// 方向，按照字典序排序
const Coordinate dir[] = {{-1, -2}, {1, -2}, {-2, -1}, {2, -1},
                          {-2, 1},  {2, 1},  {-1, 2},  {1, 2}};
// const int direction_x[] = {-2, -2, -1, -1, 1, 1, 2, 2};
// const int direction_y[] = {-1, 1, -2, 2, -2, 2, -1, 1};
bool KnightMove(Coordinate &pos, int step) {
  // 棋子的当前位置，和剩余格子数，深搜
  if (step == 0) {
    // 剩余格子为0就结束了
    path.push(pos);
    // 记录一下位置
    return true;
  }
  if (step < 0)
    return false;
  for (int i(0); i < 8; ++i) {
    // 从字典序小的方向开始搜
    pos += dir[i];
    if (!pos.Legal()) {
      // 位置不合法就回退并找下一个方向
      pos -= dir[i];
      continue;
    }
    // 合法的话就记录下一步要去的位置
    visited[pos.x_][pos.y_] = 1;
    if (KnightMove(pos, step - 1)) {
      pos -= dir[i];
      path.push(pos);
      // 记录一下位置
      return true;
    } else {
      // 回溯
      visited[pos.x_][pos.y_] = 0;
      pos -= dir[i];
    }
  }
  // 8个方向都走不动就返回false
  return false;
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w6_2.in", "r", stdin);
#endif

  int n;
  cin >> n;
  cin.ignore();
  int scenario(1);
  while (n--) {
    // p: 行号1...p， q：列号:A...q
    cin >> p >> q;
    cin.ignore();
    // 输出：字典序lexicographically，A1->A2->A3...
    cout << "Scenario #" << scenario++ << ":" << endl;
    memset(visited, 0, sizeof(visited));
    Coordinate start(0, 0);
    visited[0][0] = 1;
    int step_left = p * q;
    if (!KnightMove(start, step_left - 1))
      // 因为第一个格子直接踩上去了，所以剩余格子数要-1
      cout << "impossible";
    else {
      while (!path.empty()) {
        cout << char(path.top().y_ + 'A') << path.top().x_ + 1;
        path.pop();
      }
    }
    cout << endl << endl;
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
