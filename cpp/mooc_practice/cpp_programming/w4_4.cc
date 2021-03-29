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
  BigInt(const int *ptr, const int &digit, const int &negative);
  BigInt(const string &str = "");
  BigInt(const BigInt &c); // 复制构造函数
  ~BigInt();               // 析构函数
  string Out();            // 用来输出的函数
  BigInt &operator=(const BigInt &b);
  /**************************************************************************************/
  friend int Compare(const BigInt &a, const BigInt &b);
  // 用来比较的函数, 如果a>b 返回1，a==b返回0，a<b返回
  // 声明为友元而不是成员函数的原因是为了在操作符重载函数（非成员函数）中使用，否则无法访问私有成员
  // 而且比较函数也不需要调用成员a,来实现a.Compare()
  /**************************************************************************************/
  friend BigInt Extend(const int &digit, const BigInt &s);
  // 这个函数用来扩展某个对象的空间至digit位，使其低位和对象s相同，高
  // 如果不填s，就默认里面是个空串位补'0'，同样也不需要使用a.Extend()这种形式，所以也是友元而非成员函数
  /**************************************************************************************/
  // 加减乘除的返回值不要加&，因为重载运算符函数中会返回构造函数生成的局部对象，
  // 如果加了引用&，返回的是该临时对象的地址，在函数结束后就会找不到该对象
  // 而=重构的返回值加&的原因是*this，而且需要返回的值是一个可修改的左值，否则无法连续赋值
  // 这里最好用普通友元函数，因为用成员函数的时候由于会对a进行借位或进位的操作，
  // 从而导致a的值被修改，导致后续错误！！
  friend BigInt operator+(const BigInt &a, const BigInt &b);
  friend BigInt operator-(const BigInt &a, const BigInt &b);
  // friend BigInt operator*(const BigInt &a, const BigInt &b);
  // friend BigInt operator/(const BigInt &a, const BigInt &b);
  /**************************************************************************************/
};
int main() {
  // 由于在类中已经声明过友元函数了，所以Compare(),
  // Extend()这些函数相当于已经在main函数前声明过了
  string a, b;
  char op;
  cin >> a;
  cin >> op;
  cin >> b;
  BigInt big_a(a);
  BigInt big_b(b);
  BigInt big_c;
  switch (op) { // switch case里面如果有初始化 一定要加{}
  case '+':
    // 这里直接调用了=，要重载operator=()
    big_c = big_a + big_b;
    break;
  case '-':
    big_c = big_a - big_b;
    break;
  // case '*':
  //   big_c = big_a * big_b;
  //   break;
  // case '/':
  //   big_c = big_a / big_b;
  //   break;
  default:
    break;
  }
  // cout << big_a.Out() << endl;
  // cout << big_b.Out() << endl;
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
    negative_ = c.negative_;
  } else {
    ptr_ = nullptr;
    digit_ = 0;
    negative_ = 0;
  }
}
BigInt::~BigInt() {
  if (ptr_)
    delete[] ptr_;
}
string BigInt::Out() {
  // 输出时候，先把BigInt变成string，再删除前面多余的0，再插入负号。
  // 这个顺序是因为用find_first_not_of()的时候如果先插入了负号，指针就会在负号的位置停下，而不是最高有效位。
  string s_out;
  // 从后往前将int数组转化成string类型，并用'+'拼接在一起
  if (negative_ == 0)
    return "0";
  for (int i(digit_ - 1); i >= 0; --i)
    s_out += to_string(ptr_[i]);
  // 要删掉输出字符串前面所有多余的0
  // find()系列函数第一个参数是找哪个字符串，第二个参数是从哪个位置开始找
  // find_first_not_of()是找第一个'与目标串中的任意一个字符都不相同'的字符的位置
  int pos = s_out.find_first_not_of("0", 0);
  s_out.erase(0, pos);
  if (negative_ > 0)
    s_out.insert(0, "-"); // 如果是负数，在第0位插入负号
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
    negative_ = b.negative_;
  } else {
    ptr_ = nullptr;
    digit_ = 0;
    negative_ = 0;
  }
  return *this;
}
int Compare(const BigInt &a, const BigInt &b) {
  // 用来比较的函数, 如果a>b 返回1，a==b返回0，a<b返回
  // 声明为友元而不是成员函数的原因是为了在操作符重载函数（非成员函数）中使用，否则无法访问私有成员
  // 而且比较函数也不需要调用成员a,来实现a.Compare()
  bool same = false;
  if (a.digit_ > b.digit_) {
    return 1;
  } else if (a.digit_ < b.digit_) {
    return -1;
  } else {
    // a,b位数一样的时候，要从高位往低位判断
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
    return 0; // 跑完循环都还没return，那就是一样大，返回0
  }
}
BigInt Extend(const int &digit, const BigInt &s = BigInt()) {
  // 这个函数用来扩展某个对象的空间至digit位，使其低位和对象s相同，高
  // 如果不填s，就默认里面是个空串位补'0'，同样也不需要使用a.Extend()这种形式，所以也是友元而非成员函数
  int digit_ext = digit;
  int *ptr_ext;
  ptr_ext = new int[digit_ext];
  if (s.ptr_) {
    for (int i(0); i < s.digit_; ++i)
      ptr_ext[i] = s.ptr_[i];
    for (int i(s.digit_); i < digit_ext; ++i)
      ptr_ext[i] = 0;
  } else { // 如果是默认空串，那么全部位都填成0
    for (int i(0); i < digit_ext; ++i)
      ptr_ext[i] = 0;
  }
  return BigInt(ptr_ext, digit_ext);
}
BigInt operator+(const BigInt &a, const BigInt &b) {
  // 由于不能直接操作const类型的对象，只能构造个新的临时a和临时b出来
  // 坚持用const是为了防止改变a和b里面的值，不能出现四则运算以后，原来的数字改变的情况
  // 特别是在有借位的时候很容易出现这种错误！
  // 如果a的位数小于b的位数，先要扩展a的空间和b一样，否则要扩展b的空间，前面补0；
  // 最后相加的时候高位直接就可以c = 0 + b或者c = a + 0；
  // 而不需要分情况讨论再先加低位后复制高位了。
  // 直接调用Extend()函数
  BigInt tmp_a, tmp_b;
  tmp_a = Extend((a.digit_ >= b.digit_ ? a.digit_ : b.digit_), a);
  tmp_b = Extend((a.digit_ >= b.digit_ ? a.digit_ : b.digit_), b);
  int carry(0); // 进位，最低位是0
  // 输出c的位数，在做加法时只需要比a的空间大1(这时a，b位数相同)
  int digit_c = (tmp_a.digit_ + 1);
  int *ptr_c = new int[digit_c]; // 存储最后结果的空间，输出
  // 顺序相加就可以了，因为是逆序存放的
  // 加到a和b的最高位,计算时需要加上前一位的进位
  for (int i(0); i < tmp_a.digit_; ++i) {
    ptr_c[i] = tmp_a.ptr_[i] + tmp_b.ptr_[i] + carry;
    if (ptr_c[i] > 9) { // 如果数字相加出现进位，记录进位，并删掉最高位
      carry = 1;
      ptr_c[i] -= 10;
    } else {
      carry = 0;
    }
  }
  // 如果循环到a的最高位，还有进位
  if (carry != 0) {
    ptr_c[digit_c - 1] = carry; // 进位存到c的最高位
  }
  return BigInt(ptr_c, digit_c);
}
BigInt operator-(const BigInt &a, const BigInt &b) {
  int digit_c;
  int *ptr_c;                      // 存储最后结果的空间，输出
  int negative_c = -Compare(a, b); // a > b, c就是个正数，negative_c < 0
  BigInt minuend, subtractor;
  if (negative_c < 0) {
    // a > b
    minuend = a;
    subtractor = Extend(a.digit_, b);
    digit_c = a.digit_; // 减法输出c的位数，和被减数一样即可
    ptr_c = new int[digit_c];
  } else if (negative_c > 0) {
    // b > a
    minuend = b;
    subtractor = Extend(b.digit_, a);
    digit_c = b.digit_; // 减法输出c的位数，和被减数一样即可
    ptr_c = new int[b.digit_];
  } else {
    // a = b
    digit_c = 1;
    ptr_c = new int[1];
    ptr_c[0] = 0;
    // 返回值要包含negative，输出的时候用来判断是否输出负号或者0
    return BigInt(ptr_c, digit_c, negative_c);
  }
  int borrow; // 减法需要借位
  for (int i(0); i < minuend.digit_; ++i) {
    if (minuend.ptr_[i] < subtractor.ptr_[i]) { // 如果该位需要借位
      minuend.ptr_[i] += 10;
      borrow = 1;
      minuend.ptr_[i + 1] -= borrow; // 高位-1，如果高位是0，也可以减成负数
    } else {
      borrow = 0;
    }
    ptr_c[i] = minuend.ptr_[i] - subtractor.ptr_[i]; // c[i] = a[i] - b[i];
  }
  if (borrow == 1)
    cout
        << "\'-\' error"; // 如果最后还要借位，肯定就出错了，因为已经判断过大小了
  return BigInt(ptr_c, digit_c, negative_c);
}
// BigInt operator*(const BigInt &a, const BigInt &b) {
//   int msb; // 记录a的最高有效位
//   // 如果a有x位，b有y位，乘完后最多有(x+1) + (y+1) - 1 == x + y + 1位；
//   // 所以a要扩展到这么多位
//   int *ptr_a = new int[digit_ + b.digit_ + 1];
//   // 顺序排放，0是低位，digit_ - 1是高位
//   // 先把低位复制，高位放'0'
//   for (int i(0); i < digit_; ++i)
//     ptr_a[i] = ptr_[i];
//   for (int i(digit_); i < digit_ + b.digit_ + 1; ++i)
//     ptr_a[i] = 0;
//   msb = digit_;
//   digit_ += b.digit_ + 1;
//   delete[] ptr_;
//   ptr_ = ptr_a;
//   ptr_a = nullptr;

//   int carry(0); // 进位，最低位是0
//   // a与b的每一位相乘，然后把所有和按照位数相加
//   for (int j(0); j < b.digit_; ++j) { // b的每一位都要和a相乘
//     for (int i(0); i < msb; ++i) {    // 每一轮加到a的最高有效位
//       // 要像手算一样，a和b到第j位相乘，就要记录到从第j位开始到到位置
//       ptr_[i + j] +=
//           ptr_[i] * b.ptr_[j] + carry; // 这里要用+=，因为每一轮都会加
//       if (ptr_[i + j] > 9) {           // 如果数字出现进位
//         carry = ptr_[i + j] / 10;      // 记录进位
//         ptr_[i + j] -= 10 * carry;     // 删掉高位
//       } else {
//         carry = 0;
//       }
//     }
//     if (carry != 0) { // 如果a的最高有效位还有进位
//       ptr_[msb + 1 + j] = carry;
//     }
//     carry = 0; // 每算完一轮，carry都要回0
//   }
//   return *this;
// }
// BigInt operator/(const BigInt &a, const BigInt &b) {
// 除法是从最高位往最低位计算
//   int msb;                 // 记录a的最高有效位
//   bool smaller = false;    // 如果a > b smaller就是false 否则是true
//   if (digit_ < b.digit_) { // 如果a位数更少， 直接就=0
//     delete[] ptr_;
//     digit_ = 1;
//     ptr_ = new int[1];
//     ptr_[0] = 0;
//   } else if (digit_ == b.digit_) { // 如果位数一样多
//     for (int i(digit_ - 1); i >= 0;
//          --i) { // 从高位往低位判断，如果a比b小就smaller
//       if (ptr_[i] < b.ptr_[i]) {
//         smaller = true;
//         break;
//       } else if (ptr_[i] > b.ptr_[i]) {
//         smaller = false;
//         break;
//       } else {
//         continue;
//       }
//     }
//     if (smaller == true) {
//       delete[] ptr_;
//       digit_ = 1;
//       ptr_ = new int[1];
//       ptr_[0] = 0;
//     }
//   } else { // 如果a的位数比较多，直接计算除法
//     // 除法从最高位开始
//     // 思路见：https://blog.csdn.net/ysz171360154/article/details/88956342
//     // 扩展b的位数
//     int *ptr_b = new int[digit_];
//     // 顺序排放，0是低位，digit_是高位
//     // 先把低位复制，高位放'0'
//     for (int i(0); i < b.digit_; ++i)
//       ptr_b[i] = ptr_[i];
//     for (int i(digit_); i < digit_; ++i)
//       ptr_b[i] = 0;
//     // b.digit_ = digit_;
//     // delete[] b.ptr_;
//     // ptr_ = ptr_b;
//     // ptr_b = nullptr;
//   }

//   return *this;
// }