// 1的个数
// 给定一个十进制整数N，求其对应2进制数中1的个数

#include <iostream>
using namespace std;

int main() {
  // 第一个整数表示有N组测试数据，其后N行是对应的测试数据，每行为一个整数。
  int group_num; //有几组数据
  // cout << "How many groups of data?" << endl;
  cin >> group_num;
  for (int i(0); i < group_num; ++i) {
    int decimal, number_of_one(0);
    // cout << "Enter a number in decimal." << endl;
    cin >> decimal;
    while (decimal > 0) {
      number_of_one += decimal % 2;
      decimal /= 2;
    }
    // cout << "There are " << number_of_one << " \'1\'s in this number." <<
    // endl;
    cout << number_of_one << endl;
  }

  return 0;
}