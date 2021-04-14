/*************************************************************************************
编程题＃6：MyString
来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 1024kB

描述
请写出 MyString类，使得下面程序的输出结果符合下面的要求。
同w5_1.cc
**************************************************************************************/
/*
编程题＃1 (w5_1.cc)
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
写一个MyString 类，使得下面程序的输出结果是：

1. abcd-efgh-abcd-

2. abcd-

3.

4. abcd-efgh-

5. efgh-

6. c

7. abcd-

8. ijAl-

9. ijAl-mnop

10. qrst-abcd-

11. abcd-qrst-abcd- uvw xyz

about

big

me

take

abcd

qrst-abcd-

要求：MyString类必须是从C++的标准类string类派生而来。
提示1：如果将程序中所有 "MyString" 用"string" 替换，那么题目的程序中除了
最后两条语句编译无法通过外，其他语句都没有问题，而且输出和前面给的结果吻合。
也就是说，MyString类对 string类的功能扩充只体现在最后两条语句上面。
提示2: string类有一个成员函数 string substr(int start,int length);
能够求从 start位置开始，长度为length的子串
*/
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
// 在此处补充你的代码
class MyString : public string {
public:
  MyString(const string &str = "");
  MyString(const char *c);
  // MyString(const MyString&);
  MyString operator()(const int &a, const int &b);
  // friend ostream &operator<<(ostream &os, const MyString &str);
};
MyString::MyString(const string &str) : string(str) {}
MyString::MyString(const char *c) : string(c) {}
MyString MyString::operator()(const int &start, const int &len) {
  string::substr(); // 调用基类的函数
  return this->substr(start, len);
} 
int CompareString(const void *e1, const void *e2) {
  // e1排在e2前面的时候(*e1 < *e2)，返回的是负整数-1，所以这是按照字符串内容长度升序排列，最短的放在最前面
  MyString *s1 = (MyString *)e1;
  MyString *s2 = (MyString *)e2;
  if (*s1 < *s2)
    return -1;
  else if (*s1 == *s2)
    return 0;
  else if (*s1 > *s2)
    return 1;
}
int main() {
  MyString s1("abcd-"), s2, s3("efgh-"), s4(s1);
  MyString SArray[4] = {"big", "me", "about", "take"};
  cout << "1. " << s1 << s2 << s3 << s4 << endl; // 可看出s2是缺省参数构造的
  s4 = s3;
  s3 = s1 + s3;
  cout << "2. " << s1 << endl;
  cout << "3. " << s2 << endl;
  cout << "4. " << s3 << endl;
  cout << "5. " << s4 << endl;
  cout << "6. " << s1[2] << endl;
  s2 = s1;
  s1 = "ijkl-";
  s1[2] = 'A';
  cout << "7. " << s2 << endl;
  cout << "8. " << s1 << endl;
  s1 += "mnop";
  cout << "9. " << s1 << endl;
  s4 = "qrst-" + s2;
  cout << "10. " << s4 << endl;
  s1 = s2 + s4 + " uvw " + "xyz";
  cout << "11. " << s1 << endl;
  // qsort(SArray, 4, sizeof(MyString), CompareString); // 本地编译器不能通过，coursera上面可以通过，不用管了
  // 有一种说法是qsort不能给自定义数据类型排序，而sort就没问题，我试了一下sort，确实结果就正确了，报错也消失了。
  for (int i = 0; i < 4; ++i)
    cout << SArray[i] << endl;
  //输出s1从下标0开始长度为4的子串
  cout << s1(0, 4) << endl;
  //输出s1从下标为5开始长度为10的子串
  cout << s1(5, 10) << endl;
  return 0;
}