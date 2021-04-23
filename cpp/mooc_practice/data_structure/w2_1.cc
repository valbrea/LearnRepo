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
  Node(const T &data) : data_(data) {}
  Node(const T &data, Node *pre, Node *suc)
      : data_(data), pre_(pre), suc_(suc) {}
};

template <typename T> class List {
public:
  typedef Node<T> ListNode;
  int size_;
  ListNode *head_;
  ListNode *tail_;
  List() : size_(0) {}
  ~List() {
    while (size_) {
      DeleteNode();
    }
  }
  // 创建N个节点
  void CreateNode(int n) {
    int num(1);
    ListNode *cur = new ListNode(num);
    head_ = cur;
    tail_ = cur;
    ++size_;
    --n;
    while (n--) {
      cur = new ListNode(++num, tail_, head_);
      tail_->suc_ = cur;
      tail_ = cur;
      ++size_;
    }
    //循环链表
    tail_->suc_ = head_;
    head_->pre_ = tail_;
  }
  // 寻找第m个节点，把head指向这个节点
  void FindNode(int m) {
    while (--m)
      head_ = head_->suc_;
  }
  // 删除head指向的节点
  void DeleteNode() {
    ListNode *temp = head_;
    temp->pre_->suc_ = temp->suc_;
    temp->suc_->pre_ = temp->pre_;
    head_ = head_->suc_;
    delete temp;
    --size_;
  }
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
  cout << joseph.head_->data_ << endl;
  return 0;
}