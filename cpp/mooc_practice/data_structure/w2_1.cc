/*
1. 约瑟夫问题
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
有n只猴子，按顺时针方向围成一圈选大王（编号从1到n），从第1号开始报数，一直数到m，数到m的猴子退出圈外，
剩下的猴子再接着从1开始报数。就这样，直到圈内只剩下一只猴子时，这个猴子就是猴王，编程求输入n，m后，输出最后猴王的编号。

输入
输入包含两个整数，第一个是n，第二个是m (0 < m,n <=300)。

输出
输出包含一行，即最后猴王的编号。

样例输入
12 4

样例输出
1
*/
#include <iostream>
using namespace std;
template <typename T> struct Node {
  T data_;
  Node *pre_;
  Node *suc_;
  Node() {}
  Node(const T &data, Node *pre, Node *suc)
      : data_(data), pre_(pre), suc_(suc) {}
};

template <typename T> class List {
public:
  typedef Node<T> ListNode;
  int size_;
  ListNode *cur_;
  List() : size_(0), cur_() {}
  ~List() {
    while (size_) { DeleteNode(); }
  }
  // 创建N个节点，返回最后一个节点的编号
  void CreateNode(int n) {
    size_ = n;
    // 起始编号是1
    int x = 0;
    ListNode *tail = new ListNode(++x, cur_, cur_);
    cur_ = tail;
    while (--n) {
      tail = new ListNode(++x, tail, cur_);
      tail->pre_->suc_ = tail;
    }
    cur_->pre_ = tail;
  }
  // 寻找第m个节点，返回这个节点
  void *FindNode(int m) {
    while (m--) {
      cur_ = cur_->suc_;
    }
  }
  // 删除某个节点，返回新的size_
  int DeleteNode() {
    if (size_ <= 0)
      return 0;
    ListNode *temp = cur_;
    temp->pre_->suc_ = temp->suc_;
    temp->suc_->pre_ = temp->pre_;
    cur_ = cur_->suc_;
    delete temp;
    --size_;
    return size_;
  };
};

int main() {
  int n, m;
  cin >> n >> m;
  cin.ignore();
  List<int> joseph;
  joseph.CreateNode(n);
  while (joseph.size_ > 1) { 
    joseph.FindNode(m);
    joseph.DeleteNode();
  }
  cout << joseph.cur_->data_ << endl;
  return 0;
}