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
const int MAX_COUNT = 65;
int Poke(vector<int> &poke, int totalPoke) {
  if (totalPoke <= 0) {
    return 0;
  }
  if (totalPoke == 1) {
    return 1;
  }

  int ans = MAX_COUNT;
  int recursiveResult;
  bool flag;

  // 顺子
  if (totalPoke >= 5) {
    for (size_t i = 0; i < 13; ++i) {
      flag = true; // 有顺子
      for (size_t j = i; j < i + 5; ++j) {
        if ((j < 13 && poke[j] == 0) || j >= 10) {
          flag = false;
          break;
        }
      }
      if (flag) {
        for (size_t j = i; j < i + 5; ++j) {
          --poke[j];
        }
        recursiveResult = Poke(poke, totalPoke - 5);
        if (recursiveResult + 1 < ans) {
          ans = recursiveResult + 1;
        }
        for (size_t j = i; j < i + 5; ++j) {
          ++poke[j];
        }
      }
    }
  }

  // 炸弹
  if (ans == MAX_COUNT) {
    recursiveResult = 0;
    for (int &num : poke) {
      recursiveResult += (num / 4);
      num %= 4;
      recursiveResult += num;
    }
    ans = recursiveResult;
  }
  

  // 对子
  if (ans == MAX_COUNT) {
    recursiveResult = 0;
    for (int &num : poke) {
      recursiveResult += (num / 2);
      num %= 2;
      recursiveResult += num;
    }
    ans = recursiveResult;
  }

  // 单牌
  if (ans == MAX_COUNT) {
    ans = 0;
    for (int num : poke) {
      ans += num;
    }
  }

  return ans;
}
int main() {
#ifdef LOCAL
  freopen(".debug/pdd2_6_7.in", "r", stdin);
#endif

  int n;
  cin >> n;
  cin.ignore();
  vector<int> poke(13);
  int total = 0;
  int num;
  char c;
  for (int i = 0; i < n; ++i) {
    if (cin >> num) {
      ++poke[i - 1];
      total += num;
    } else {
      cin.clear();
      c = cin.get();
      if (c == ' ') {
        c = cin.get();
      }
      switch (c) {
      case 'J':
        total += 10;
        ++poke[9];
        break;
      case 'Q':
        total += 11;
        ++poke[10];
        break;
      case 'K':
        total += 12;
        ++poke[11];
        break;
      case 'A':
        total += 1;
        ++poke[0];
        break;
      default:
        break;
      }
    }
  }
  int times = n;

  cout << Poke(poke, total) << endl;

#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
