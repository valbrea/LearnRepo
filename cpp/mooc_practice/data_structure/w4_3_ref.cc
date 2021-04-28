// 利用next数组的特性，时间复杂度是O(n)，暂时没看懂
#include <iostream>
#include <string>

using namespace std;

int next[1000005];

void get_next(string s, int next[]) {
  int length = s.length();
  int i = 0, j = -1;
  next[0] = -1;
  while (i < length) {
    if (j == -1 || s[i] == s[j]) {
      i++;
      j++;
      next[i] = j;
    } else {
      j = next[j];
    }
  }
}

int main(void) {
  int len;
  int t = 1, j;
  while (cin >> len, len) {
    string s;
    cin >> s;
    get_next(s, ::next);
    cout << "Test case #" << t++ << endl;
    for (int i = 2; i <= len; i++) {
      j = i - ::next[i];
      if (i % j == 0 && i / j >= 2)
        cout << i << " " << i / j << endl;
    }
    cout << endl;
  }

  return 0;
}