/*
2. 出栈序列统计
来源：POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 100ms 内存限制: 64kB

描述
栈是常用的一种数据结构，有n个元素在栈顶端一侧等待进栈，栈顶端另一侧是出栈序列。你已经知道栈的操作有两
种：push和pop，前者是将一个元素进栈，后者是将栈顶元素弹出。现在要使用这两种操作，由一个操作序列可以
得到一系列的输出序列。请你编程求出对于给定的n，计算并输出由操作数序列1，2，…，n，经过一系列操作可能
得到的输出序列总数。

输入
就一个数n(1≤n≤15)。

输出
一个数，即可能输出序列的总数目。

样例输入
3

样例输出
5

提示
先了解栈的两种基本操作，进栈push就是将元素放入栈顶，栈顶指针上移一位，等待进栈队列也上移一位，出栈
pop是将栈顶元素弹出，同时栈顶指针下移一位。

用一个过程采模拟进出栈的过程，可以通过循环加递归来实现回溯：重复这样的过程，如果可以进栈则进一个元
素，如果可以出栈则出一个元素。就这样一个一个地试探下去，当出栈元素个数达到n时就计数一次(这也是递归
调用结束的条件)。
*/
#include <iostream>
using namespace std;
int Stk(int left, int inside) {
  // 如果所有元素都已经出栈了
  if (left == 0 && inside == 0)
    return 1;
  // 如果栈里没有元素，只能入栈
  if (left != 0 && inside == 0)
    return Stk(left - 1, inside + 1);
  // 如果没剩的，栈里还有，就只能出栈
  if (left == 0 && inside != 0)
    return Stk(left, inside - 1);
  // 如果栈不空，还有剩余元素，则可以做：1.入栈 2.出栈
  if (left != 0 && inside != 0)
    return (Stk(left - 1, inside + 1) + Stk(left, inside - 1));
}
int main() {
  int left, inside(0);
  cin >> left;
  cin.ignore();
  cout << Stk(left, inside) << endl;

  return 0;
}