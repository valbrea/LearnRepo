/******************************************
 * #3 找出第k大的数
 * 用户输入N和K，然后接着输入N个正整数（无序的），
 * 程序在不对N个整数排序的情况下，找出第K大的数。
 * 注意，第K大的数意味着从大到小排在第K位的数。
 ******************************************/

#include <iostream>
using namespace std;
int main() {
  // cout << "输入整数个数n和想求得的序号k" << endl;
  int n, k;
  cin >> n;
  cin.ignore();
  cin >> k;
  cin.ignore();
  // cout << "输入" << n << "个整数" << endl;

  int a[10000] = {0};
  for (int i(0); i < n; i++)
    cin >> a[i];

  int max = 0;
  int max_index = 0;
  // 把比k大的数全部清零，删除k-1次就找到k了
  for (int j = 0; j < k - 1; j++) {
    for (int i = 0; i < n; i++) {
      if (a[i] >= max) {
        max = a[i];
        max_index = i;
      }
    }
    a[max_index] = 0;
    max = 0;
  }

  for (int i = 0; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
      max_index = i;
    }
  }
  cout << max << endl;

  return 0;
}