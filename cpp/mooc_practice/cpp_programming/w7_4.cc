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
*/
#include <iostream>
#include <string>
using namespace std;
string Copy(string operand);
string Add(string operand);
string Find(string operand);
string Rfind(string operand);
string Insert(string operand);
string Reset(string operand);
string Print(string operand);
string Printall(string operand);
int *CutOperand(string operand);
bool AllIsNum(string str1);
int main() {
  int n(0);
  cin >> n;
  cin.ignore();
  string *str = new string[n];
  for (int i(1); i <= n; ++i)
    cin >> str[i];
  string command;
  while (true) {
    getline(cin, command);
    if (command == "over")
      break;
    int pos(0);
    command.find(" ");
    string operation, operand;          // 把命令分成操作和操作数
    operation = command.substr(0, pos); // 第一个空格前是操作 (copy等)
    operand = command.substr(pos + 1, command.length()); // 后面都算作操作数

    if (operation == "copy") {
      Copy(operand);
    } else if (operation == "add") {
      Add(operand);
    } else if (operation == "find") {
      Find(operand);
    } else if (operation == "rfind") {
      Rfind(operand);
    } else if (operation == "insert") {
      Insert(operand);
    } else if (operation == "reset") {
      Reset(operand);
    } else if (operation == "print") {
      Print(operand);
    } else if (operation == "printall") {
      Printall(operand);
    } else {
      cout << "command error!" << endl;
    }
  }

  return 0;
}
string Copy(string operand) {
  int *op_ = CutOperand(operand);
  int n, x, l;
  n = op_[0];
  x = op_[1];
  l = op_[2];
  return str[i].substr(x, l);
}

string Add(string operand) {
    string S1, S2;
    int b = operand.find(" ");
    S1 = operand.substr(0, b);
    S2 = operand.substr(b + 1, operand.length());
    if (AllisNum(S1) && AllisNum(S2)) {
        return stoi(S1) + stoi(S2);
    } else {
        return S1 + S2;
    }
}
string Find(string operand);
string Rfind(string operand);
string Insert(string operand);
string Reset(string operand);
string Print(string operand);
string Printall(string operand);
int *CutOperand(string operand) {
    // 把operand拆开成多个操作数字;
    string *op_str = new string[operand.length()];
    int *op = new int[operand.length()];
    for (int i(0), j(0); operand[i] != '\0'; ++i) {
      if (operand[i] != ' ')
        op_str[j] += operand[i]; // 如果不是就记录到第j个op_str中
      else {
        operand.erase(i, 1); // 如果是' '就删掉第i个起的1个字符，即删掉空格
        op[j] = stoi(op_str[j]);
        ++j;
      } 
    }
}
bool AllIsNum(string str1) {
    bool all = false;
    for (int i(0); i < str1.length(); ++i) {
        if (isdigit(str[i]) {
           all = true;
        }
        else {
           all = false;
           break;
        }
    }
    return all;
}