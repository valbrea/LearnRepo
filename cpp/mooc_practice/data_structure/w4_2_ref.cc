// 自己写的wrong answer，也不知道哪里错了，有毒
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
  vector<string> dict;
  string str;
  cin >> str;
  while (str != "#") {
    dict.push_back(str);
    cin >> str;
  }
  string str1;
  cin >> str1;
  while (str1 != "#") {
    bool find = false;
    for (int i = 0; i < dict.size(); i++) {
      if (dict[i] == str1) {
        find = true;
        cout << str1 << " is correct" << endl;
      }
    }
    if (!find) {
      cout << str1 << ":";
      for (int i = 0; i < dict.size(); i++) {
        if (str1.size() + 1 == dict[i].size()) {
          int j, k;
          for (j = 0, k = 0;
               dict[i][j] == str1[k] && j < dict[i].size() && k < str1.size();
               j++, k++)
            ;
          for (j = j + 1;
               dict[i][j] == str1[k] && j < dict[i].size() && k < str1.size();
               j++, k++)
            ;
          if (j == dict[i].size() && k == str1.size())
            cout << " " << dict[i];
        }
        if (str1.size() - 1 == dict[i].size()) {
          int j, k;
          for (j = 0, k = 0;
               dict[i][j] == str1[k] && j < dict[i].size() && k < str1.size();
               j++, k++)
            ;
          for (k = k + 1;
               dict[i][j] == str1[k] && j < dict[i].size() && k < str1.size();
               j++, k++)
            ;
          if (j == dict[i].size() && k == str1.size())
            cout << " " << dict[i];
        }
        if (str1.size() == dict[i].size()) {
          int j, k;
          for (j = 0, k = 0;
               dict[i][j] == str1[k] && j < dict[i].size() && k < str1.size();
               j++, k++)
            ;
          for (j = j + 1, k = k + 1;
               dict[i][j] == str1[k] && j < dict[i].size() && k < str1.size();
               j++, k++)
            ;
          if (j == dict[i].size() && k == str1.size())
            cout << " " << dict[i];
        }
      }
      cout << endl;
    }
    cin >> str1;
  }
  return 0;
}