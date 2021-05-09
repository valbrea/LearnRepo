#include <iostream>
using namespace std;
int main() {
  long long k, a, b;
  cin >> k >> a >> b;
  cin.ignore();
  int day(0);
  if (k > 0) {
    if (a - b > 0) {
      while (k - b > 0) {
        k -= a;
        k += b;
        ++day;
      }
      cout << day << endl;
    } else {
      cout << "-1" << endl;
    }
  } else {
    // k < 0
    k = -k;
    if (a - b < 0) {
      if (k % (b - a) == 0)
        cout << k / (b - a) << endl;
      else
        cout << (k / (b - a) + 1) << endl;
    } else {
      cout << "-1" << endl;
    }
  }

  return 0;
}