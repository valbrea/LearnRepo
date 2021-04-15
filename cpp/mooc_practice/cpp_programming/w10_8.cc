/*
编程题＃8：计算整数k
来源: 北京大学在线程序评测系统POJ
(Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

总时间限制: 1000ms 内存限制: 1024kB

描述
输入整数 n ( 0 <=n<= 2^30) , 以及整数i,j(0 <= i,j <31,i < j-1),
输出整数k(按十六进制输出结果 )，k的第i位和n相同，第j位和n不同，i,j之间的位是1,
其他位都是0。这里提到的所有的位，指的都是二进制位，最右边算第0位。

输入
第一行是整数 t，表示数据组数。

每组输入数据是一行，三个整数 n,i和j。

输出
对每组输入数据，按十六进制输出结果。

样例输入
2
23 3 5
7 0 2

样例输出
30
3
*/
#include <cmath>
#include <iostream>
using namespace std;
int main() {
  int t, n, i, j;
  cin >> t;
  while (t--) {
    cin >> n >> i >> j;
    // 最右边算第0位！！！！！
    // k_i = n & (第i位是1，其余是0) = n & (2powi)
    // k_j = n & (2powj) ^ (2powj)
    // 中间的位有 (j-1)-(i+1)+1 = (j-i-1)位
    // k_mid = 2pow(i+1) + 2pow(i+2) + ... + 2pow(j-1) = 2powj - 2pow(i+1)
    // k = k_i | k_j | k_mid

    int k, k_j, k_i, k_mid(0); // k的第i，j位和中间的位
    k_i = n & (int)pow(2, i);
    k_j = n & (int)pow(2, j) ^ (int)pow(2, j);
    k_mid = (int)pow(2, j) - (int)pow(2, i + 1);
    k = k_i | k_j | k_mid;
    cout << hex << k << endl; // 输出要16进制!!!我说怎么一直不对!!!
  }
  return 0;
}