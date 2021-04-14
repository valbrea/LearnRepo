/*
编程题＃5：计算数组的低3位之和
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 1024kB

描述
输入一个正整数构成的数组a[0], a[1], a[2], ... , a[n-1],
计算它们的二进制低3位之和。
输入
数组a,以0表示输入结束。

输出
一个整数 , 所输入数组各元素的二进制低3位之和。

样例输入
1 3 9 7 3 6 20 15 18 17 4 8 18 0

样例输出
41
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
// 在此处补充你的代码
class CMy_add {
    public:
    int &sum_; //只有引用my_sum才能直接修改它
    CMy_add(int &my_sum): sum_(my_sum) {}
    void operator()(int i) {
        sum_ += (i & 7); //位运算：保留低3位，其余置0
    }
};

int main(int argc, char *argv[]) {
  int v, my_sum = 0;
  vector<int> vec;
  cin >> v;
  while (v) {
    vec.push_back(v);
    cin >> v;
  }
  for_each(vec.begin(), vec.end(), CMy_add(my_sum));
  cout << my_sum << endl;
  return 0;
}