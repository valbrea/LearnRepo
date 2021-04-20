#include <iostream>
using namespace std;
inline bool Equal(string &a, string &b) {
  int len = a.size();
  if (len % 2 == 0) {
    string a1, a2, b1, b2;
    a1 = a.substr(0, (len / 2));
    a2 = a.substr((len / 2), (len / 2));
    b1 = b.substr(0, (len / 2));
    b2 = b.substr((len / 2), (len / 2));
    return (Equal(a1, b1) && Equal(a2, b2)) || (Equal(a1, b2) && Equal(a2, b1));
  } else {
    for (int i = 0; i < len; ++i) {
      if (a[i] != b[i]) {
        return false;
      }
    }
    return true;
  }
}

int main() {
  int t;
  cin >> t;
  cin.ignore();
  while (t--) {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    bool ans(false);
    ans = Equal(a, b);
    if (ans)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }

  return 0;
}