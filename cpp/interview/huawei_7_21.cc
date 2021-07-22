// #define LOCAL // 本地调试宏定义，提交代码时注释掉此行
#define STL // STL库，不用时注释掉此行
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

#define MAX_K 10001
int main() {
#ifdef LOCAL
  freopen(".debug/huawei_7_21_1.in", "r", stdin);
#endif
  /*
  50 3
 0 0 15
 10 10 11
 15 20 40
 out
 2
  */
  typedef enum { kShun, kNi } Status;
  struct Passenger {
    int start_;
    int on_id_;
    int off_id_;
    int run_time_;
    Status status_;
    int end_;
    // friend bool operator<(Passenger $p1, Passenger p2)
  };
  int n, k;
  cin >> n >> k;
  cin.ignore();
  // 2 <= n <= 100, 0 <= k <= 10000
  Passenger pass[MAX_K];
  int s, on, off;
  for (int i(0); i < k; ++i) {
    cin >> s >> on >> off;
    if (on != off) {
      pass[i].start_ = s;
      pass[i].on_id_ = on;
      pass[i].off_id_ = off;
      int big, small;
      if (on > off) {
        big = on;
        small = off;
      } else {
        big = off;
        small = on;
      }
      if ((big - small) > (n / 2)) {
        pass[i].status_ = kNi;
        pass[i].run_time_ = (n - (big - small)) * 5;
      } else {
        pass[i].status_ = kShun;
        pass[i].run_time_ = (big - small) * 5;
      }
      pass[i].end_ = pass[i].start_ + pass[i].run_time_;
    }
    cin.ignore();
  }
  int min_start = 5 * n;
  int max_end = 0;
  for (int i(0); i < k; ++i) {
    if (pass[i].start_ < min_start)
      min_start = pass[i].start_;
    if (pass[i].end_ > max_end)
      max_end = pass[i].end_;
  }
  vector<int> count(MAX_K, 0);
  int max_count(0);

  for (int time(min_start); time <= max_end; ++time) {
    for (int i(0); i < k; ++i) {
      if (pass[i].start_ <= time && time < pass[i].end_)
        ++count[time];
    }
    if (count[time] > max_count)
      max_count = count[time];
  }
  cout << max_count << endl;
#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
