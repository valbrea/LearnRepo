// 冒泡排序

#include <iostream>
using namespace std;

int main() {
  int n = 0;
  int a[1000];
  //   cout << "please enter the length \'n\' of the array." << endl;
  cin >> n;
  cin.ignore();
  //   cout << "please enter the elements of this array." << endl;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 1; j < n - i; ++j) {
      if (a[j - 1] > a[j]) {
        int temp = a[j];
        a[j] = a[j - 1];
        a[j - 1] = temp;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << a[i] << endl;
  }
  cout << endl;

  return 0;
}
