/*
1. 英语数字转换器
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在这个问题中，将用英语给你一个或多个整数。你的任务是将这些数字转换成整型表示。
数字范围从-999,999,999到999,999,999.下面是你的程序必须考虑的详尽的英语单词表：

negative, zero, one, two, three, four,five, six, seven, eight, nine, ten,
eleven, twelve, thirteen, fourteen,fifteen, sixteen, seventeen, eighteen,
nineteen, twenty, thirty, forty, fifty,sixty, seventy, eighty, ninety, hundred,
thousand, million

输入
输入包括多个样例，注意：

1.负数前面有词negative

2.当能用thousand的时候，将不用hundred。例如1500将写为"one thousand five
hundred",而不是"fifteen hundred".

输入将以一个空行结束

输出
输出将是每一个单独一行，每一个后面一个换行符

样例输入
six
negative seven hundred twenty nine
one million one hundred one
eight hundred fourteen thousand twenty two

样例输出
6
-729
1000101
814022
*/
#include <iostream>
#include <string>
using namespace std;
struct Voca {
  string vocabulary_;
  int num_;
  int times_;
  Voca(string voca, int num, int times)
      : vocabulary_(voca), num_(num), times_(times) {}
};
int main() {
  Voca vocas[32] = {{"negative", 0, -1},
                    {"zero", 0, 1},
                    {"one", 1, 1},
                    {"two", 2, 1},
                    {"three", 3, 1},
                    {"four", 4, 1},
                    {"five", 5, 1},
                    {"six", 6, 1},
                    {"seven", 7, 1},
                    {"eight", 8, 1},
                    {"nine", 9, 1},
                    {"ten", 10, 1},
                    {"eleven", 11, 1},
                    {"twelve", 12, 1},
                    {"thirteen", 13, 1},
                    {"fourteen", 14, 1},
                    {"fifteen", 15, 1},
                    {"sixteen", 16, 1},
                    {"seventeen", 17, 1},
                    {"eighteen", 18, 1},
                    {"nineteen", 19, 1},
                    {"twenty", 20, 1},
                    {"thirty", 30, 1},
                    {"forty", 40, 1},
                    {"fifty", 50, 1},
                    {"sixty", 60, 1},
                    {"seventy", 70, 1},
                    {"eighty", 80, 1},
                    {"ninety", 90, 1},
                    {"hundred", 100, 100},
                    {"thousand", 1000, 1000},
                    {"million", 1000000, 1000000}};
  string english;
  while (getline(cin, english)) {
    string word;
    int blank(0), start(0);
    do {
      int output(0), nega(0);
      blank = english.find(' ', start);
      if (blank != string ::npos) {
        word = english.substr(start, blank - start);
        start = blank + 1;
      } else {
        blank = english.size();
        word = english.substr(start, blank - start);
      }
      for (int i(0); i < 32; ++i) {
        if (word == vocas[i].vocabulary_) {
          output += vocas[i].num_ * vocas[i].times_;
          break;
        }
      }
      if (word == vocas[31].vocabulary_)
        nega = 1;
    } while (blank != string::npos);
  }

  return 0;
}