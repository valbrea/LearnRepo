/*
2. 拼写检查
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 2000ms 内存限制: 65536kB

描述
现在有一些英语单词需要做拼写检查，你的工具是一本词典。需要检查的单词，有的是词典中的单词，有的与词典中的单词相似，你的任务是发现这两种情况。单词A与单词B相似的情况有三种：

1、删除单词A的一个字母后得到单词B；

2、用任意一个字母替换单词A的一个字母后得到单词B；

3、在单词A的任意位置增加一个字母后得到单词B。

你的任务是发现词典中与给定单词相同或相似的单词。

输入
第一部分是词典中的单词，从第一行开始每行一个单词，以"#"结束。词典中的单词保证不重复，最多有10000个。

第二部分是需要查询的单词，每行一个，以"#"结束。最多有50个需要查询的单词。

词典中的单词和需要查询的单词均由小写字母组成，最多包含15个字符。

输出
按照输入的顺序，为每个需要检查的单词输出一行。如果需要检查的单词出现在词典中，输出“?x
is
correct"，?x代表需要检查的单词。如果需要检查的单词没有出现在词典中，则输出"?x:
?x1 ?x2
...?xn"，其中?x代表需要检查的单词，?x1...?xn代表词典中与需要检查的单词相似的单词，这些单词中间以空格隔开。如果没有相似的单词，输出"?x:"即可。

样例输入
i
is
has
have
be
my
more
contest
me
too
if
award
#
me
aware
m
contest
hav
oo
or
i
fi
mre
#

样例输出
me is correct
aware: award
m: i my me
contest is correct
hav: has have
oo: too
or:
i is correct
fi: i
mre: more me
*/

#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int Similar(string &a, string &b) {
  if (a.size() > b.size() && a.size() - b.size() <= 1)
    return 1; // check比词典长1
  else if (a.size() < b.size() && b.size() - a.size() <= 1)
    return 2; // check比词典短1
  else if (a.size() == b.size())
    return 3; // 如果长短相同
  else
    return 0; // 不相似
}

int main() {
  string words;
  vector<string> dictionary;
  queue<string> tocheck;
  while (words != "#") {
    // 这样会录入"#"，因为是先录入再判断
    getline(cin, words);
    dictionary.push_back(words);
  }
  // 由于word="#"，需要修改，否则无法进下一个循环
  words = "";
  while (words != "#") {
    getline(cin, words);
    tocheck.push(words);
  }
  while (tocheck.front() != "#") {
    string check = tocheck.front();
    tocheck.pop();
    vector<string>::iterator ii = dictionary.begin();
    string out = check + ":";
    for (; ii != dictionary.end() - 1; ++ii) { // 因为录入了"#"，所以是end()-1
      if (Similar(check, *ii) == 0) // 如果不相似，直接下一个;
        continue;
      string temp;
      int i(0);
      switch (Similar(check, *ii)) {
      case 1: // 输入比词典长1
        while (check[i] == ii->at(i))
          ++i;
        // 删除输入的第i个位置，再和字典比较是否相等，如果相等就输出
        temp += check.substr(0, i);
        temp += check.substr(i + 1, check.size() - i - 1);
        if (temp == *ii)
          out += " " + *ii;
        break;
      case 2: // 输入比词典短1
        while (check[i] == ii->at(i))
          ++i;
        // 删除字典的第i个位置，再和输入比较是否相等，如果相等就输出
        temp += ii->substr(0, i);
        temp += ii->substr(i + 1, ii->size() - i - 1);
        if (temp == check)
          out += " " + *ii;
        break;
      case 3:                          // 一样长
        if (check == *ii) {            // 如果直接相同
          out = check + " is correct"; // 先修改out，然后跳出循环
          break;
        }
        while (check[i] == ii->at(i))
          ++i;
        // 替换输入的第i个位置与字典相同，如果和字典相等就输出
        temp += check.substr(0, i);
        temp += ii->at(i);
        temp += check.substr(i + 1, check.size() - i - 1);
        if (temp == *ii)
          out += " " + *ii;
        break;
      default:
        break;
      }
      if (check == *ii)
        // 修改out以后，直接跳出循环
        break;
    }
    cout << out << endl;
  }

  return 0;
}