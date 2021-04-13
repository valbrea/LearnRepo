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
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int *PrimeFactorNumber(int val) {
    // 找出val以内的所有素数
    // 素数是1，合数是0
    int sum;
    static int *prime = new int[val];
    memset(prime, 0, val * sizeof(int)); // 先全部置为1
  for (int i(2); i * i < val; ++i) {
      sum = i;
      if (prime[sum] == 0) {
          while (sum < val) {
              sum += i;
              if (sum < val) // if防止数组越界
                prime[sum] = 0;
          }
      }
  }
  return prime;
}
class Prior {
public:
  bool operator()(int num1, int num2) {}
};
int main() {
  int n;
  cin >> n;
  cin.ignore();
  while (n-- > 0) {
    priority_queue<int, deque<int>, Prior> nums;
    int temp;
    for (int i(0); i < 10; ++i) {
      cin >> temp;
      nums.push(temp);
    }
  }
  return 0;
}