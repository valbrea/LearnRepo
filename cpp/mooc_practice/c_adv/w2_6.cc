/* 编程题＃6：流感传染
注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
有一批易感人群住在网格状的宿舍区内，宿舍区为n*n的矩阵，每个格点为一个房间，房间里可能住人，也可能空着。
在第一天，有些房间里的人得了流感，以后每天，得流感的人会使其邻居传染上流感，
（已经得病的不变），空房间不会传染。请输出第m天得流感的人数。

输入
第一行一个数字n，n不超过100，表示有n*n的宿舍房间。

接下来的n行，每行n个字符，’.’表示第一天该房间住着健康的人，’#’表示该房间空着，’@’表示第一天该房间住着得流感的人。

接下来的一行是一个整数m，m不超过100.

输出
输出第m天，得流感的人数 */
/*******************
 * 要注意实际上是并行处理每天的病例，但模拟时只能顺序处理，所以一定要用某些标记加以区分。
 * ****************/
#include <iostream>
using namespace std;

int main() {
  int number(0), day(1), end(0);
  const char health('.'), empty('#'), inffected('@'), susceptible('!');
  cin >> number;
  char room[100][100] = {0};
  for (int i(0); i < number; ++i)
    for (int j(0); j < number; ++j)
      cin >> room[i][j];
  cin >> end;
  for (day; day < end; ++day) {
    for (int i(0); i < number; ++i) {
      for (int j(0); j < number; ++j) {
        if (room[i][j] == inffected) {
          if (room[i + 1][j] == health)
            room[i + 1][j] = susceptible;
          if (room[i - 1][j] == health)
            room[i - 1][j] = susceptible;
          if (room[i][j + 1] == health)
            room[i][j + 1] = susceptible;
          if (room[i][j - 1] == health)
            room[i][j - 1] = susceptible;
        }
      }
    }

    for (int i(0); i < number; ++i) {
      for (int j(0); j < number; ++j) {
        // cout << room[i][j];
        if (room[i][j] == susceptible)
          room[i][j] = inffected;
      }
      // cout << endl;
    }
    // cout << "过程中" << endl;
    // for (int i(0); i < number; ++i)
    // {
    //     for (int j(0); j < number; ++j)
    //     {
    //         cout << room[i][j];
    //     }
    //     cout << endl;
    // }
  }
  int count(0);
//   cout << "结果" << endl;
  for (int i(0); i < number; ++i) {
    for (int j(0); j < number; ++j) {
      if (room[i][j] == inffected)
        count++;
    //   cout << room[i][j];
    }
    // cout << endl;
  }
  cout << count << endl;
  return 0;
}