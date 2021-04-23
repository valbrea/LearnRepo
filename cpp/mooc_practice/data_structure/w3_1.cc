/*
1. 密码翻译
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在情报传递过程中，为了防止情报被截获，往往需要对情报用一定的方式加密，简单的加密算法虽然不足以完全避免情报被破译，但仍然能防止情报被轻易的识别。我们给出一种最简的的加密方法，对给定的一个字符串，把其中从a-y,A-Y的字母用其后继字母替代，把z和Z用a和A替代，则可得到一个简单的加密字符串。

输入
第一行是字符串的数目n。

其余n行每行一个字符串。

输出
输出每行字符串的加密字符串。

样例输入
1
Hello! How are you!

样例输出
Ifmmp! Ipx bsf zpv!
*/
#include <iostream>
#include <string>
using namespace std;
int main() {
  int n;
  cin >> n;
  cin.ignore();
  while (n--) {
    char ch;
    string str;
    while ((ch = getchar()) != '\n') {
      if (('A' <= ch && ch < 'z') || ('a' <= ch && ch < 'z'))
        ch += 1;
      else if (ch == 'Z')
        ch = 'A';
      else if (ch == 'z')
        ch = 'a';
      else
      ;
      str += ch;
    }
    cout << str << endl;
  }
  return 0;
}