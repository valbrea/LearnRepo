// apples and bugs
/*
 * 你买了一箱n个苹果，很不幸的是买完时箱子里混进了一条虫子。
 * 虫子每x小时能吃掉一个苹果，假设虫子在吃完一个苹果之前不会吃另一个，那么经过y小时你还有多少个完整的苹果？
 */

#include <iostream>
using namespace std;

int main() {
  // 输入仅一行，包括n，x和y（均为整数）。
  // cout << "输入苹果总数，虫子吃苹果的速度，吃了几个小时。" << endl;
  int total, rate, hour;
  cin >> total >> rate >> hour;
  int left;
  if (hour % rate != 0)
    left = total - (hour / rate + 1);
  else
    left = total - (hour / rate);
  // cout << "剩余苹果数量为：" << left << endl;
  if (left >= 0)
    cout << left << endl;
  else
    cout << "0" << endl;

  return 0;
}