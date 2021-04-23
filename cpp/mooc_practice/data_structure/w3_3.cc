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
#include <string>
using namespace std;
string TypeIn(string str) {
  stack<char> temp;
  string eq;
  char op;
  // 注意！！！加减乘除优先级一样！！注意看题！
  for (int i(0); i < str.size(); ++i) {
    op = str[i]; // str不需要pop了
    if (isalnum(op))
      eq += op;
    else if (op == '(')
      temp.push(op);
    else if (op == ')') {
      // 右括号只用来判断，不入栈
      while (temp.top() != '(') {
        eq += temp.top();
        temp.pop();
      }
      temp.pop(); // 丢弃左括号
    } else {
      // 本题中加减乘除优先级都一样，所以操作会不一样
      if (temp.empty() || temp.top() == '(')
        temp.push(op);
      else {
        eq += temp.top();
        temp.pop();
        temp.push(op);
      }
    }
  }
  while (!temp.empty()) {
    eq += temp.top();
    temp.pop();
  }
  return eq;
}
int Cal(string out) {
  stack<int> temp_int;
  char op;
  int a, b;
  for (int i(0); i < out.size(); ++i) {
    op = out[i];
    if (isalpha(op)) {
      temp_int.push(op);
    } else if (isdigit(op)){
      temp_int.push(op - '0');
    } else {
      b = temp_int.top();
      temp_int.pop();
      a = temp_int.top();
      temp_int.pop();
      switch (op) {
      case '+':
        a += b;
        temp_int.push(a);
        break;
      case '-':
        a -= b;
        temp_int.push(a);
        break;
      case '*':
        a *= b;
        temp_int.push(a);
        break;
      case '/':
        a /= b;
        temp_int.push(a);
        break;
      default:
        break;
      }
    }
  }
  return temp_int.top();
}
int main() {
  int n;
  cin >> n;
  cin.ignore();
  while (n--) {
    string str1, str2;
    getline(cin, str1);
    getline(cin, str2);
    string out1, out2;
    out1 = TypeIn(str1);
    out2 = TypeIn(str2);
    int ans1, ans2;
    ans1 = Cal(out1);
    ans2 = Cal(out2);
    if (ans1 == ans2)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}