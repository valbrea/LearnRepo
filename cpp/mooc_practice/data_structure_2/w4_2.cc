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
/*
 * n名选手player[1:n]，n-1个内部节点tree[0:n-1]
 * 最底层最左端的内部节点其编号为s，且s = 2^⌊ log2( n − 1 ) ⌋
 * 因为对于有n-1个元素(内部节点)的完全二叉树，
 * 最底层内部节点个数是n − s，最低层外部节点的个数lowExt = 2 * ( n − s )
 * 令offset = 2 * s - 1即内部节点最底层最右端的节点编号。
 */
const int MAX = 65535;
template <class T> class LoserTree {
private:
  int max_size_; // 最大选手数
  int n_;        // 当前选手数
  int low_ext_;  // 最底层外部节点数
  int offset_;   // 其余节点总数
  int *arena_; // 败方树内部节点数组（存放的下标），从0开始，0是冠军
  T *player_; // 选手元素数组，从1开始！
  void Play(int p, int lc, int rc);

public:
  LoserTree(int max_size = MAX) : max_size_(max_size) {}
  ~LoserTree() { delete[] arena_; }
  // 初始化败方树
  void Initialize(T a[], int size);
  // 返回最终胜利者arena_[0]的索引
  int Champion() { return (n_) ? arena_[0] : 0; }
  int Winner(int x, int y) { return player_[x] <= player_[y] ? x : y; }
  int Loser(int x, int y) { return player_[x] > player_[y] ? x : y; }
  // 位置i的选手改变后重构败方树
  void RePlay(int i, int new_value);
  void Show() const;
};
template <class T> void LoserTree<T>::Initialize(T a[], int size) {
  if (size > max_size_ || size < 2) { // 边界判断
    cout << "Bad Input!" << endl << endl;
    return;
  }
  // 成员变量初始化
  n_ = size;
  player_ = a;
  arena_ = new int[n_];

  // 最底层最左端的内部节点其编号为s，且s = 2^⌊ log2( n − 1 ) ⌋
  int i, s; // s = 2^log(n - 1)
  for (s = 1; 2 * s <= n_ - 1; s += s)
    ; // 若有h层满二叉树的败者树，则一共有s = 2 ^ h = 1 + 1 + 2 + ... + h
      // 个节点（包括冠军节点） 这里数到了倒数第二层（low_ext_上一层）
  low_ext_ = 2 * (n_ - s);
  offset_ = 2 * s - 1;
  
  for (i = 2; i <= low_ext_; i += 2) // 底层外部相互比赛
    Play((offset_ + i) / 2, i - 1, i);
  if (n_ % 2) { // n是奇数，内部和外部比赛
    Play(n_ / 2, arena_[(n_ - 1) / 2], low_ext_ + 1);
    i = low_ext_ + 3;
  } else {
    i = low_ext_ + 2;
  }
  for (; i <= n_; i += 2) // 剩余外部节点的比赛
    Play((i - low_ext_ + n_ - 1) / 2, i - 1, i);
}
template <class T> void LoserTree<T>::Play(int p, int lc, int rc) {
  arena_[p] = Loser(lc, rc); // 败者索引放在arena[p]
  int temp1, temp2;
  temp1 = Winner(lc, rc);  // p处的胜者索引
  while (p > 1 && p % 2) { // 内部右侧，要沿路向上比赛
    temp2 = Winner(temp1, arena_[p / 2]);
    arena_[p / 2] = Loser(temp1, arena_[p / 2]);
    temp1 = temp2;
    p /= 2;
  }
  // arena_[p] 是左孩子或者arena_[1]
  arena_[p / 2] = temp1;
}
template <class T> void LoserTree<T>::RePlay(int i, int new_value) {
  if (i <= 0 || i > n_) {
    cout << "Out of Bounds!" << endl << endl;
    return;
  }
  int p;
  if (i <= low_ext_) // 确定父节点位置
    p = (i + offset_) / 2;
  else
    p = (i - low_ext_ + n_ - 1) / 2;
  player_[i] = new_value;           // 改变i处元素的值
  arena_[0] = Winner(i, arena_[p]); // 利用这两个空间
  arena_[p] = Loser(i, arena_[p]);
  int temp;
  for (; (p / 2) >= 1; p /= 2) {
    // 沿路向上比赛
    temp = Winner(arena_[p / 2], arena_[0]);
    arena_[p / 2] = Loser(arena_[p / 2], arena_[0]);
    arena_[0] = temp;
  }
}
template <class T> void LoserTree<T>::Show() const {
  for (int i(0); i < n_; ++i)
    cout << player_[arena_[i]] << " ";
  cout << endl;
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("data_structure_2/.debug/w4_2.in", "r", stdin);
#endif

  int m, n;
  cin >> n >> m;
  int *players = new int[n + 1];
  for (int i(1); i <= n; ++i)
    cin >> players[i]; //! player要从1开始！
  LoserTree<int> lt;
  lt.Initialize(players, n);
  lt.Show();
  int index, key;
  while (m--) {
    cin >> index >> key;
    lt.RePlay(index + 1, key); //! 因为输入的index是从0开始，player要从1开始
    lt.Show();
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
