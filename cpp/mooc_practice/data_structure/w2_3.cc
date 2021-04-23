// 同cpp_programming/w4_4.cc中的乘法部分
// 这里删除了除法和减法部分，修改了main中的输入以符合题目要求

/*
3. 大整数乘法
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
求两个不超过200位的非负整数的积。

输入
有两行，每行是一个不超过200位的非负整数，没有多余的前导0。

输出
一行，即相乘后的结果。结果里不能有多余的前导0，即如果结果是342，那么就不能输出为0342。

样例输入
12345678900
98765432100

样例输出
1219326311126352690000

提示
30%的数据，输入的两个整数不超过8位。
*/
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
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
class BigInt {
  int *ptr_;
  int digit_;
  int negative_;

public:
  BigInt(const int *ptr, const int &digit, const int &negative);
  BigInt(const string &str = "");
  BigInt(const BigInt &c);
  ~BigInt();
  string Out();
  BigInt inline &operator=(const BigInt &b);
  friend inline int Compare(const BigInt &a, const BigInt &b);
  friend inline BigInt ExtendFromLow(const int &digit, const BigInt &s);
  friend inline BigInt ExtendFromHigh(const int &digit, const BigInt &s);
  friend inline BigInt Shorten(const int &digit, const BigInt &s);
  friend inline BigInt operator+(const BigInt &a, const BigInt &b);
  friend inline BigInt operator-(const BigInt &a, const BigInt &b);
  friend inline BigInt operator*(const BigInt &a, const BigInt &b);
  friend inline BigInt operator/(const BigInt &a, const BigInt &b);
};
int main() {

  string a, b;
  // char op;
  cin >> a;
  // cin >> op;
  cin >> b;
  BigInt big_a(a);
  BigInt big_b(b);
  BigInt big_c;
  // switch (op) {
  // case '+':

  //   big_c = big_a + big_b;
  //   break;
  // case '-':
  //   big_c = big_a - big_b;
  //   break;
  // case '*':
  //   big_c = big_a * big_b;
  //   break;
  // case '/':
  //   big_c = big_a / big_b;
  //   break;
  // default:
  //   break;
  // }
  big_c = big_a * big_b;
  cout << big_c.Out() << endl;
  return 0;
}
BigInt::BigInt(const int *ptr, const int &digit, const int &negative = -1)
    : ptr_(), digit_(digit), negative_(negative) {

  ptr_ = new int[digit];
  for (int i(0); i < digit_; ++i)
    ptr_[i] = ptr[i];
}
BigInt::BigInt(const string &str) : ptr_(), digit_(0), negative_(-1) {

  digit_ = str.length();
  ptr_ = new int[digit_];

  for (int i(0), j(digit_ - 1); j >= 0; --j, ++i) {

    string s_tmp = str.substr(i, 1);
    ptr_[j] = atoi(s_tmp.c_str());
  }
}
BigInt::BigInt(const BigInt &c) {
  if (c.ptr_) {
    ptr_ = new int[c.digit_];
    for (int i(0); i < c.digit_; ++i)
      ptr_[i] = c.ptr_[i];
    digit_ = c.digit_;
    negative_ = c.negative_;
  } else {
    ptr_ = NULL;
    digit_ = 0;
    negative_ = 0;
  }
}
BigInt::~BigInt() {
  if (ptr_)
    delete[] ptr_;
}
string BigInt::Out() {

  string s_out;

  if (negative_ == 0)
    return "0";
  char *temp = new char[digit_];
  for (int i(digit_ - 1); i >= 0; --i) {
    sprintf(temp, "%d", ptr_[i]);
    s_out = s_out + temp;
  }

  int pos = s_out.find_first_not_of("0", 0);
  s_out.erase(0, pos);
  if (negative_ > 0)
    s_out.insert(0, "-");
  return s_out;
}
inline BigInt &BigInt::operator=(const BigInt &b) {
  if (ptr_ == b.ptr_)
    return *this;
  if (ptr_)
    delete[] ptr_;
  if (b.ptr_) {
    ptr_ = new int[b.digit_];
    for (int i(0); i < b.digit_; ++i)
      ptr_[i] = b.ptr_[i];
    digit_ = b.digit_;
    negative_ = b.negative_;
  } else {
    ptr_ = NULL;
    digit_ = 0;
    negative_ = 0;
  }
  return *this;
}
inline int Compare(const BigInt &a, const BigInt &b) {

  if (a.digit_ > b.digit_) {
    return 1;
  } else if (a.digit_ < b.digit_) {
    return -1;
  } else {

    for (int i(a.digit_ - 1); i >= 0; --i) {
      if (a.ptr_[i] > b.ptr_[i]) {
        return 1;
        break;
      } else if (a.ptr_[i] < b.ptr_[i]) {
        return -1;
        break;
      } else {
        continue;
      }
    }
    return 0;
  }
}
inline BigInt ExtendFromLow(const int &digit, const BigInt &s = BigInt()) {

  int digit_ext = digit;
  int *ptr_ext;
  ptr_ext = new int[digit_ext];
  if (s.ptr_) {
    for (int i(0); i < s.digit_; ++i)
      ptr_ext[i] = s.ptr_[i];
    for (int i(s.digit_); i < digit_ext; ++i)
      ptr_ext[i] = 0;
  } else {
    for (int i(0); i < digit_ext; ++i)
      ptr_ext[i] = 0;
  }
  return BigInt(ptr_ext, digit_ext);
}
inline BigInt ExtendFromHigh(const int &digit, const BigInt &s = BigInt()) {

  int digit_ext = digit;
  int *ptr_ext;
  ptr_ext = new int[digit_ext];
  if (s.ptr_) {

    for (int i(digit_ext - 1); i >= (digit_ext - s.digit_); --i)
      ptr_ext[i] = s.ptr_[i - (digit_ext - s.digit_)];

    for (int i(digit_ext - s.digit_ - 1); i >= 0; --i)
      ptr_ext[i] = 0;
  } else {
    for (int i(0); i < digit_ext; ++i)
      ptr_ext[i] = 0;
  }
  return BigInt(ptr_ext, digit_ext);
}
inline BigInt Shorten(const int &digit, const BigInt &s = BigInt()) {

  int digit_ext = digit;
  int *ptr_ext;
  ptr_ext = new int[digit_ext];
  for (int i(digit_ext - 1); i >= 0; --i)
    ptr_ext[i] = s.ptr_[i - (digit_ext - s.digit_)];

  return BigInt(ptr_ext, digit_ext);
}
inline BigInt operator+(const BigInt &a, const BigInt &b) {

  BigInt tmp_a, tmp_b;
  tmp_a = ExtendFromLow((a.digit_ >= b.digit_ ? a.digit_ : b.digit_), a);
  tmp_b = ExtendFromLow((a.digit_ >= b.digit_ ? a.digit_ : b.digit_), b);
  int carry(0);

  int digit_c = (tmp_a.digit_ + 1);
  int *ptr_c = new int[digit_c];

  for (int i(0); i < tmp_a.digit_; ++i) {
    ptr_c[i] = tmp_a.ptr_[i] + tmp_b.ptr_[i] + carry;
    if (ptr_c[i] > 9) {
      carry = 1;
      ptr_c[i] -= 10;
    } else {
      carry = 0;
    }
  }

  if (carry != 0) {
    ptr_c[digit_c - 1] = carry;
  }
  return BigInt(ptr_c, digit_c);
}

inline BigInt operator*(const BigInt &a, const BigInt &b) {

  int digit_c = a.digit_ + b.digit_ + 1;
  BigInt tmp_a, tmp_b;
  tmp_a = ExtendFromLow(digit_c, a);
  tmp_b = ExtendFromLow(digit_c, b);

  int carry = 0;

  int *ptr_c = new int[digit_c];
  for (int i(0); i < digit_c; ++i)
    ptr_c[i] = 0;
  for (int j(0); j < b.digit_; ++j) {
    for (int i(0); i < a.digit_; ++i) {

      ptr_c[i + j] += tmp_a.ptr_[i] * tmp_b.ptr_[j] + carry;
      if (ptr_c[i + j] > 9) {
        carry = ptr_c[i + j] / 10;
        ptr_c[i + j] -= 10 * carry;
      } else {
        carry = 0;
      }
    }
    if (carry != 0) {
      ptr_c[a.digit_ + j] += carry;
    }
    carry = 0;
  }
  return BigInt(ptr_c, digit_c);
}
