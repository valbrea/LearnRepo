/*
编程题＃7：字符串排序
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 1024kB

描述
请按照要求对输入的字符串进行排序。

输入
第一行是正整数T，表示测试数据的组数
每组测试数据输入共两行，
第一行是正整数N，表示字符串个数
第二行是N个字符串, 字符串间用空格分离

输出
对于每组测试数据，先输出一行：
Case: n
如对第一组数据就输出Case: 1
第二行按照字符串长度从小到大排序之后输出N个字符串，字符串之间以空格间隔（不会出现字符串长度相同的情况）
第三行按照字符串首字符ASCII码序从小到大排序之后输出N个字符串，字符串之间以空格间隔（不会出现字符串首字母相同的情况）

样例输入
2
4
a bnss ds tsdfasg
5
aaa bbbb ccccd sa q

样例输出
Case: 1
a ds bnss tsdfasg
a bnss ds tsdfasg
Case: 2
q sa aaa bbbb ccccd
aaa bbbb ccccd q sa
*/
#include <iostream>
#include <list>
#include <string>
using namespace std;

class A {
private:
  string name;

public:
  A(string n) : name(n) {}
  friend bool operator<(const class A &a1, const class A &a2);
  friend bool operator==(const class A &a1, const class A &a2) {
    if (a1.name.size() == a2.name.size())
      return true;
    else
      return false;
  }
  friend ostream &operator<<(ostream &o, const A &a) {
    o << a.name;
    return o;
  }
  string get_name() const { return name; }
  int get_size() const { return name.size(); }
};
// 在此处补充你的代码
bool operator<(const A &a1, const A &a2) {
  return a1.get_size() < a2.get_size();
}

template <class T> class MyLarge {
public:
  bool operator()(const T &a1, const T &a2) {
    return a1.get_name().at(0) < a2.get_name().at(0);
  }
};

// 方法2：Show是一个函数模板，Show()传入的是一个list<A>的迭代器，所以begin就是该类型的迭代器
// Print传入的是*begin，也就是一个A类型的对象的引用
// 不过用这种方法不太好，函数模板毫无必要，因为Print()只能传入A类型的对象引用，所以如果*It指向别的类型就会报错
// 而且也不能把Print()写成类模板，因为show()里面调用的Print()并没有传入实参，所以无法通过传入实参实例化出Print的一个模板类
class Print {
public:
  void operator()(A &a) { cout << a.get_name() << " "; }
};

template <class It> void Show(It begin, It last, Print p) {
  for (; begin != last; ++begin)
    p(*begin);
}

int main(int argc, char *argv[]) {
  list<A> lst;
  int ncase, n, i = 1;
  string s;
  cin >> ncase;
  while (ncase--) {
    cout << "Case: " << i++ << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> s;
      lst.push_back(A(s));
    }
    lst.sort();
    Show(lst.begin(), lst.end(), Print());

    cout << endl;
    lst.sort(MyLarge<A>());
    Show(lst.begin(), lst.end(), Print());
    cout << endl;
    lst.clear();
  }
  return 0;
}