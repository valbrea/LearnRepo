/*
编程题＃5：字符串插入
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB、

描述
有两个字符串str和substr，str的字符个数不超过10，substr的字符个数为3。
（字符个数不包括字符串结尾处的'\0'。）
将substr插入到str中ASCII码最大的那个字符后面，若有多个最大则只考虑第一个。

输入
输入包括若干行，每一行为一组测试数据，格式为

str substr

输出
对于每一组测试数据，输出插入之后的字符串。
*/
#include <cstring>
#include <iostream>
using namespace std;
int main() {
  char str[14] = {0}, substr[4] = {0};
  while (cin.getline(str, 11, ' ') && cin.getline(substr, 4)) {
    char max(0);
    int max_index(0);
    // 找出最大的字符和对应位置
    for (int i(0); str[i] != 0; ++i) {
      if (str[i] > max) {
        max_index = i;
        max = str[i];
      }
    }
    // 从后往前移3格
    for (int i(strlen(str)); i > max_index; --i) {
      str[i + 3] = str[i];
    }
    // 把子串插入主串
    for (int i(max_index + 1); i < max_index + 4; ++i) {
      str[i] = substr[i - max_index - 1];
    }
    cout << str << endl;
  }

  return 0;
}