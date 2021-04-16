/*****************************************************************
 * #4 找和为K的两个元素
 * ***************************************************************
 * 描述
 * 在一个长度为n(n < 1000)的整数序列中，判断是否存在某两个元素之和为k。
 * ***************************************************************
 * 输入
 * 第一行输入序列的长度n和k，用空格分开。
 * 第二行输入序列中的n个整数，用空格分开。
 * ***************************************************************
 输出 如果存在某两个元素的和为k，则输出yes，否则输出no。
 * ***************************************************************/
#include <iostream>
using namespace std;
int main() {
  // cout << "输入序列的长度N， 两个元素之和K" << endl;
  int length, sum;
  cin >> length >> sum;
  // cout << "输入序列中的N个整数，用空格分开" << endl;
  int number[length];
  for (int i = 0; i < length; i++)
    cin >> number[i];
  bool success = false;
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (number[i] + number[j] == sum) {
        success = true;
        break;
      }
    }
  }
  if (success == true)
    cout << "yes" << endl;
  else
    cout << "no" << endl;

  return 0;
}