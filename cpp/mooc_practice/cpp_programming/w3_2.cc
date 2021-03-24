/*
描述
下面程序的输出是：

10

请补足Sample类的成员函数。不能增加成员变量。
输入
无

输出
10

#include <iostream>
using namespace std;
class Sample{
public:
    int v;
    Sample(int n):v(n) { }
// 在此处补充你的代码
};
int main() {
    Sample a(5);
    Sample b = a;
    cout << b.v;
    return 0;
}

*/

#include <iostream>
using namespace std;
class Sample{
public:
    int v;
    Sample(int n):v(n) { }
// 在此处补充你的代码
    // Sample(Sample &c): v(c.v = 10) { } // 不能用const Sample & c 因为这样就会无法赋值。但这种方法不好，因为会改变引用对象c的值
    // Sample(const Sample &c) {v = c.v * 2} // 这样就比较合理， 不会改变应用对象c的值
    Sample (const Sample &c): v(10) {}  // 这种方法其实不需要对输入c进行任何操作，但是调用复制构造函数必须要输入一个同类对象的引用
};
int main() {
    Sample a(5);
    Sample b = a;
    cout << b.v;
    return 0;
}