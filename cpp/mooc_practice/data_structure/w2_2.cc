/*
2. 多项式加法
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 5000kB

描述
我们经常遇到两多项式相加的情况，在这里，我们就需要用程序来模拟实现把两个多项式相加到一起。首先，我们会有两个多项式，每个多项式是独立的一行，每个多项式由系数、幂数这样的多个整数对来表示。

如多项式2x20- x17+ 5x9- 7x7+ 16x5+ 10x4 + 22x2- 15

对应的表达式为：2 20 -1 17 5 9 - 7 7 16 5 10 4 22 2 -15 0。

为了标记每行多项式的结束，在表达式后面加上了一个幂数为负数的整数对。

同时输入表达式的幂数大小顺序是随机的。

我们需要做的就是把所给的两个多项式加起来。

输入
输入包括多行。

第一行整数n,表示有多少组的多项式需要求和。(1 < n < 100)

下面为2n行整数，每一行都是一个多项式的表达式。表示n组需要相加的多项式。

每行长度小于300。

输出
输出包括n行，每行为1组多项式相加的结果。

在每一行的输出结果中，多项式的每一项用“[x y]”形式的字符串表示，x是该项的系数、y
是该项的幂数。要求按照每一项的幂从高到低排列，即先输出幂数高的项、再输出幂数低的项。

系数为零的项不要输出。

样例输入
2
-1 17 2 20 5 9 -7 7 10 4 22 2 -15 0 16 5 0 -1
2 19 7 7 3 17 4 4 15 10 -10 5 13 2 -7 0 8 -8
-1 17 2 23 22 2 6 8 -4 7 -18 0 1 5 21 4 0 -1
12 7 -7 5 3 17 23 4 15 10 -10 5 13 5 2 19 9 -7

样例输出
[ 2 20 ] [ 2 19 ] [ 2 17 ] [ 15 10 ] [ 5 9 ] [ 6 5 ] [ 14 4 ] [ 35 2 ] [ -22 0 ]
[ 2 23 ] [ 2 19 ] [ 2 17 ] [ 15 10 ] [ 6 8 ] [ 8 7 ] [ -3 5 ] [ 44 4 ] [ 22 2 ]
[ -18 0 ]
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
  ListNode *head_;
  ListNode *tail_;
  List() : size_(0), {
    head_ = new ListNode();
    tail_ = new ListNode();
    head_->suc_ = tail_;
    tail_->pre_ = head_;
  }
  ~List() {
    while (size_) {
      DeleteNode(head_->suc_);
    }
  }
  // 在队尾创建节点
  void CreateNode(T &data) {
    ListNode *temp = new ListNode(data, tail_->pre_, tail_);
    tail_->pre_->suc_ = temp;
    tail_->pre_ = temp;
    ++size_;
  }
  // 删除合法节点pos， 返回其数值
  T DeleteNode(ListNode *pos) {
    T data = pos->data_;
    pos->pre_->suc_ = pos->suc_;
    pos->suc_->pre_ = pos->pre_;
    delete pos;
    --size_;
    return data;
  }
  // 在节点pos前插入一个数据为data的节点作为前驱
  ListNode *InsertBefore(ListNode *pos, T &data) {
    ++size_;
    ListNode *temp = new ListNode(data, pos->pre_, pos);
    pos->pre_->suc = temp;
    pos->pre_ = temp;
    return temp;
  }
  // 有序列表的二路归并：
  // 当前列表中自p_first起的first_size个元素，与列表lst中自p_second起的second_size个元素归并
  void Merge(ListNode *p_first, int first_size, List<T> &lst, ListNode *p_second,
             int second_size) {
    ListNode *pp = p_first->pre_;
    while (second_size > 0) { // 若第二个链表没合并完
      // 若第一个链表没合并完且第一个链表中节点的指数 <= 第二个链表中节点的指数
      if ((first_size > 0) && (p_first->data_ <= p_second->data_)) {
        // 第一个链表归入合并的链表，并替换为其直接后继
        p_first = p_first->suc_;
        if (p_second == p_first)
          break; // 如果第一个链表耗尽则结束
        --first_size;
      } else {
        // 若第一个链表已经耗尽，或第一个链表中节点的指数 > 第二个链表中节点的指数
        // 在第一个链表的前面插入第二个链表中的p_second元素
        InsertBefore(p_first, lst.DeleteNode((p_second = p_second->suc_)->pred));
        --second_size;
      }
      p_first = pp->suc_; // 确定归并后区间的起点
    }
  }
  void MergeSort(ListNode *p_begin, int size) {
    if (size_ < 2)
      return;
    int mid = size_ >> 1;
    ListNode *p_mid = p_begin;
    for (int i(0); i < mid; ++i)
      p_mid = p_mid->suc_;              // elem_mid指向mid处
    MergeSort(p_begin, mid);            // 归并排序[1, mid]
    MergeSort(p_mid->suc_, size - mid); // 归并排序[mid + 1, size]
    Merge(p_begin, mid, *this, p_mid->suc_, size - mid)
  }

  int main() {
    int n;
    cin >> n;
    cin.ignore();
    List<int> poly1, poly2;
    while (n--) {
      int coe(0), exp(0);
      while ((cin >> coe >> exp) >= 0) {
        poly1.CreateNode(make_pair(coe, exp));
      }
      while ((cin >> coe >> exp) >= 0) {
        poly2.CreateNode(make_pair(coe, exp));
      }
    }
  }
  return 0;
}