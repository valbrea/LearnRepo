/*
链接：https://ac.nowcoder.com/acm/contest/13215/B
来源：牛客网

题目描述
小红有一个字符串，她每次操作可以改变一个字符的值。
对于'a'、'b'、'c'、……、'y'等小写字母，小红每次操作可以把该字母变成比它大一位的字母，即变成'b'、'c'、'd'、……、'z'。
对于'A'、'B'、'C'、……、'Y'等大写字母，小红每次操作可以把该字母变成比它大一位的字母，即变成'B'、'C'、'D'、……、'Z'。
对于'0'、'1'、'2'、……、'8'等数字，小红每次操作可以把该数字变成比它大一位的数字，即变成'1'、'2'、'3'、……、'9'。
对于一些特殊的字符：
1. 'z' 会变成 'A'。
2. 'Z' 会变成 '0'。
3. '9' 会变成 'a'。
现在小红想使这个字符串不存在任意相同的两个字符，你能输出这个最小的操作次数吗？

输入描述:
第一行一个正整数nn，代表字符串的长度。
接下来一个长度为nn的，仅包含小写字母、大写字母或数字的字符串。
(1 \leq n \leq 10^51≤n≤10
5
 )
输出描述:
如果小红无法达成目的，则输出 -1 ，否则输出最小的操作次数。
*/
#include <iostream>
#include <set>
using namespace std;
char Next(char ch) {
  if (isalnum(ch)) {
    switch (ch) {
    case 'z':
      ch = 'A';
      break;
    case 'Z':
      ch = '0';
      break;
    case '9':
      ch = 'a';
      break;
    default:
      ch += 1;
      break;
    }
  } else {
    cout << "error" << endl;
  }
  return ch;
}
int main() {
  int n;
  cin >> n;
  cin.ignore();
  char *str = new char[n];
  cin.getline(str, n + 1);
  set<char> uniq;
  typedef set<char>::iterator it;
  pair<it, bool> result;
  int count(0);
  for (int i(0); i < n; ++i) {
    result = uniq.insert(str[i]);
    while (!result.second) {
      result = uniq.insert((str[i] = Next(str[i])));
      ++count;
    }
  }
  cout << count << endl;

  return 0;
}