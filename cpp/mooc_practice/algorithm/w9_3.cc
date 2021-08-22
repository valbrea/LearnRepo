/*
编程题＃3：Gone Fishing
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 2000ms 内存限制: 65536kB

描述
John is going on a fishing trip. He has h hours available (1 <= h <= 16), and
there are n lakes in the area (2 <= n <= 25) all reachable along a single,
one-way road. John starts at lake 1, but he can finish at any lake he wants. He
can only travel from one lake to the next one, but he does not have to stop at
any lake unless he wishes to. For each i = 1,...,n - 1, the number of 5-minute
intervals it takes to travel from lake i to lake i + 1 is denoted ti (0 < ti
<=192). For example, t3 = 4 means that it takes 20 minutes to travel from lake 3
to lake 4. To help plan his fishing trip, John has gathered some information
about the lakes. For each lake i, the number of fish expected to be caught in
the initial 5 minutes, denoted fi( fi >= 0 ), is known. Each 5 minutes of
fishing decreases the number of fish expected to be caught in the next 5-minute
interval by a constant rate of di (di >= 0). If the number of fish expected to
be caught in an interval is less than or equal to di , there will be no more
fish left in the lake in the next interval. To simplify the planning, John
assumes that no one else will be fishing at the lakes to affect the number of
fish he expects to catch.

Write a program to help John plan his fishing trip to maximize the number of
fish expected to be caught. The number of minutes spent at each lake must be a
multiple of 5.

输入
You will be given a number of cases in the input. Each case starts with a line
containing n. This is followed by a line containing h. Next, there is a line of
n integers specifying fi (1 <= i <=n), then a line of n integers di (1 <=i <=n),
and finally, a line of n - 1 integers ti (1 <=i <=n - 1). Input is terminated by
a case in which n = 0.

输出
For each test case, print the number of minutes spent at each lake, separated by
commas, for the plan achieving the maximum number of fish expected to be caught
(you should print the entire plan on one line even if it exceeds 80 characters).
This is followed by a line containing the number of fish expected.

If multiple plans exist, choose the one that spends as long as possible at lake
1, even if no fish are expected to be caught in some intervals. If there is
still a tie, choose the one that spends as long as possible at lake 2, and so
on. Insert a blank line between cases.

样例输入
2
1
10 1
2 5
2
4
4
10 15 20 17
0 3 4 3
1 2 3
4
4
10 15 50 30
0 3 4 3
1 2 3
0
样例输出
45, 5
Number of fish expected: 31
240, 0, 0, 0
Number of fish expected: 480
115, 10, 50, 35
Number of fish expected: 724
来源
East Central North America 1999
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

// todo: h [1, 16]小时， n [2, 25]个湖，开始于湖1，能够在任意湖停下
// todo: i到i+1有 ti 个5分钟间隔(0, 192]
// todo: 在湖i，最开始5分钟能抓到 fi 条鱼
// todo: 随后每5分钟衰减 di 条鱼，fi 不能 <= di
// todo: 要求输出每个湖呆的时间，能抓到的最多的鱼数量
const int max_n = 26;
int h, n, f[max_n], d[max_n], t[max_n];

int main() {
#ifdef LOCAL_DEBUG
  freopen("algorithm/.debug/w9_3_2.in", "r", stdin);
#endif

  while (cin >> n && n != 0) {
    cin >> h;
    h = h * 60 / 5; // 换算成有多少个五分钟
    for (int i(1); i <= n; ++i)
      cin >> f[i];
    for (int i(1); i <= n; ++i)
      cin >> d[i];
    for (int i(1); i <= n - 1; ++i)
      cin >> t[i];
    t[0] = 0; // lake 0 到lake 1不要时间

    //* 贪心：计算到湖i为止能钓到的最多鱼
    // int *spend = new int[n + 1]; // 计算每个湖呆了多久
    vector<int> max_s(n + 1, 0); // 钓鱼数量最大的那组spend数据
    int max_fish(-1);
    for (int i(1); i <= n; ++i) {
      // 初始化
      int fish_num(0);
      vector<int> spend(n + 1, 0);  // 每个湖呆的时间初始化为0
      vector<int> ff(f, f + i + 1); // 到湖i为止前面所有f
      h -= t[i - 1];
      int time = h; // 最远走到湖i的剩余时间 => time
      //* 减去走到这个湖消耗的时间，那么到i为止的所有湖都相当于可以瞬移到了;
      if (time <= 0)
        break; // 如果走到这个湖就没时间了，后面的循环就可以不做了
      while (time--) {
        int max_f_index = 1;
        for (int j(1); j <= i; ++j) {
          // 找到当前ff最大的index
          if (ff[j] > ff[max_f_index])
            max_f_index = j;
        }
        if (ff[max_f_index] <= 0)
          break; // f[i] - d[i] <= 0 时就钓不到鱼了
        fish_num += ff[max_f_index];
        ff[max_f_index] -= d[max_f_index];
        spend[max_f_index] += 5; // 在该鱼塘逗留了5分钟
      }
       spend[1] += (time + 1) * 5;
        // 剩余的时间都用在lake 1上
      if (fish_num > max_fish) {
        max_fish = fish_num;
        for (int j(1); j <= n; ++j)
          max_s[j] = spend[j];
        // 记录每个湖花费的时间
      }
    }
    for (int i(1); i < n; ++i)
      cout << max_s[i] << ", ";
    cout << max_s[n] << endl;
    cout << "Number of fish expected: " << max_fish << endl << endl;
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
