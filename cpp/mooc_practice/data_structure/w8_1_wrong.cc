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
#define LOCAL // 本地调试宏定义，提交代码时注释掉此行
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

typedef enum { kUnvisited, kVisited } Vstatus;

struct Vertex {
  string data_;
  int index_;
  int in_degree_, out_degree_;
  Vstatus status_;
  int parent_;
  Vertex(string const &s = "", int index = -1)
      : // 构造新顶点
        data_(s), index_(index), in_degree_(0), out_degree_(0),
        status_(kUnvisited), parent_(-1) {}
};
struct Edge {
  int from_, to_;
  int weight_;
  Edge() : from_(-1), to_(-1), weight_(0) {}
  Edge(int from, int to, int weight) : from_(from), to_(to), weight_(weight) {}

  class Graph {
    // *图的ADT
  private:
    vector<Vertex> V;
    vector<vector<Edge *>> E;

  public:
    int num_vertex_;
    int num_edge_;
    int *mark_; // 顶点访问标记

    int VerticesNum() { return num_vertex_; }
    int EdgesNum() { return num_edge_; }

    void InsertVertex(string const &s) {
      V.push_back(Vertex(s, ++num_vertex_));
    }
    void InsertEdge(string from, string to, int weight) {
      if (IsExist(from, to))
    }
    void IsExist(int i, int j) { // 边i, j是否存在
      return (0 <= i) && (i < num_vertex_) && (0 <= j) && (j <= num_vertex_) &&
             E[i][j] != NULL;
    }
    int FromVertex(Edge &one_edge) { return one_edge.from_; }
    int ToVertex(Edge &one_edge) { return one_edge.to_; }
    int Weight(Edge &one_edge) { return one_edge.weight_; }
  } graph;

  class Dist {
  public:
    int index_;  // 顶点索引
    int length_; // 最短路长度
    int pre_;    // 最后经过的顶点
    // bool operator<(Dist &d2) { return length_ < d2.length_; }
    Dist() : index_(-1), length_(0), pre_(-1) {}
    Dist(int l) : index_(-1), length_(l), pre_(-1) {}
  };
  void Dijkstra(Graph &g, int s, Dist *&min_d) {
    min_d = new Dist[g.VerticesNum()]; // 记录当前最短路径长度
    for (int i = 0; i < g.VerticesNum(); ++i) {
      // 初始化
      g.mark_[i] = kUnvisited;
      min_d[i].index_ = i;
      min_d[i].length_ = INF;
      min_d[i].pre_ = s;
    }
    min_d[s].length_ = 0;
    priority_queue<Dist> minheap;
    minheap.push(min_d[s]);

    for (int i(0); i < g.VerticesNum(); ++i) {
      bool found = false;
      Dist d;
      while (!minheap.empty()) {
        d = minheap.top();
        minheap.pop();
        if (g.mark_[d.index_] == kUnvisited) {
          found = true;
          break;
        }
      }
      if (!found) // 有不可达点就跳出循环
        break;
      int v = d.index_;
      g.mark_[v] = kVisited;
      for (Edge e = g.FirstEdge(v); g.Isedge(e); e = g.NextEdge(e)) {
        if (min_d[g.ToVertex(e)].length_ > (min_d[v].length_ + g.Weight(e))) {
          min_d[g.ToVertex(e)].length_ = min_d[v].length_ + g.Weight(e);
          min_d[g.ToVertex(e)].pre_ = v;
          minheap.push(min_d[g.ToVertex(e)]);
        }
      }
      for (Vertex v = g.FirstVertex(); g.IsExist(v); v = g.NextNbr(v)) {
      }
    }
  }
  int main() {
#ifdef LOCAL
    freopen(".debug/w8_1.in", "r", stdin);
#endif

    int p, q, r;
    string str1, str2;
    cin >> p;
    cin.ignore();
    graph.num_vertex_ = p;
    for (int i = 0; i < p; ++i) {
      getline(cin, str1);
      graph.InsertVertex(str1);
    }
    cin >> q;
    cin.ignore();
    int temp_w;
    for (int i = 0; i < q; ++i) {
      cin >> str1 >> str2 >> temp_w;
      cin.ignore();
      graph.InsertEdge(str1, str2, temp_w);
    }

    cin >> r;
    cin.ignore();
    string *start = new string[r];
    string *end = new string[r];
    for (int i = 0; i < r; ++i) {
      cin >> str1 >> str2;
      cin.ignore();
      start[i] = str1;
      end[i] = str2;
    }

#ifdef LOCAL
    cout << endl
         << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

    return 0;
  }
