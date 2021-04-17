/* #5：分离整数的各个数位
* 描述
从键盘输入一个任意的四位整数，要求正确地分离出它的千位、百位、十位和个位数，并分别在屏幕上输出，输出采用每行输出一个数的方式，不带其它符号。
*/

#include <iostream>
using namespace std;

int main() {
  unsigned int number;
  cin >> number;
  if (number >= 100 && number < 1000) {
    // cout << "千位" << number / 1000 << endl;
    // cout << "百位" << number / 100 % 10 << endl;
    // cout << "十位" << number / 10 % 10 << endl;
    // cout << "个位" << number % 10 << endl;
    // cout << number / 1000 << endl;
    cout << number / 100 % 10 << endl;
    cout << number / 10 % 10 << endl;
    cout << number % 10 << endl;
  } else {}
    // cout << "请输入四位数字。" << endl;

  return 0;
}