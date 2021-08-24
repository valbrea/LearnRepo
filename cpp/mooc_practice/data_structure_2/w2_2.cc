/*
2. 数据筛选
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 10000ms 内存限制: 3000kB

描述
小张需要从一批数量庞大的正整数中挑选出第k小的数，因为数据量太庞大，挑选起来很费劲，希望你能编程帮他进行挑选。

输入
第一行第一个是数据的个数n(10<=n<=106)，第二个是需要挑选出的数据的序号k(1<=k<=105)，n和k以空格分隔；

第二行以后是n个数据T(1<=T<=109)，数据之间以空格或者换行符分隔。

输出
第k小数（如果有相同大小的也进行排序，例如对1,2,3,8,8，第4小的为8，第5小的也为8）。

样例输入
10 5
1 3 8 20 2
9 10 12 8 9
样例输出
8
*/
#define STL   // STL库，不用时注释掉此行
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

int main() {
#ifdef LOCAL_DEBUG
  freopen("data_structure_2/.debug/w2_2.in", "r", stdin);
#endif

  int n, k;
  cin >> n >> k;
  vector<int> data(n);
  int d;
  for (int i = 0; i < n; ++i) {
    cin >> d;
    data[i] = d;
  }
  make_heap(data.begin(), data.end(), greater<int>());
  while (--k) {
    pop_heap(data.begin(), data.end(), greater<int>());
    data.pop_back();
  }
  cout << data[0] << endl;
  

#ifdef LOCAL_DEBUG
  cout << endl << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
