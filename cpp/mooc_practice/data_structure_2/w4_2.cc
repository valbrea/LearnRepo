/*
2. 败方树
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
给定一个整数数组，要求对数组中的元素构建败方树（数组相邻元素两两比较，从第一个元素开始）。之后修改数组中的元素，要求输出初始构建以及修改后得到的败方树的所有内部结点代表的整数(从左到右从上到下输出）

输入
第一行为数组的元素个数n和修改的次数m。

第二行为n个整数，即数组的元素。

接下来m行代表m次修改操作，每次操作修改数组中的一个元素，每一行包括两个整数，第一个为被修改元素在数组中的标号，第二个为修改之后的元素值。

输出
输出m+1行。

第一行为初始构建的败方树的所有内部结点代表的整数(按照树的结点从左到右从上到下的顺序输出）

接下来m行为接下来m次修改后得到的败方树的所有内部结点代表的整数(按照树的结点从左到右从上到下的顺序输出）

样例输入
8 1
10 9 20 6 16 12 90 17
3 15
样例输出
6 12 9 17 10 20 16 90
9 12 15 17 10 20 16 90
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

#define LOCAL_DEBUG // 本地调试宏定义，提交代码时注释掉此行
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll INF_LL = 0x3f3f3f3f3f3f3f3f;
const int MAX = 65535;
template <class T> class LoserTree {
private:
  int max_size_; // 最大选手数
  int n_;        // 当前选手数，
  int low_ext_;  // 最底层外部节点数
  int offset_;   // 其余节点总数
  int *b_;       // 败方树内部节点数组（存放的下标）
  T *l_;         // 元素数组
  void Play(int p, int lc, int rc, int (*winner)(T a[], int b, int c));

public:
  LoserTree(int tree_size = MAX) {}
  ~LoserTree() { delete[] b_; }
  // 初始化败方树
  void Initialize(T a[], int size, int (*winner)(T a[], int b, int c),
                  int (*loser)(T a[], int b, int c));
  // 返回最终胜利者b_[0]的索引
  int Winner() { return (n_) ? b_[0] : 0; }
  // 位置i的选手改变后重构败方树
  void RePlay(int i, int (*winner)(T a[], int b, int c),
              int (*loser)(T a[], int b, int c));
};
template <class T>
void LoserTree<T>::Initialize(T a[], int size,
                              int (*winner)(T a[], int b, int c),
                              int (*loser)(T a[], int b, int c)) {
  if (size > max_size_ || size < 2) { // 边界判断
    cout << "Bad Input!" << endl << endl;
    return;
  }
  int i, s; // s = 2^log(n - 1)
  for (s = 1; 2 * s <= n_ - 1; s += s)
    ; // 若有h层满二叉树的败者树，则一共有s = 2 ^ h = 1 + 1 + 2 + ... + h 个节点（包括冠军节点）
     // 这里数到了倒数第二层（low_ext_上一层）
  low_ext_ = 2 * (n_ - s);
  offset_ = 2 * s - 1;
  for (i = 2; i < low_ext_; i += 2) // 底层外部相互比赛
    Play((offset_ + i) / 2, i - 1, i, winner, loser);
  if (n % 2) {                      // n是奇数，内部和外部比赛
    Play(n / 2, b_[(n - 1) / 2], low_ext_ + 1, winner, loser);
    i = low_ext_ + 3;
  } else {
    i = low_ext_ + 2;
  }
  for (; i <= n; i += 2)            // 剩余外部节点的比赛
    Play((i - low_ext_ + n - 1) / 2, i - 1, i, winner, loser);
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("data_structure_2/.debug/w4_2.in", "r", stdin);
#endif

  int m, n;
  cin >> n >> m;
  vector<int> elems;
  int key;
  for (int i(0); i < n; ++i) {
    cin >> key;
    elems.push_back(key);
  }
  int index;
  for (int i(0); i < m; ++i) {
    cin >> index >> key;
    Change(index, key, elems);
    Show();
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
