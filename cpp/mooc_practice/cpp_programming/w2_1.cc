/*
简单的学生信息处理程序实现
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个学生信息处理程序中，要求实现一个代表学生的类，并且所有成员变量都应该是私有的。

（注：评测系统无法自动判断变量是否私有。我们会在结束之后统一对作业进行检查，请同学们严格按照题目要求完成，否则可能会影响作业成绩。）

输入
姓名，年龄，学号，第一学年平均成绩，第二学年平均成绩，第三学年平均成绩，第四学年平均成绩。

其中姓名、学号为字符串，不含空格和逗号；年龄为正整数；成绩为非负整数。

各部分内容之间均用单个英文逗号","隔开，无多余空格。

输出
一行，按顺序输出：姓名，年龄，学号，四年平均成绩（向下取整）。

各部分内容之间均用单个英文逗号","隔开，无多余空格。

样例输入
Tom,18,7817,80,80,90,70

样例输出
Tom,18,7817,80
*/
#include <iostream>
#include <string>
using namespace std;
class Student
{
private:
    char *name_ = new char[20], *number_ = new char[20];
    int age_, grade_[4];

public:
    char comma = ',';
    void Input();
    void Output();
};

int main()
{
    Student s;
    s.Input();
    s.Output();

    return 0;
}
void Student::Input()
{
    cin.getline(name_, 20, ',');
    cin >> age_ >> comma;
    cin.getline(number_, 20, ',');
    cin >> grade_[0] >> comma >> grade_[1] >> comma >> grade_[2] >> comma >> grade_[3];
}
void Student::Output()
{
    cout << name_ << comma << age_ << comma << number_ << comma
         << (grade_[0] + grade_[1] + grade_[2] + grade_[3]) / 4 << endl;
}
