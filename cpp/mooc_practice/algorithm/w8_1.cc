/*
编程题＃1：Flip Game
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
Flip game is played on a rectangular 4x4 field with two-sided pieces placed on
each of its 16 squares. One side of each piece is white and the other one is
black and each piece is lying either it's black or white side up. Each round you
flip 3 to 5 pieces, thus changing the color of their upper side from black to
white and vice versa. The pieces to be flipped are chosen every round according
to the following rules:

Choose any one of the 16 pieces.
Flip the chosen piece and also all adjacent pieces to the left, to the right, to
the top, and to the bottom of the chosen piece (if there are any).

https://d3c33hcgiwev3.cloudfront.net/NRFINhluEeWTGCIAC9WPFA_c13e2bd3b78ef574b09ae3481d4bd87e_Screen-Shot-2015-06-22-at-11.07.11-PM.png?Expires=1628985600&Signature=UspdY~RjUPZCU3OtOmxW~uzXMO7xk0hnBvdfaWdlls~XjH4jiu0rtWAqVisThGmcyjH76UeJxa26g-jr5lH95n6fRe7JHrNb6DOEz1iTCbZNa4ext2glMune5WxIBtu8-d2N6jZOaO6iX3IYFK3K6X4j8l-UtYa7FHE2-pfac7A_&Key-Pair-Id=APKAJLTNE6QMUY6HBC5A

Consider the following position as an example:

bwbw

wwww

bbwb

bwwb

Here "b" denotes pieces lying their black side up and "w" denotes pieces lying
their white side up. If we choose to flip the 1st piece from the 3rd row (this
choice is shown at the picture), then the field will become:

bwbw

bwww

wwwb

wwwb

The goal of the game is to flip either all pieces white side up or all pieces
black side up. You are to write a program that will search for the minimum
number of rounds needed to achieve this goal.

输入
The input consists of 4 lines with 4 characters "w" or "b" each that denote game
field position.

输出
Write to the output file a single integer number - the minimum number of rounds
needed to achieve the goal of the game from the given position. If the goal is
initially achieved, then write 0. If it's impossible to achieve the goal, then
write the word "Impossible" (without quotes).

样例输入
bwwb
bbwb
bwwb
bwww
样例输出
4
*/
#define STL // STL库，不用时注释掉此行
#include <bitset>
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

const int MAX = 65536;
int min_step = INF;
int flag[MAX];
unsigned long Flip(bitset<16> s, int i, int j) {
  s.flip(4 * i + j);
  // 翻转第i,j个位置 和 周围四个位置
  if (i - 1 >= 0) {
    s.flip(4 * (i - 1) + j);
  }
  if (i + 1 < 4) {
    s.flip(4 * (i + 1) + j);
  }
  if (j - 1 >= 0) {
    s.flip(4 * i + j - 1);
  }
  if (j + 1 < 4) {
    s.flip(4 * i + j + 1);
  }
  // 返回翻转后状态对应的unsigned long
  return s.to_ulong();
}
void Bfs(bitset<16> &s) {
  // 广搜, s代表当前状态
  unsigned long next; // 代表下一个可能的状态
  queue<bitset<16> > q;
  int step(0);
  q.push(s);
  while (!q.empty()) {
    int level_end = q.size();
    for (int t = 0; t < level_end; ++t) {
      // 把上次加入的所有状态全部遍历完毕视作遍历完一层
      s = q.front();
      if (s == 0 || s == bitset<16>(0xffff) || step > 12) {
        // 按照熄灯问题的解法，最多按掉后三排的所有灯，所以不会超过12步
        if (step < min_step)
          min_step = step;
      } else {
        for (int i(0); i < 4; ++i)
          for (int j(0); j < 4; ++j) {
            next = Flip(s, i, j);
            if (!flag[next])
              q.push(bitset<16>(next));
            flag[next] = 1;
          }
      }
      q.pop();
    } // 遍历完一层才记作一步
    ++step;
  }
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w8_1.in", "r", stdin);
#endif

  // 思路：状态一共2^16=65536个，可以用一个bitset<16>来表示，全黑0xffff全白0x0，
  // 16bits = 2 bytes, 也可以用一个unsigned short来保存，但没必要
  // 利用BFS搜索出最短路径，并用min_setp保存步数
  char c;
  bitset<16> states; // states存放当前棋盘状态
  for (int i(0); i < 4; ++i)
    for (int j(0); j < 4; ++j) {
      cin >> c;
      if (c == 'b')
        states.flip(4 * i + j); // 反转对应位置
    }
  flag[states.to_ulong()] = 1;
  Bfs(states);
  if (min_step > 12)
    cout << "Impossible" << endl;
  else
    cout << min_step << endl;

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
