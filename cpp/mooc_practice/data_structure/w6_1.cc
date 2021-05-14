/*
1. Huffman编码树
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 1000ms 内存限制: 65536kB

描述
构造一个具有n个外部节点的扩充二叉树，每个外部节点Ki有一个Wi对应，作为该外部节点的权。使得这个扩充二叉树的叶节点带权外部路径长度总和最小：

                          Min( W1 * L1 + W2 * L2 + W3 * L3 + … + Wn * Ln)

Wi:每个节点的权值。

Li:根节点到第i个外部叶子节点的距离。

编程计算最小外部路径长度总和。

输入
第一行输入一个整数n，外部节点的个数。第二行输入n个整数，代表各个外部节点的权值。

2<=N<=100

输出
输出最小外部路径长度总和。

样例输入
4
1 1 3 5

样例输出
17
*/
#include <algorithm>
#include <iostream>
using namespace std;
int WeightSum(int *w, int n) {
  if (n == 1)
    return 0;
  else {
    sort(w, w + n, greater<int>());
    w[n - 2] +=  w[n - 1];
    return w[n - 2] + WeightSum(w, n - 1);
  }
}
int main() {
  int n;
  cin >> n;
  cin.ignore();
  int *weight = new int[n];
  for (int i(0); i < n; ++i)
    cin >> weight[i];
  cout << WeightSum(weight, n) << endl;

  return 0;
}