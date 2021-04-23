/*
3. 等价表达式
来源：POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 1000ms 内存限制: 65536kB

描述
判断两个表达式在数学上是否是等价的。

输入
第一行：N（1<=N<=20），表示测试数据组数。

接下来每组测试数据包括两行，每行包括一个数学表达式，每个表达式的长度不超过80个字符。输入数据没有空行。

一个表达式可能包括：

单个英文字母表示的变量（区分大小写）

数字（只有一位数）

配对的括号

运算符加+、减-、乘*

任意数量的空格或tab（可能出现在表达式中间的任何位置）

注意：表达式保证是语法正确的，且所有运算符的优先级相同，运算次序从左至右。变量的系数和指数保证不超过16位整数。

输出
对每个测试数据，输出一行：等价则输出“YES”，不等价则输出“NO”。

样例输入
3
(a+b-c)*2
(a+a)+(b*2)-(3*c)+c
a*2-(a+c)+((a+c+e)*2)
3*a+c+(2*e)
(a-b)*(a-b)
(a*a)-(2*a*b)-(b*b)

样例输出
YES
YES
NO
*/
#include <iostream>
#include <stack>
using namespace std;
bool Prior(char a, char b) {}
int main() {
  int n;
  cin >> n;
  cin.ignore();
  while (n--) {
    stack<char> temp1, eq1;
    char op;
    // 注意！！！加减乘除优先级一样！！注意看题！
    while ((op = cin.get()) != '\n') {
      if (isalnum(op))
        eq1.push(op);
      else if (op == '(') {
        temp1.push(op);
      } else if (op == ')') {
        // 右括号只用来判断，不入栈
        while (temp1.top() != '(') {
          eq1.push(temp1.top());
          temp1.pop();
        }
        temp1.pop(); // 丢弃左括号
      }
      else {
        // 本题中加减乘除优先级都一样！！！
        if (temp1.empty())
          temp1.push(op);
      }
    }
  }
  return 0;
}