/*
编程题＃6： priority queue练习题
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 2500ms 内存限制: 131072kB

描述
我们定义一个正整数a比正整数b优先的含义是：

*a的质因数数目（不包括自身）比b的质因数数目多；

*当两者质因数数目相等时，数值较大者优先级高。

现在给定一个容器，初始元素数目为0，之后每次往里面添加10个元素，每次添加之后，要求输出优先级最高与最低的元素，并把该两元素从容器中删除。

输入
第一行: num (添加元素次数，num <= 30)

下面10*num行，每行一个正整数n（n < 10000000).

输出
每次输入10个整数后，输出容器中优先级最高与最低的元素，两者用空格间隔。

样例输入
1
10 7 66 4 5 30 91 100 8 9

样例输出
66 5
*/
#include <algorithm>
#include <cmath>
#include <iostream>
// #include <queue>
using namespace std;
int *max_prime;
inline int *PrimeArray(int val) {
  int sum(0);
  int sqr = (int)sqrt(val);            // 质因数的上限sqr就是根号val
  static int *prime = new int[val]{0}; // 全部置0,不包括val自身所以不用+1
  // 找sqr以下的质数，用合数筛法, 质数为0，合数置为1
  for (int i(2); i <= sqr; ++i) {
    sum = i;
    if (prime[sum] == 0) { // 欧拉筛，防止同一个数被筛多次
      while (sum < val) {
        sum += i;      // 先+后置1防止2，3这些一开始的质数被置1
        if (sum < val) // if防止数组越界
          prime[sum] = 1;
      }
    }
  }
  return prime;
}
inline int PrimeFactorNumber(int val) {
  int count(0);
  for (int i(2); i < val; ++i) {
    if (max_prime[i] == 0 && val % i == 0)
      ++count;
  }
  return count;
}
// class Prior {
// public:
//   inline bool operator()(int num1, int num2) {
//     if (PrimeFactorNumber(num1) < PrimeFactorNumber(num2))
//       return true;
//     else if (PrimeFactorNumber(num1) == PrimeFactorNumber(num2))
//       return (num1 < num2 ? true : false);
//     else
//       return false;
//   }
// };
class Num {
public:
  int num_;
  int factor_num_;
  Num() : num_(0), factor_num_(0) {}
  Num(int num, int factor_num) : num_(num), factor_num_(factor_num) {}
  bool operator<(Num &num2) {
    if (factor_num_ < num2.factor_num_)
      return true;
    else if (factor_num_ == num2.factor_num_)
      return num_ < num2.num_ ? true : false;
    else
      return false;
  }
};
int main() {
  int n;
  cin >> n;
  cin.ignore();
  while (n-- > 0) {
    Num nums[10];
    int max(0);
    for (int i(0); i < 10; ++i) {
      cin >> nums[i].num_;
      if (nums[i].num_ > max)
        max = nums[i].num_;
    }
    max_prime = PrimeArray(max);
    for (int i(0); i < 10; ++i) {
      nums[i].factor_num_ = PrimeFactorNumber(nums[i].num_);
    }
    sort(nums, nums + 10);
    cout << nums[9].num_ << " " << nums[0].num_ << endl;
  }

  return 0;
}