/*
1. 距离排序
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
给出三维空间中的n个点（不超过10个）,求出n个点两两之间的距离,并按距离由大到小依次输出两个点的坐标及它们之间的距离。

输入
输入包括两行，第一行包含一个整数n表示点的个数，第二行包含每个点的坐标(坐标都是整数)。点的坐标的范围是0到100，输入数据中不存在坐标相同的点。

输出
对于大小为n的输入数据，输出n*(n-1)/2行格式如下的距离信息：

(x1,y1,z1)-(x2,y2,z2)=距离

其中距离保留到数点后面2位。

(用cout输出时保留到小数点后2位的方法:cout<<fixed<<setprecision(2)<<x)

样例输入
4
0 0 0 1 0 0 1 1 0 1 1 1
样例输出
(0,0,0)-(1,1,1)=1.73
(0,0,0)-(1,1,0)=1.41
(1,0,0)-(1,1,1)=1.41
(0,0,0)-(1,0,0)=1.00
(1,0,0)-(1,1,0)=1.00
(1,1,0)-(1,1,1)=1.00

提示
用cout输出时保留到小数点后2位的方法:cout<<fixed<<setprecision(2)<<x

注意：
冒泡排序满足下面的性质,选择排序和快速排序(qsort或sort)需要对下面的情况进行额外处理

使用冒泡排序时要注意边界情况的处理,保证比较的两个数都在数组范围内

1.
对于一行输出中的两个点(x1,y1,z1)和(x2,y2,z2)，点(x1,y1,z1)在输入数据中应出现在点(x2,y2,z2)的前面。

比如输入：

2

0 0 0 1 1 1

输出是：

(0,0,0)-(1,1,1)=1.73

但是如果输入：

2

1 1 1 0 0 0

输出应该是：

(1,1,1)-(0,0,0)=1.73

2. 如果有两对点p1,p2和p3,p4的距离相同，则先输出在输入数据中靠前的点对。

比如输入：

3

0 0 0 0 0 1 0 0 2

输出是：

(0,0,0)-(0,0,2)=2.00

(0,0,0)-(0,0,1)=1.00

(0,0,1)-(0,0,2)=1.00

如果输入变成：

3

0 0 2 0 0 1 0 0 0

则输出应该是：

(0,0,2)-(0,0,0)=2.00

(0,0,2)-(0,0,1)=1.00

(0,0,1)-(0,0,0)=1.00
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

struct Coordinate {
  int x_, y_, z_;
  Coordinate(int x, int y, int z) : x_(x), y_(y), z_(z) {}
  friend ostream &operator<<(ostream &os, const Coordinate &c) {
    os << "(" << c.x_ << "," << c.y_ << "," << c.z_ << ")";
    return os;
  }
};

double Dis(Coordinate &a, Coordinate &b) {
  return sqrt(pow(a.x_ - b.x_, 2) + pow(a.y_ - b.y_, 2) + pow(a.z_ - b.z_, 2));
}
struct Ans {
  double dis_;
  Coordinate a_, b_;
  Ans(double dis, Coordinate &a, Coordinate &b) : dis_(dis), a_(a), b_(b) {}
  friend bool operator>(const Ans &a, const Ans &b) { return a.dis_ > b.dis_; }
};
int main() {
#ifdef LOCAL_DEBUG
  freopen("data_structure_2/.debug/w2_1.in", "r", stdin);
#endif

  int n;
  cin >> n;
  vector<Coordinate> points;
  int x, y, z;
  while (n--) {
    cin >> x >> y >> z;
    points.push_back(Coordinate(x, y, z));
  }
  vector<Ans> ans;
  for (int i = 0; i < points.size(); ++i)
    for (int j = i + 1; j < points.size(); ++j)
      ans.push_back(Ans(Dis(points[i], points[j]), points[i], points[j]));

  stable_sort(ans.begin(), ans.end(), greater<Ans>());

  for (int i(0); i < ans.size(); ++i) {
    cout << ans[i].a_ << "-" << ans[i].b_ << "=" << fixed << setprecision(2)
         << ans[i].dis_ << endl;
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
