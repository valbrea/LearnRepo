/*
编程题＃1： 棋盘问题
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个给定形状的棋盘（形状可能是不规则的）上面摆放棋子，棋子没有区别。要求摆放时任意的两个棋子不能放在棋盘中的同一行或者同一列，请编程求解对于给定形状和大小的棋盘，摆放k个棋子的所有可行的摆放方案C。

输入
输入含有多组测试数据。

每组数据的第一行是两个正整数，n
k，用一个空格隔开，表示了将在一个n*n的矩阵内描述棋盘，以及摆放棋子的数目。 n <=
8 , k <= n

当为-1 -1时表示输入结束。

随后的n行描述了棋盘的形状：每行有n个字符，其中 # 表示棋盘区域， .
表示空白区域（数据保证不出现多余的空白行或者空白列）。

输出
对于每一组数据，给出一行输出，输出摆放的方案数目C （数据保证C<2^31）。

样例输入
2 1
#.
.#
4 4
...#
..#.
.#..
#...
-1 -1
样例输出
2
1
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

const int max_n = 8;
int n, k;
char board[max_n][max_n + 1]; 
//! 这里列数一定要max_n + 1，因为cin.getline()录入的最后要放个终止字符
int visited[max_n]; // 标记哪一列放了棋子
ll ans = 0;
void Dfs(int row) {
  // 按行搜索
  if (k == 0) {
    // 棋子用完，方案数++
    ++ans;
    return;
  }
  if (row == n)
    return; // 越界
  // 因为要计算所有的可行方案，所以第一个棋子应该每一行都放一遍
  for (int col(0); col < n; ++col) {
    // 对该行的所有可行位置，放一个棋子
    if (board[row][col] == '#' && !visited[col]) {
      // 如果是可以棋子的位置，且这一列没有放过棋子
      visited[col] = 1;
      --k;
      Dfs(row + 1); // 放下一行的棋子
      ++k;
      visited[col] = 0;
    }
  }
  // 直接不放这一行，从下一行开始放的其余情况
  Dfs(row + 1);
}

int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w6_1.in", "r", stdin);
#endif

  while (cin >> n >> k && n > 0 && k > 0) {
    cin.ignore();
    cin.ignore();
    memset(visited, 0, sizeof(visited)); // 每次清空一下visited
    for (int i(0); i < n; ++i)
      cin.getline(board[i], n + 1, '\n');
    ans = 0;
    Dfs(0);
    cout << ans << endl;
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
