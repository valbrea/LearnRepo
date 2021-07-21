/*
1. 我爱北大
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 1000ms 内存限制: 65536kB

描述
“红楼飞雪，一时英杰……”耳边传来了那熟悉的歌声。而这，只怕是我最后一次听到这个声音了。

想当年，我们曾经怀着豪情壮志，许下心愿，走过静园，走过一体，走过未名湖畔的每个角落。

想当年，我们也曾慷慨高歌，瞻仰民主与科学，瞻仰博雅塔顶，那百年之前的遗韵。

没错，我爱北大，我爱这个校园。

然而，从当我们穿上学位服的那一刻起，这个校园，就再也不属于我。它只属于往事，属于我的回忆。

没错，这，是我在北大的最后一日。此时，此景，此生，此世，将刻骨难忘。

再也没有了图书馆自习的各种纷纭，再也没有了运动场上的挥汗如雨，有的，只是心中永远的不舍，与牵挂。

夜，已深。人，却不愿离去。天边有一颗流星划过，是那般静，宁谧。

忍不住不回头，我的眼边，有泪光，划过。

这时候，突然有一位路人甲从你身旁出现，问你：从XX到XX怎么走？

索性，就让我再爱你一次。因为，北大永远在你心中。北大的地图，永远在你的心中。

轻手挥扬，不带走一分云彩。

输入
输入分为三个部分。

第一个部分有P+1行，第一行为一个整数P，之后的P行表示北大的地点。地点长度不超过20个字符。

第二个部分有Q+1行，第一行为一个整数Q，之后的Q行每行分别为两个字符串与一个整数，表示这两点有直线的道路，并显示二者之间的矩离（单位为米）。

第三个部分有R+1行，第一行为一个整数R，之后的R行每行为两个字符串，表示需要求的路线。

p<=30,Q<=50,R<=20

输出
输出有R行，分别表示每个路线最短的走法。其中两个点之间，用->(矩离)->相隔。

样例输入
6
XueYiShiTang
CanYinZhongXin
XueWuShiTang
XueYiXiaoBaiFang
BaiNianJiangTang
GongHangQuKuanJi
6
XueYiShiTang CanYinZhongXin 80
XueWuShiTang CanYinZhongXin 40
XueYiShiTang XueYiXiaoBaiFang 35
XueYiXiaoBaiFang XueWuShiTang 85
CanYinZhongXin GongHangQuKuanJi 60
GongHangQuKuanJi BaiNianJiangTang 35
2
XueYiXiaoBaiFang BaiNianJiangTang
GongHangQuKuanJi GongHangQuKuanJi
样例输出
XueYiXiaoBaiFang->(35)->XueYiShiTang->(80)->CanYinZhongXin->(60)->GongHangQuKuanJi->(35)->BaiNianJiangTangGongHangQuKuanJi
*/
// #define LOCAL // 本地调试宏定义，提交代码时注释掉此行
#define STL   // STL库，不用时注释掉此行
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
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

using namespace std;
typedef long long ll;

enum { kUnvisited, kVisited };
map<string, int> name_index;
map<int, string> index_name;

struct Dist {  // 最短路信息
  int index_;  // 顶点索引
  int length_; // 最短路长度
  int pre_;    // 最后经过的顶点
  Dist() : index_(-1), length_(0), pre_(-1) {}
  Dist(int l) : index_(-1), length_(l), pre_(-1) {}
  friend bool operator<(const Dist d1, const Dist &d2) {
    return d1.length_ < d2.length_;
  }
  // 要用到堆排序所以需要重载<
};
void Dijkstra(vector<vector<int> > &weight, int start, Dist *&min) {
  int n = weight.size();
  min = new Dist[n]; // 记录当前最短路径长度, 长度为n的对象数组
  int *mark = new int[n]; // 标记顶点是否被访问
  for (int i = 0; i < n; ++i) {
    // 初始化
    mark[i] = kUnvisited;
    min[i].index_ = i;
    min[i].length_ = INF;
    min[i].pre_ = start;
  }
  min[start].length_ = 0;
  priority_queue<Dist> minheap;
  minheap.push(min[start]);
  for (int i(0); i < n; ++i) {
    bool found = false;
    Dist d;
    while (!minheap.empty()) { // 如果非空就取出最小的路径长度信息
      d = minheap.top();
      minheap.pop();
      if (mark[d.index_] == kUnvisited) {
        // 找到路径长度最小的节点，没访问过就跳出循环
        found = true;
        break;
      }
    }
    // 如果没有符合条件的最短路径信息，就跳出本次循环
    if (!found) // 或者到了终点也要跳出循环
      break;
    int v = d.index_;
    mark[v] = kVisited;
    // 把这个节点v加入到第一组
    // 对于v的所有相邻点j
    for (int j = 0; j < n; ++j) {
      if ((min[v].length_ + weight[v][j]) < min[j].length_) {
        // 更新所有v到j的路径长度
        min[j].length_ = min[v].length_ + weight[v][j];
        min[j].pre_ = v;
        minheap.push(min[j]);
      }
    }
  }
  // 处理完以后，min里面就保存好了所有数据
}
void ShowPath(vector<vector<int> > &weight, Dist *&ans, int end) {
  // if (end == ans[end].pre_) {
  //   cout << index_name[end] << "->(0)->" << index_name[end] << endl;
  //   return;
  // }
  stack<int> path;
  while (end != ans[end].pre_) {
    path.push(ans[end].index_);
    end = ans[end].pre_;
  }
  int i = end;
  
  cout << index_name[i];
  while (!path.empty()) {
    int j = path.top();
    path.pop();
    cout << "->(" << weight[i][j] << ")->" << index_name[j];
    i = j;
  }
  cout << endl;
}
int main() {
#ifdef LOCAL
  freopen(".debug/w8_1.in", "r", stdin);
#endif

  int p, q, r;
  string str1, str2;
  cin >> p;
  cin.ignore();
  for (int i = 0; i < p; ++i) {
    getline(cin, str1);
    name_index.insert(make_pair(str1, i));
    index_name.insert(make_pair(i, str1));
  }

  // 初始化邻接矩阵为INF;
  vector<vector<int> > weight(p, vector<int>(p, INF));
  for (int i(0); i < p; ++i) {
    weight[i][i] = 0; // 对角线是0,自己到自己的距离是0
  }
  cin >> q;
  cin.ignore();
  int temp_w;
  for (int i = 0; i < q; ++i) {
    cin >> str1 >> str2 >> temp_w;
    cin.ignore();
    if (str1 != str2) { // 防止自环
    int a = name_index[str1];
    int b = name_index[str2];
    if (temp_w < weight[a][b]) // 可能有重边，取权值最小的
      weight[a][b] = weight[b][a] = temp_w; 
    }
  }

  cin >> r;
  cin.ignore();
  int *start = new int[r];
  int *end = new int[r];
  for (int i = 0; i < r; ++i) {
    cin >> str1 >> str2;
    cin.ignore();
    start[i] = name_index[str1];
    end[i] = name_index[str2];
  }

  for (int i = 0; i < r; ++i) {
    Dist *ans;
    Dijkstra(weight, start[i], ans);
    ShowPath(weight, ans, end[i]);
  }

#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
