// #2 大象喝水
/* 一只大象口渴了，要喝20升水才能解渴，但现在只有一个深h厘米，底面半径为r厘米的小圆桶(h和r都是整数)。
 * 问大象至少要喝多少桶水才会解渴。
 */
#include <iostream>
using namespace std;

int main() {
  int depth, radius;
  // cout <<
  // "输入有一行：包行两个整数，以一个空格分开，分别表示小圆桶的深h和底面半径r，单位都是厘米。"
  // << endl;
  cin >> depth >> radius;

  double volume;
  const double PI = 3.1415927;
  volume = PI * (double)radius * (double)radius * (double)depth;

  int number_of_barrel;
  number_of_barrel = 20 * 1000 / volume + 1;
  // cout << "大象至少要喝" << number_of_barrel << "桶水才会解渴。" << endl;
  cout << number_of_barrel << endl;
  return 0;
}