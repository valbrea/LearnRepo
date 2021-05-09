#include <iostream>
using namespace std;
struct kids {
  int t;
  int h;
  int d;
  kids() : t(0), h(0), d(0) {}
};

int main() {
  int n;
  cin >> n;
  kids *kid = new kids[n];
  int *count = new int[n];
  for (int i(0); i < n; ++i) {
    cin >> kid[i].t >> kid[i].h >> kid[i].d;
  }
  for (int i(0); i < n; ++i) {
    count[i] = 0;
    bool seej(false);
    for (int j(n - 1); j > i; --j) {
      // 看后面
      if (kid[i].t - kid[i].d <= kid[j].t && kid[j].t <= kid[i].t + kid[i].d)
        seej = true;
      else
        continue;
      // 如果从j-1到i+1都找不到比j更高的， higher = false
      // 如果找到了，这个j = 这个更高的k，继续找
      for (int k(j - 1); k > i; --k) {
        if (kid[k].h >= kid[j].h) {
          j = k + 1;
          seej = false;
          break;
        }
      }
      if (seej = true)
        count[i] += j - i;
    }

    seej = false;
    for (int j(0); j < i; ++j) {
      // 看前面
      if (kid[i].t - kid[i].d <= kid[j].t && kid[j].t <= kid[i].t + kid[i].d)
        seej = true;
      else
        continue;
      // 如果找到了更高的，这个j = 这个更高的k，seej = false
      for (int k(j + 1); k < i; ++k) {
        if (kid[k].h >= kid[j].h) {
          j = k - 1;
          seej = false;
          break;
        }
      }
      if (seej == true)
        count[i] += i - j;
    }

    cout << count[i] << " ";
  }
  return 0;
}