/****************************************************************
 * ＃3：最长单词2
 *
 * 方法二
 *****************************************************************/
#include <iostream>
using namespace std;

int main() {
  char sentence[500] = {0};
  int length(0), begin(0), end(0), max(0);

  cin.getline(sentence, 500);
  for (int i(0); sentence[i] != '\0'; i++) {
    if (sentence[i] != ' ' && sentence[i] != '.') // 如果不是空格和句尾
    {
      length++;
    } else if (length >= max) // 如果长度比max长，更新max
    {
      end = i;
      begin = i - length;
      max = length;
      length = 0;
    } else if (sentence[i] == '.') // 遇到句尾就结束
    {
      break;
    }
  }

//   cout << "最长单词为";
  for (int i(begin); i < end; i++) {
    cout << sentence[i];
  }
  cout << endl;

  return 0;
}