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
  int negative_; // 用来记录减法最后是不是负数

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
  // cout << big_a.out() << endl;
  switch (op) { // switch case里面如果有初始化 一定要加{}
  case '+': {
    // 这里直接调用了=，要重载operator=()
    big_c = big_a + big_b;
    break;
  }
  case '-': {
    big_c = big_a - big_b;
    break;
  }
  case '*': {
    big_c = big_a * big_b;
    break;
  }
  case '/': {
    big_c = big_a / big_b;
    break;
  }
  default: {
    break;
  }
  }
  cout << big_a.out() << endl;
   cout << big_b.out() << endl;
  cout << big_c.out() << endl;
  return 0;
}
BigInt::BigInt(const int *ptr, const int &digit)
    : ptr_(), digit_(digit), negative_(-1) {
  ptr_ = new int[digit];
  for (int i(0); i < digit_; ++i)
    ptr_[i] = ptr[i];
}
BigInt::BigInt(const string &str) : ptr_(), digit_(0), negative_(-1) {
  // 每一位的数字（0～9）都储存到int数组中
  digit_ = str.length();
  ptr_ = new int[digit_];
  for (int i(0), j(digit_ - 1); j >= 0; --j, ++i) {
    // 逆序存放比较合理，这样加的时候就可以顺序加
    string s_tmp = str.substr(i, 1); // 每次从i开始，每次截取长度为1
    ptr_[j] = atoi(s_tmp.c_str());
  }
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
  if (negative_ > 0)
    s_out = "-"; // 如果是负数先输入负号
  for (int i(digit_ - 1); i >= 0; --i)
    s_out += to_string(ptr_[i]);
  return s_out;
}
BigInt &BigInt::operator=(const BigInt &b) {
  if (ptr_ == b.ptr_)
    return *this;
  if (ptr_)
    delete[] ptr_;
  if (b.ptr_) {
    ptr_ = new int[b.digit_];
    for (int i(0); i < b.digit_; ++i)
      ptr_[i] = b.ptr_[i];
    digit_ = b.digit_;
  } else {
    ptr_ = nullptr;
    digit_ = 0;
  }
  return *this;
}
BigInt &BigInt::operator+(const BigInt &b) {
  // 如果a的位数小于b的位数，先要扩展a的空间和b一样
  if (digit_ < b.digit_) {
    int *ptr_a = new int[b.digit_];
    // 顺序排放，0是低位，digit_是高位
    // 先把低位复制，高位放'0'
    for (int i(0); i < digit_; ++i)
      ptr_a[i] = ptr_[i];
    for (int i(digit_); i < b.digit_; ++i)
      ptr_a[i] = 0;
    digit_ = b.digit_;
    delete[] ptr_;
    ptr_ = ptr_a;
    ptr_a = nullptr;
  }
  int carry(0); // 进位，最低位是0
  // 顺序相加就可以了
  for (int i(0); i < digit_;
       ++i) { // 先加到a的最高位,计算时需要加上前一位的进位
    ptr_[i] += b.ptr_[i] + carry;
    if (ptr_[i] > 9) { // 如果数字相加出现进位，记录进位，并删掉最高位
      carry = 1;
      ptr_[i] -= 10;
    } else {
      carry = 0;
    }
  }
  if (carry != 0) { // 如果a的最高位还有进位，需要扩展空间
    int *ptr_tmp = new int[digit_ + 1]; // 生成临时空间，比原空间+1
    for (int i(0); i < digit_; ++i)
      ptr_tmp[i] = ptr_[i];
    ptr_tmp[digit_] = carry; // 进位存到的最高位
    delete[] ptr_;           // 删掉原本a的空间
    ptr_ = ptr_tmp;          // 再把a的指针指向这片临时空间
    digit_ = digit_ + 1;
    ptr_tmp = nullptr;
  }
  return *this;
}
BigInt &BigInt::operator-(const BigInt &b) {
  int msb;          // 记录a的最高有效位
  int negative = -1; // 如果a < b negative就是1 相等是0 否则是-1；
  // 如果a的位数小于b的位数，先要扩展a的空间和b一样
  if (digit_ < b.digit_) {
    int *ptr_a = new int[b.digit_];
    // 顺序排放，0是低位，digit_是高位
    // 先把低位复制，高位放'0'
    for (int i(0); i < digit_; ++i)
      ptr_a[i] = ptr_[i];
    for (int i(digit_); i < b.digit_; ++i)
      ptr_a[i] = 0;
    msb = digit_; // 记录a的最高有效位 0～msb-1 一共msb位
    negative = 1;
    digit_ = b.digit_;
    delete[] ptr_;
    ptr_ = ptr_a;
    ptr_a = nullptr;
  } else if (digit_ == b.digit_) { // 如果位数一样多
    for (int i(digit_ - 1); i >= 0;
         --i) { // 从高位往低位判断，如果a比b小就negative
      if (ptr_[i] < b.ptr_[i]) {
        negative = 1;
        break; // 如果高位大，就直接break出去
      } else if (ptr_[i] > b.ptr_[i]) {
        negative = -1; // 如果高位小，也直接break出去
        break;
      } else {
        negative = 0;
        continue; // 如果一样大，就查找下一位
      }
    }
  } else { // 如果a的位数比较多，直接减b
    negative = -1;
  }

  int borrow(0);      // 减法需要借位
  if (negative < 0) { // 不需要翻转的话，计算到b的最高位就可以了
    for (int i(0); i < b.digit_; ++i) {
      if (ptr_[i] < b.ptr_[i]) { // 如果该位需要借位
        ptr_[i] += 10;
        borrow = 1;
        ptr_[i + 1] -= borrow; // 高位-1，如果高位是0，也可以减成负数
      } else {
        borrow = 0;
      }
      ptr_[i] -= b.ptr_[i]; // a[i] = a[i] - b[i];
    }
    if (borrow == 1)
      cout << "\'-\' error"; // 如果最后还要借位，肯定就出错了，因为已经判断过大小了
  } else if (negative > 0) { // 如果需要反转，需要使用msb
    for (int i(0); i < digit_; ++i) {
      if (b.ptr_[i] < ptr_[i]) {
        b.ptr_[i] += 10;
        borrow = 1;
        b.ptr_[i + 1] -= borrow;
      } else {
        borrow = 0;
      }
      ptr_[i] = b.ptr_[i] - ptr_[i]; // a[i] = b[i] - a[i]
    }
    negative_ = negative; // 最后加个负号
    if (borrow == 1)
      cout << "\'-\' error"; // 如果最后还要借位，肯定就出错了
  } else { // negative == 0，输出就只有一位，返回一个只有"0"的成员
    delete[] ptr_;
    digit_ = 1;
    ptr_ = new int[1];
    ptr_[0] = 0;
  }
  return *this;
}
BigInt &BigInt::operator*(const BigInt &b) {
  int msb; // 记录a的最高有效位
  // 如果a有x位，b有y位，乘完后最多有(x+1) + (y+1) - 1 == x + y + 1位；
  // 所以a要扩展到这么多位
  int *ptr_a = new int[digit_ + b.digit_ + 1];
  // 顺序排放，0是低位，digit_ - 1是高位
  // 先把低位复制，高位放'0'
  for (int i(0); i < digit_; ++i)
    ptr_a[i] = ptr_[i];
  for (int i(digit_); i < digit_ + b.digit_ + 1; ++i)
    ptr_a[i] = 0;
  msb = digit_;
  digit_ += b.digit_ + 1;
  delete[] ptr_;
  ptr_ = ptr_a;
  ptr_a = nullptr;

  int carry(0); // 进位，最低位是0
  // a与b的每一位相乘，然后把所有和按照位数相加
  for (int j(0); j < b.digit_; ++j) { // b的每一位都要和a相乘
    for (int i(0); i < msb; ++i) {    // 每一轮加到a的最高有效位
      // 要像手算一样，a和b到第j位相乘，就要记录到从第j位开始到到位置
      ptr_[i + j] +=
          ptr_[i] * b.ptr_[j] + carry; // 这里要用+=，因为每一轮都会加
      if (ptr_[i + j] > 9) {           // 如果数字出现进位
        carry = ptr_[i + j] / 10;      // 记录进位
        ptr_[i + j] -= 10 * carry;     // 删掉高位
      } else {
        carry = 0;
      }
    }
    if (carry != 0) { // 如果a的最高有效位还有进位
      ptr_[msb + 1 + j] = carry;
    }
    carry = 0; // 每算完一轮，carry都要回0
  }
  return *this;
}
BigInt &BigInt::operator/(const BigInt &b) {
  // 除法是从最高位往最低位计算
  int msb;                 // 记录a的最高有效位
  bool smaller = false;    // 如果a > b smaller就是false 否则是true
  if (digit_ < b.digit_) { // 如果a位数更少， 直接就=0
    delete[] ptr_;
    digit_ = 1;
    ptr_ = new int[1];
    ptr_[0] = 0;
  } else if (digit_ == b.digit_) { // 如果位数一样多
    for (int i(digit_ - 1); i >= 0;
         --i) { // 从高位往低位判断，如果a比b小就smaller
      if (ptr_[i] < b.ptr_[i]) {
        smaller = true;
        break;
      } else if (ptr_[i] > b.ptr_[i]) {
        smaller = false;
        break;
      } else {
        continue;
      }
    }
    if (smaller == true) {
      delete[] ptr_;
      digit_ = 1;
      ptr_ = new int[1];
      ptr_[0] = 0;
    }
  } else { // 如果a的位数比较多，直接计算除法
    // 除法从最高位开始
    // 思路见：https://blog.csdn.net/ysz171360154/article/details/88956342
    // 扩展b的位数
    int *ptr_b = new int[digit_];
    // 顺序排放，0是低位，digit_是高位
    // 先把低位复制，高位放'0'
    for (int i(0); i < b.digit_; ++i)
      ptr_b[i] = ptr_[i];
    for (int i(digit_); i < digit_; ++i)
      ptr_b[i] = 0;
    // b.digit_ = digit_;
    // delete[] b.ptr_;
    // ptr_ = ptr_b;
    // ptr_b = nullptr;
  }

  return *this;
}