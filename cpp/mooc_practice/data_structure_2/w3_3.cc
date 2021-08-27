/*
3. DNA排序
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
现在有一些长度相等的DNA串（只由ACGT四个字母组成），请将它们按照逆序对的数量多少排序。

逆序对指的是字符串A中的两个字符A[i]、A[j]，具有i < j 且 A[i] > A[j]
的性质。如字符串”ATCG“中，T和C是一个逆序对，T和G是另一个逆序对，这个字符串的逆序对数为2。

输入
第1行：两个整数n和m，n(0<n<=50)表示字符串长度，m(0<m<=100)表示字符串数量

第2至m+1行：每行是一个长度为n的字符串

输出
按逆序对数从少到多输出字符串，逆序对数一样多的字符串按照输入的顺序输出。

样例输入
10 6
AACATGAAGG
TTTTGGCCAA
TTTGGCCAAA
GATCAGATTT
CCCGGGGGGA
ATCGATGCAT
样例输出
CCCGGGGGGA
AACATGAAGG
GATCAGATTT
ATCGATGCAT
TTTTGGCCAA
TTTGGCCAAA
*/
#define STL // STL库，不用时注释掉此行
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#ifdef STL
#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#endif

// #define LOCAL_DEBUG // 本地调试宏定义，提交代码时注释掉此行
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll INF_LL = 0x3f3f3f3f3f3f3f3f;
bool Cmp(const pair<string, int> d1, const pair<string, int> d2) {
  return d1.second < d2.second;
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("data_structure_2/.debug/w3_3.in", "r", stdin);
#endif

  int n, m;
  cin >> n >> m;
  cin.ignore();
  string str;
  int count;
  vector<pair<string, int> > dna;

  while (m--) {
    getline(cin, str);
    count = 0;
    for (int i = 0; i < str.size(); ++i)
      for (int j = i + 1; j < str.size(); ++j) {
        if (str[i] > str[j])
          ++count;
      }
    dna.push_back(make_pair(str, count));
  }
  sort(dna.begin(), dna.end(), Cmp);
  for (int i = 0; i < dna.size(); ++i)
    cout << dna[i].first << endl;

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
