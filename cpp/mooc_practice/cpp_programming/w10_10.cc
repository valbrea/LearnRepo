/*
编程题＃10：输出指定结果二
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 1024kB

描述
通过填空使得程序输出的结果符合下面的要求。
输入
不需要输入。

输出
使得程序的输出结果是：

2
3
B::destructor
A::destructor
3
4
B::destructor
A::destructor
3
B::destructor
A::destructor
A::destructor
A::destructor
*/
#include <iostream>
#include <map>
using namespace std;
// 在此处补充你的代码
class A {
public:
  static int count;
  A() { ++count; }
  A(int n) { ++count; }
  virtual ~A() { cout << "A::destructor" << endl; }
  // 最后count少了1，唯一区别就是用了delete，所以delete被重载了
  void operator delete(void *pa) { --count; } // delete的参数必须是void*类型
};
class B : public A {
public:
  B(int n) {}
  ~B() { cout << "B::destructor" << endl; }
};

int A::count = 0;
void func(B b) {}
int main() {
  A a1(5), a2;

  cout << A::count << endl;
  B b1(4);
  cout << A::count << endl;

  func(b1); // fun(b1)两次析构

  cout << A::count << endl;
  A *pa = new B(4);
  cout << A::count << endl;

  delete pa; // pa两次析构
  cout << A::count << endl;
  return 0; // 四次析构
}