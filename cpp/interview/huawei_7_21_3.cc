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
enum { kUnvisited, kVisited };

void Topo(vector<vector<int> > &matrix, vector<int> &in_degree, int v) {
  int *mark = new int[v];
  priority_queue<int, vector<int>, greater<int> >
      q; // 要求在同等条件下，编号小的顶点在前，所以要用priority_queue
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
    
    cout << "v" << u + 1 << ' ';
  }
}
void GetMaxPath (int n ) {
  int i, j ,k, v2, v3, max = 0;
  int **path, *p;
  
}
#define NINF (INT_MIN / 2)
int main() {
#ifdef LOCAL
  freopen(".debug/huawei_7_21_3.in", "r", stdin);
#endif
  vector<int> in;
  string str;
  int tmp1, tmp2, tmp3;
  char l,r,c;
  cin >> l;
  while (cin >> l >> tmp1 >> c >> tmp2 >> c >> tmp3 >> r >> c) {
    in.push_back(tmp1);
    in.push_back(tmp2);
    in.push_back(tmp3);
    
  }

  int n = in.size() / 3;
  vector<vector<int> > matrix(n + 1, vector<int>(n + 1, 0));
  vector<vector<int> > weight(n + 1, vector<int>(n + 1, 0));
  vector<int> in_degree(n + 1, 0);
  for (int i = 0; i < n * 3; i = i + 3) {
    int s = in[i];
    int d = in[i + 1];
    int w = in[i + 2];

    weight[s][d] = w;
    matrix[s][d] = 1;
    in_degree[d]++;
  }
  Topo(matrix, in_degree, n);
#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
