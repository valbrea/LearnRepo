/*
编程题＃4：大整数的加减乘除
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)
注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
给出两个正整数以及四则运算操作符（+ - * /），求运算结果。

输入
第一行：正整数a，长度不超过100
第二行：四则运算符o，o是“+”，“-”，“*”，“/”中的某一个
第三行：正整数b，长度不超过100
保证输入不含多余的空格或其它字符

输出
一行：表达式“a o b”的值。

补充说明：
1. 减法结果有可能为负数
2. 除法结果向下取整
3. 输出符合日常书写习惯，不能有多余的0、空格或其它字符

样例输入
9876543210
+
9876543210

样例输出

19753086420
*/
#include <iostream>
#include <string>
using namespace std;
class BigInt {
  int *ptr_;
  int digit_;
  bool negative_; // 用来记录减法最后是不是负数

public:
  BigInt(const int *ptr, const int &digit);
  BigInt(const string &str = "");
  BigInt(const BigInt &c);
  ~BigInt();
  string out();
  BigInt &operator=(const BigInt &b);
  BigInt &operator+(const BigInt &b);
  BigInt &operator-(const BigInt &b);
  BigInt &operator*(const BigInt &b);
  BigInt &operator/(const BigInt &b);
};
int main() {
  string a, b;
  char op;
  cin >> a;
  cin >> op;
  cin >> b;
  BigInt big_a(a);
  BigInt big_b(b);
  BigInt big_c;
  cout << big_a.out() << endl;
  cout << big_b.out() << endl;
  cout << op << endl;
  return 0;
}
BigInt::BigInt(const int *ptr, const int &digit)
    : ptr_(), digit_(digit), negative_(false) {
  ptr_ = new int[digit];
  for (int i(0); i < digit_; ++i)
    ptr_[i] = ptr[i];
}
BigInt::BigInt(const string &str) : ptr_(), digit_(0), negative_(false) {
  // 每一位的数字（0～9）都储存到int数组中
  digit_ = str.length();
  // cout << "digit_" << digit_ << endl;
  ptr_ = new int[digit_];
  for (int i(0), j(digit_ - 1); j >= 0; --j, ++i) {
    // 逆序存放比较合理，这样加的时候就可以顺序加
    string s_tmp = str.substr(i, 1); // 每次从i开始，每次截取长度为1
    ptr_[j] = atoi(s_tmp.c_str());
  }
  // cout << ptr_[0] << ptr_[digit_] << endl;
}
BigInt::BigInt(const BigInt &c) {
  if (c.ptr_) {
    ptr_ = new int[c.digit_];
    for (int i(0); i < c.digit_; ++i)
      ptr_[i] = c.ptr_[i];
    digit_ = c.digit_;
  } else {
    ptr_ = nullptr;
    digit_ = 0;
  }
}
BigInt::~BigInt() {
  if (ptr_)
    delete[] ptr_;
}
string BigInt::out() {
  string s_out;
  // 从后往前将int数组转化成string类型，并用'+'拼接在一起
  // cout << to_string(ptr_[0]) << endl;
  if (negative_)
    s_out = "-"; // 如果是负数先输入负号
  for (int i(digit_ - 1); i >= 0; --i)
    s_out += to_string(ptr_[i]);
  return s_out;
}
