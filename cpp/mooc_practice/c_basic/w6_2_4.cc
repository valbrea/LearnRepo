/* #4 最大奇数与最小偶数之差的绝对值
描述
输入6个正整数，且这6个正整数中至少存在一个奇数和一个偶数。

设这6个正整数中最大的奇数为a，最小的偶数为b，求出|a-b|的值
*/

#include <iostream>
using namespace std;

int main() {
  // cout << "输入6个正整数，且至少有一个奇数和一个偶数，且都小于100。" << endl;
  int integer[6];
  int min_even = 100, max_odd = 0;
  for (int i(0); i < 6; ++i) {
    cin >> integer[i];

    if (integer[i] % 2 == 0 && integer[i] < min_even) {
      min_even = integer[i];
    } else if (integer[i] % 2 == 1 && integer[i] > max_odd) {
      max_odd = integer[i];
    }
  }

  int ans;
  if (max_odd > min_even) {
    ans = max_odd - min_even;
  } else {
    ans = min_even - max_odd;
  }

  cout << ans << endl;

  return 0;
}