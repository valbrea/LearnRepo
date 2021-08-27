/*
1. 牛的选举
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
现在有N（1<=N<=50000）头牛在选举它们的总统，选举包括两轮：第一轮投票选举出票数最多的K（1<=K<=N）头牛进入第二轮；第二轮对K头牛重新投票，票数最多的牛当选为总统。

现在给出每头牛i在第一轮期望获得的票数Ai（1<=Ai<=1,000,000,000），以及在第二轮中（假设它进入第二轮）期望获得的票数Bi（1<=Bi<=1,000,000,000），请你预测一下哪头牛将当选总统。幸运的是，每轮投票都不会出现票数相同的情况。

输入
第1行：N和K

第2至N+1行：第i+1行包括两个数字：Ai和Bi

输出
当选总统的牛的编号（牛的编号从1开始）

样例输入
5 3
3 10
9 2
5 6
8 4
6 5
样例输出
5
*/
#define STL // STL库，不用时注释掉此行
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
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

int n, k;
struct Cow {
  int id_, a_, b_;
  Cow(int id, int a, int b) : id_(id), a_(a), b_(b) {}
};

bool GreaterA(const Cow &c1, const Cow &c2) { return c1.a_ > c2.a_; }
bool GreaterB(const Cow &c1, const Cow &c2) { return c1.b_ > c2.b_; }

int main() {
#ifdef LOCAL_DEBUG
  freopen("data_structure_2/.debug/w3_1.in", "r", stdin);
#endif

  std::cin >> n >> k;
  std::vector<Cow> cow;
  int ai, bi;
  for (int i = 1; i <= n; ++i) {
    std::cin >> ai >> bi;
    cow.push_back(Cow(i, ai, bi));
  }
  sort(cow.begin() + 1, cow.end(), GreaterA);
  sort(cow.begin() + 1, cow.begin() + k + 1, GreaterB);

  std::cout << cow[1].id_ << std::endl;

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
