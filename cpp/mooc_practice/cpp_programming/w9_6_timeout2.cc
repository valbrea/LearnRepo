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
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;
bool IsPrime(int val) {
  // 判断某个数是不是质数，不需要用筛法
  // 详情见https://blog.csdn.net/sinat_26811377/article/details/96584293
  if (val <= 3)
    return val > 1;
  // 只有6x-1和6x+1的数才有可能是质数
  if (val % 6 != 1 && val % 6 != 5)
    return false;
  // 判断这些数能否被小于sqrt(n)的奇数整除
  // 最小正因数<=sqrt(val)，如果找到sqrt(val)还没找到最小正因数,那就是素数了
  for (int i = 5; i <= (int)sqrt(val); i += 6) {
    if (val % i == 0 || val % (i + 2) == 0)
      return false;
  }
  return true;
}
int PrimeFactorNumber(int val) {
  int count(0), checked(0), raw(val);
  bool counted(false); // counted用来记录是否计数过
  for (int i(2); i <= val; ++i) {
    while (val % i == 0) {
      if (!counted) {
        ++count;
        counted = true;
      }
      val /= i;
    }
    // checked用来防止出现这种情况，一个大的合数，最开始2，3，5，7都不是它的因数时被重复计算IsPrime()
    // 例如5*7*13，在检查i = 2,3,4的时候，checked 都== 5*7*13，所以不检查IsPrime()，
    // 但是当i=5进入过while循环以后，因为val == 7*13 != checked，就会再次检查7*13是不是质数。
    // 之后checked = 7*13，进入i = 6循环继续...
    if (checked != val && IsPrime(val)) {
      if (val == raw)
        return 0; // 如果输入的本身是一个质数的话，就要直接返回0
      ++count;
      checked == val;
      break;
    }
    counted = false; // 每个i的flag一开始都是false
  }
  return count;
}
class Prior {
public:
  bool operator()(int num1, int num2) {
    if (PrimeFactorNumber(num1) < PrimeFactorNumber(num2))
      return true;
    else if (PrimeFactorNumber(num1) == PrimeFactorNumber(num2))
      return (num1 < num2 ? true : false);
    else
      return false;
  }
};
int main() {
  int n;
  cin >> n;
  cin.ignore();
  while (n-- > 0) {
    priority_queue<int, deque<int>, Prior> nums;
    int val;
    for (int i(0); i < 10; ++i) {
      cin >> val;
      nums.push(val);
      // cout << "check: " << val << "->" << PrimeFactorNumber(val) << endl;
    }
    int top = nums.top();
    for (int i(0); i < 9; ++i)
      nums.pop();
    int tail = nums.top();
    cout << top << " " << tail << endl;
  }

  return 0;
}