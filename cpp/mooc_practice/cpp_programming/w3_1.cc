/*
编程题＃1
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
下面程序输出的结果是：

0
5

请填空：
#include <iostream>
using namespace std;
class A {
public:
    int val;
// 在此处补充你的代码
};
main() {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
}

提示
所缺代码具有如下形式：
 A(_________________ ){ val = n; }
    ________________ GetObj() {
        return _________________;
    }
*/

#include <iostream>
using namespace std;
class A
{
public:
    int val;
    // 在此处补充你的代码
    // 第一种 返回A类型对象的引用，用this指针
    A(int n = 0) { val = n; }
    A & GetObj()
    {
        return *this;
    }
    // 第二种写法 返回int类型val的引用
    // int & GetObj()
    // {
    //     return val;
    // }
};
int main()
{
    A a;
    cout << a.val << endl;
    a.GetObj() = 5; // 对函数的返回值进行赋值，所以要使用引用返回值&
    cout << a.val << endl;
    return 0;
}