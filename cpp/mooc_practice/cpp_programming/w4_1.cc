/*
编程题 ＃1
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
下面程序的输出是：

3+4i

5+6i

请补足Complex类的成员函数。不能加成员变量。
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
*/
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
class Complex {
private:
  double r, i;

public:
  void Print() { cout << r << "+" << i << "i" << endl; }
  // 在此处补充你的代码
  Complex &operator=(const string &s) {
    int pos = s.find("+", 0);
    string sTmp = s.substr(0, pos);
    r = atof(sTmp.c_str());
    sTmp = s.substr(pos + 1, s.length() - pos - 2);
    i = atof(sTmp.c_str());
    return *this; // 返回值不要写const Complex & 不然返回的值就和a不同类型了
  }
};
int main() {
  Complex a;
  a = "3+4i"; // 相当于a.operator=("3+4i")
  a.Print();
  a = "5+6i";
  a.Print();
  return 0;
}