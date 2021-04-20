
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;
typedef pair<int, int> pa;
struct Cmp {
  bool operator()(pa a, pa b) {
    if (a.first != b.first)
      return a.first > b.first;
    else
      return a.second > b.second;
  }
};

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> v(n, 0);
  priority_queue<pa, vector<pa>, Cmp> pr;
  for (int i(0); i < n; ++i) {
    cin >> v[i];
    pr.push(pa(v[i], i));
  }

  while (k--) {
    int pointer = pr.top().second;
    cout << pointer + 1 << endl;
    int m = pr.top().first + v[pointer];
    pr.pop();
    pr.push({m, pointer});
  }
  return 0;
}