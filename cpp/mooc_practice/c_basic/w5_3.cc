// 1， 5， 10出现的次数

#include <iostream>
using namespace std;

int main() {
  int k;
  int num[10];
  int n1(0), n5(0), n10(0);

  // cout << "Enter k" << endl;
  cin >> k;
  // cout << "Enter k numbers." << endl;
  for (int i(0); i < k; ++i) {
    cin >> num[i];
    if (num[i] == 1) {
      ++n1;
    } else if (num[i] == 5) {
      ++n5;
    } else if (num[i] == 10) {
      ++n10;
    }
  }
  cout << n1 << endl;
  cout << n5 << endl;
  cout << n10 << endl;

  return 0;
}