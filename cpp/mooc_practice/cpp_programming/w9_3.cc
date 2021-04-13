/*
编程题＃3：Set
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 5000ms 内存限制: 100000kB

描述
现有一整数集（允许有重复元素），初始为空。我们定义如下操作：

add x 把x加入集合
del x 把集合中所有与x相等的元素删除
ask x 对集合中元素x的情况询问
对每种操作，我们要求进行如下输出。
add 输出操作后集合中x的个数
del 输出操作前集合中x的个数
ask
先输出0或1表示x是否曾被加入集合（0表示不曾加入），再输出当前集合中x的个数，中间用空格格开。

输入
第一行是一个整数n，表示命令数。0<=n<=100000。

后面n行命令，如Description中所述。

输出
共n行，每行按要求输出。

提示
Please use STL’s set and multiset to finish the task
*/
#include <iostream>
#include <set>
#include <string>
using namespace std;
int main() {
  int n;
  cin >> n;
  cin.ignore();
  //   typedef pair<int, bool> elem;
  multiset<int> int_set;
  set<int> added;
  while (n-- > 0) {
    string cmd;
    getline(cin, cmd, ' ');
    int operand;
    cin >> operand;
    cin.ignore();
    if (cmd == "add") {
      int_set.insert(operand);
      added.insert(operand);
      cout << int_set.count(operand) << endl;
    } else if (cmd == "del") {
      // 输出del操作前的个数
      cout << int_set.count(operand) << endl;
      if (int_set.find(operand) != int_set.end())
        int_set.erase(operand);
    } else if (cmd == "ask") {
      cout << added.count(operand) << " " << int_set.count(operand) << endl;
    } else {
    }
  }

  return 0;
}