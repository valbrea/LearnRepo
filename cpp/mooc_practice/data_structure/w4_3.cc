/*
3. 前缀中的周期
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 3000ms 内存限制: 65536kB

描述
一个字符串的前缀是从第一个字符开始的连续若干个字符，例如"abaab"共有5个前缀，分别是a,
ab, aba, abaa,  abaab。

我们希望知道一个N位字符串S的前缀是否具有循环节。换言之，对于每一个从头开始的长度为
i （i 大于1）的前缀，是否由重复出现的子串A组成，即 AAA...A （A重复出现K次,K 大于
1）。如果存在，请找出最短的循环节对应的K值（也就是这个前缀串的所有可能重复节中，最大的K值）。

输入
输入包括多组测试数据。每组测试数据包括两行。

第一行包括字符串S的长度N（2 <= N <= 1 000 000）。

第二行包括字符串S。

输入数据以只包括一个0的行作为结尾。

输出
对于每组测试数据，第一行输出 "Test case #“ 和测试数据的编号。

接下来的每一行，输出前缀长度i和重复测数K，中间用一个空格隔开。前缀长度需要升序排列。

在每组测试数据的最后输出一个空行。

样例输入
3
aaa
12
aabaabaabaab
0
样例输出
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4
*/
#include <iostream>
#include <map>
#include <string>
using namespace std;

int FindCycles(string &s) {
  int cycle_count(1);
  for (int i(1); i < s.size(); ++i) {
    string pre = s.substr(0, i);
    string last = s.substr(i, s.size() - i);
    while (last.substr(0, i) == pre) {
      ++cycle_count;
      last = last.substr(i, last.size() - i);
    }
    // 因为要找最短循环节对应的周期数 所以i最短的时候,一旦发现返回就可以了
    if (last.size() == 0)
      return cycle_count;
    else
      cycle_count = 1;
  }
  return 0;
}
int main() {
  int len;
  int case_cnt(0);
  while (cin >> len && len != 0) {
    string input;
    cin.ignore();
    getline(cin, input);
    map<int, int> cycle;
    for (int i(1); i <= input.size(); ++i) {
      string prefix = input.substr(0, i); // 长度为i的前缀
      cycle.insert(make_pair(i, FindCycles(prefix)));
    }
    map<int, int>::iterator ii;
    cout << "Test case #" << ++case_cnt << endl;
    for (ii = cycle.begin(); ii != cycle.end(); ++ii) {
      if (ii->second == 0)
        continue;
      cout << ii->first << " " << ii->second << endl;
    }
  }

  return 0;
}
