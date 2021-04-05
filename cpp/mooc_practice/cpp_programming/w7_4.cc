/*
编程题＃4： 字符串操作
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)
注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
给定n个字符串（从1开始编号），每个字符串中的字符位置从0开始编号，长度为1-500，现有如下若干操作：
copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
add S1
S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。
find S
N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
rfind S
N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
reset S N：将第N个字符串变为S。
print N：打印输出第N个字符串。
printall：打印输出所有字符串。
over：结束操作。
其中N，X，L可由find与rfind操作表达式构成，S，S1，S2可由copy与add操作表达式构成。

输入
第一行为一个整数n（n在1-20之间）
接下来n行为n个字符串，字符串不包含空格及操作命令等。
接下来若干行为一系列操作，直到over结束。

输出
根据操作提示输出对应字符串。

样例输入
3
329strjvc
Opadfk48
Ifjoqwoqejr
insert copy 1 find 2 1 2 2 2
print 2
reset add copy 1 find 3 1 3 copy 2 find 2 2 2 3
print 3
insert a 3 2
printall
over

样例输出
Op29adfk48
358
329strjvc
Op29adfk48
35a8

输入分析
3
329strjvc
Opadfk48
Ifjoqwoqejr
insert (copy (1, find(2, 1), 2), 2, 2)
print 2
reset(add(copy(1, find(3, 1), 3), copy(2, find(2, 2), 2)), 3)
print 3
insert a 3 2
printall
over

样例输出
Op29adfk48
358
329strjvc
Op29adfk48
35a8
*/
#include <deque>
#include <iostream>
#include <string>
using namespace std;

bool AllIsNum(string &str1);
string CheckOperator(deque<string> &argv);
string *str;
int main() {
  int n(0);
  cin >> n;
  cin.ignore();
  str = new string[n];
  for (int i(0); i < n; ++i) {
    getline(cin, str[i]);
  }
  string command;
  while (command.find("over") == command.npos) {
    getline(cin, command);
    string temp_op;
    int argc(0);
    deque<string> argv;
    for (int begin(0), blank(0); blank != command.npos; begin = blank + 1) {
      blank = command.find(' ', begin);
      if (blank != command.npos) { // 如果没到末尾位置
        argv.push_back(command.substr(begin, blank - begin));
        begin = blank + 1; // 记录下一个命令的开始位置
      } else               // 如果是末尾位置
        argv.push_back(command.substr(begin, command.size() - begin));
    }
    CheckOperator(argv);
  }

  return 0;
}
string Copy(deque<string> &argv) {
  int n = atoi(CheckOperator(argv).c_str());
  int x = atoi(CheckOperator(argv).c_str());
  int l = atoi(CheckOperator(argv).c_str());

  return str[n].substr(x, l);
}
string Add(deque<string> &argv) {
  string s1 = CheckOperator(argv);
  string s2 = CheckOperator(argv);
  if (AllIsNum(s1) && AllIsNum(s2)) {
    int n1 = atoi(s1.c_str());
    int n2 = atoi(s2.c_str());
    if (0 <= n1 && n1 <= 99999 && 0 <= n2 && n2 <= 99999)
      return to_string(n1 + n2);
  } 
    return (s1 + s2);
}
int Find(deque<string> &argv) {
  string s = CheckOperator(argv);
  int n = atoi(CheckOperator(argv).c_str());
  if (str[n].find(s) != str[n].npos)
    return str[n].find(s);
  else
    return str[n].size();
}
int Rfind(deque<string> &argv) {
   string s = CheckOperator(argv);
  int n = atoi(CheckOperator(argv).c_str());
  if (str[n].rfind(s) != str[n].npos)
    return str[n].rfind(s);
  else
    return str[n].size();
}
string Insert(deque<string> &argv) {
  string s = CheckOperator(argv);
  int n = atoi(CheckOperator(argv).c_str());
  int x = atoi(CheckOperator(argv).c_str());
  return str[n].insert(x, s);
}
string Reset(deque<string> &argv) {
  
}
string Print(deque<string> &argv);
string Printall(deque<string> &argv);
bool AllIsNum(string &str1) {
  for (int i(0); i < str1.size(); ++i) {
    if (!isdigit(str1[i]))
      return false;
  }
  return true;
}

string CheckOperator(deque<string> &argv) {
  string op;
  op = argv.front();
  argv.pop_front();

  if (op == "copy")
    Copy(argv);
  else if (op == "add")
    Add(argv);
  else if (op == "find")
    Find(argv);
  else if (op == "rfind")
    Rfind(argv);
  else if (op == "insert")
    Insert(argv);
  else if (op == "reset")
    Reset(argv);
  else if (op == "print")
    Print(argv);
  else if (op == "printall")
    Printall(argv);
 
    return op;
}