/*
编程题＃1：计算矩阵边缘元素之和
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
输入一个整数矩阵，计算位于矩阵边缘的元素之和。所谓矩阵边缘的元素，就是第一行和最后一行的元素以及第一列和最后一列的元素。

输入
第一行为整数k，表示有k组数据。

每组数据有多行组成，表示一个矩阵：

第一行分别为矩阵的行数m和列数n（m < 100，n < 100），两者之间以空格分隔。

接下来输入的m行数据中，每行包含n个整数，整数之间以空格作为间隔。

输出

输出对应矩阵的边缘元素和，一个一行。
*/
#include <iostream>
using namespace std;
int main() {
  int matrix[100][100] = {0};
  int k(0); // k组数据，m行n列
  cin >> k;
  cin.ignore();
  while (k-- > 0) {
    int sum_edge(0);
    int m(0), n(0);
    cin >> m >> n;
    for (int i(0); i < m; ++i) {
      for (int j(0); j < n; ++j) {
        cin >> matrix[i][j];
        if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
          sum_edge += matrix[i][j];
        }
      }
    }
    cout << sum_edge << endl;
  }

  return 0;
}