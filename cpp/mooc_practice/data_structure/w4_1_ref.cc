// 自己写的wrong answer，也不知道哪里错了，有毒
#include <iostream>
#include <string>
using namespace std;
struct strCha {
  string s;
  int t;
  int i;
  strCha(string s1, int t1, int i1) : s(s1), t(t1), i(i1) {}
};
strCha stand[32] = {
    {"negative", -1, 1},   {"zero", 0, 0},          {"one", 1, 0},
    {"two", 2, 0},         {"three", 3, 0},         {"four", 4, 0},
    {"five", 5, 0},        {"six", 6, 0},           {"seven", 7, 0},
    {"eight", 8, 0},       {"nine", 9, 0},          {"ten", 10, 0},
    {"eleven", 11, 0},     {"twelve", 12, 0},       {"thirteen", 13, 0},
    {"fourteen", 14, 0},   {"fifteen", 15, 0},      {"sixteen", 16, 0},
    {"seventeen", 17, 0},  {"eighteen", 18, 0},     {"nineteen", 19, 0},
    {"twenty", 20, 0},     {"thirty", 30, 0},       {"forty", 40, 0},
    {"fifty", 50, 0},      {"sixty", 60, 0},        {"seventy", 70, 0},
    {"eighty", 80, 0},     {"ninety", 90, 0},       {"hundred", 100, 2},
    {"thousand", 1000, 3}, {"million", 1000000, 4},
};

long ExchangeS(string &InputS) {
  long resul = 0;
  string valueS;
  int pos = 0, next = -1;
  int j = 0;
  int flag = 1;
  int num = InputS.size();
  int Shu[32];
  int np[32];
  while (pos != string::npos) {
    pos = InputS.find(" ", pos + 1);
    if (pos != string::npos) {
      valueS = InputS.substr(next + 1, pos - next - 1);
    } else {
      valueS = InputS.substr(next + 1);
    }
    //在stand中寻找相匹配的字符串
    for (int i = 0; i < 32; i++) {
      if (valueS == stand[i].s) {
        Shu[j] = stand[i].t;
        np[j] = stand[i].i;
        j++;
        break;
      }
    }
    next = pos;
  }
  //转换成数字
  int i = 0;
  long nu = 0;
  long res = 0;
  while (i < j) {
    switch (np[i]) {
    case 1:
      flag = -1;
      i++;
    case 0:
      resul += Shu[i];
      i++;
      if (i >= j) {
        nu = nu + resul;
        resul = 0;
        break;
      } else
        continue; // nu = nu + resul; resul = 0;
    case 2:
      if (nu < 100) {
        nu += resul;
        nu *= Shu[i];
        resul = 0;
        i++;
        break;
      } else {
        resul *= Shu[i];
        i++;
        nu = nu + resul;
        resul = 0;
        break;
      }
    case 3:
      if (nu < 1000) {
        nu += resul;
        nu *= Shu[i];
        resul = 0;
        i++;
        break;
      } else {
        resul *= Shu[i];
        i++;
        nu = nu + resul;
        resul = 0;
        i++;
        break;
      }
    case 4:
      if (resul != 0)
        nu = resul + nu;
      nu *= Shu[i];
      i++;
      resul = 0;
      res = nu;
      nu = 0;
      break;
    default:
      nu = nu + Shu[i];
      resul = 0;
      break;
    }
  }
  if (res == 0)
    return nu * flag;
  else
    return (nu + res) * flag;
}
int main() {
  char s[512];
  cin.getline(s, 512);
  string InputS(s);
  while (!InputS.empty()) {
    cout << ExchangeS(InputS) << endl;
    cin.getline(s, 512);
    InputS = s;
  }
  return 0;
}