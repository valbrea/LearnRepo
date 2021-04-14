/*
编程题＃1：输出200
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 1024kB

描述
使以下代码输出结果为200.
*/
#include <iostream>
using namespace std;
class Number {
public:
  int num;
  Number(int n = 0) : num(n) {}
  // 在此处补充你的代码
  int operator*(Number &n2) { return num * n2.num; }
  operator int() { return num; }
};
int main() {
  Number n1(10), n2(20);
  Number n3;
  n3 = n1 * n2;
  cout << int(n3) << endl;
  return 0;
}