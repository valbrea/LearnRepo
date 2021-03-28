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
  long long *ptr_;
  long long seg_;

public:
  BigInt(const string &str = "");
  ~BigInt();
  string &out();
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
  switch (op) {
  case '+':
    big_c = big_a + big_b;
    break;
  case '-':
    big_c = big_a - big_b;
    break;
  case '*':
    big_c = big_a * big_b;
    break;
  case '/':
    big_c = big_a / big_b;
    break;
  default:
    break;
  }
  cout << big_c.out() << endl;
  return 0;
}
BigInt::BigInt(const string &str) : seg_(0) {
  // long long类型显示成十进制最多有19个字符
  int llbit_dec = to_string(LLONG_MAX).length();
  if (str.length() % llbit_dec == 0) { // 每隔19个字符隔断一次
    seg_ = str.length() / llbit_dec;
  } else {
    seg_ = str.length() / llbit_dec + 1;
  }
  ptr_ = new long long[seg_];
  for (int i(0), j(0); j < seg_; ++j) {
    string s_tmp = str.substr(i, i += llbit_dec); // 每隔19个字符分一个子字符串
    ptr_[j] = stoll(s_tmp.c_str()); // 把子字符串转化成long long储存到ptr_的对应位置
  }
}
BigInt::~BigInt() {
  if (ptr_)
    delete[] ptr_;
}
string &BigInt::out() {
  string s_out;
  // long long类型转化成string类型，并用'+'拼接在一起
  for (int i(0); i < seg_; ++i)
    s_out += to_string(ptr_[i]);
  return s_out;
}
BigInt &BigInt::operator+(const BigInt &b) {
  string s_sum;                // 最后输入BigInt的参数
  unsigned long long tmpll(0); // 暂时的和
  unsigned long long carry(0); // 进位
  for (int i(seg_); i >= 0; --i) { // 要从后面的字串往前面加
    tmpll = ptr_[i] + b.ptr_[i] + carry; // 两个LLONG_MAX相加等于ULLONG_MAX-1，不会溢出
    if (tmpll > LLONG_MAX) {     // 如果大于了LLONG_MAX
/***********************************************************************
 * 弃用这种思路的原因，每两个long long相加以后，虽然达到了LLONG_MAX的上限，
 * 但是转化成字符串的时候，并没有到达十进制计算需要进位时，19位都是'9'的这个大小，
 * 所以无法算出给下个子字符串多少进位合适。解决方法可以是：
 * 1. 每次只录入18位，然后第19位用作记录进位，加到下一个子字符串
 * 2. 使用数位的方法，详见https://blog.kedixa.top/2017/cpp-bigint-overview/
 * 3. 最简单的字符串倒置然后每一位从后往前加，再进位
***********************************************************************/
      s_sum += to_string(tmpll); // 转化成long long类型就会去掉最高位
      carry >>= 64;
    } else {
      s_sum += to_string((long long)ptr_[i] + b.ptr_[i] -);
    }
  }
}
BigInt &BigInt::operator-(const BigInt &b) {}
BigInt &BigInt::operator*(const BigInt &b) {}
BigInt &BigInt::operator/(const BigInt &b) {}