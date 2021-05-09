#include <iostream>
#include <queue>
#include <stack>
using namespace std;

queue<int> overtake() {
  int n, q, num, x;
  queue<int> ans;
  cin >> n >> q;
  for (int i(1); i <= n; i++) {
    ans.push(i);
  }

  for (int i(q); i > 0; --i) {
    cin >> num >> x;
    stack<int> stk1;
    stack<int> stk2;
    for (int i(n); i > 0; --i) {
      stk2.push(ans.front());
      ans.pop();
    }
    while (!stk2.empty()) {
      stk1.push(stk2.top());
      stk2.pop();
    }

    while (stk1.top() != num) {
      stk2.push(stk1.top());
      stk1.pop();
    }

    while (((x + 1) != 0) && !stk1.empty()) {
      ans.push(stk1.top());
      stk1.pop();
      x--;
    }

    while (!stk2.empty()) {
      stk1.push(stk2.top());
      stk2.pop();
    }

    while (!stk1.empty()) {
      ans.push(stk1.top());
      stk1.pop();
    }
  }

  return ans;
}

int main() {

  queue<int> ans = overtake();
  while (!ans.empty()) {
    cout << ans.front() << " ";
    ans.pop();
  }
  return 0;
}