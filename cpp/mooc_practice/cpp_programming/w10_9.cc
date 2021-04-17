/*
编程题＃9：人群的排序和分类
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 1024kB

描述
对人群按照输入的信息进行排序和分类。
输入
第一行是整数t,表明一共t组数据. t < 20

对每组数据：

第一行是整数n,表示下面一共有n行。 0 < n < 100

下面的每行代表一个人。每行以一个字母开头，代表该人所属的类别，然后跟着一个整数，代表年龄。字母只会是
'A‘或‘B' 。整数范围0到100。数据保证年龄都不相同。

输出
对每组输入数据，将这些人按年龄从小到大输出。每个人先输出类别，再输出年龄。每组数据的末尾加一行
"****"

样例输入
2
4
A 3
B 4
A 5
B 6
3
A 4
A 3
A 2

样例输出
A 3
B 4
A 5
B 6
****
A 2
A 3
A 4
****
*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
using namespace std;
// 在此处补充你的代码
class A {
protected:
  int k_;

public:
  A(int k) : k_(k) {}
  virtual void PrintNum() { cout << "A " << k_ << endl; }
  friend class Comp;
};
class B : public A {
public:
  B(int k) : A(k) {}
  virtual void PrintNum() { cout << "B " << k_ << endl; }
  friend class Comp;
};
class Comp {
public:
  bool operator()(A *a, A *b) { return a->k_ < b->k_; }
};
void Print(A *a) { a->PrintNum(); }

int main() {
  int t;
  cin >> t;
  set<A *, Comp> ct;
  while (t--) {
    int n;
    cin >> n;
    ct.clear();
    for (int i = 0; i < n; ++i) {
      char c;
      int k;
      cin >> c >> k;

      if (c == 'A')
        ct.insert(new A(k));
      else
        ct.insert(new B(k));
    }
    for_each(ct.begin(), ct.end(), Print);
    cout << "****" << endl;
  }
}