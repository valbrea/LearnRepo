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

提示
第一组样例数据的第二行末尾的8 -8，因为幂次-8为负数，所以这一行数据结束，8
-8不要参与计算。
*/
#include <iostream>
using namespace std;

struct Data {
  int coefficient_;
  int exponent_;
  Data() : coefficient_(0), exponent_(0) {}
  Data(int coe, int exp) : coefficient_(coe), exponent_(exp) {}
  bool operator>=(Data &b) const { return exponent_ >= b.exponent_; }
};
ostream &operator<<(ostream &os, const Data &data) {
  os << "[" << data.coefficient_ << " " << data.exponent_ << "] ";
  return os;
}

template <typename T> struct Node {
  T data_;
  Node *pre_;
  Node *suc_;

  Node() {}
  Node(const T &data) : data_(data), pre_(nullptr), suc_(nullptr) {}
  Node(const T &data, Node *pre, Node *suc)
      : data_(data), pre_(pre), suc_(suc) {}
  Node<T> *InsertAsPred(const T &data) {
    Node<T> *temp = new Node<T>(data, pre_, this);
    pre_->suc_ = temp;
    pre_ = temp;
    return temp;
  }
};

template <typename T> class List {
public:
  typedef Node<T> ListNode;
  int size_;
  ListNode *head_;
  ListNode *tail_;
  List() : size_(0) {
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
  // 队尾创建节点
  void CreateNode(const T &data) {
    ListNode *cur = new ListNode(data, tail_->pre_, tail_);
    tail_->pre_->suc_ = cur;
    tail_->pre_ = cur;
    ++size_;
  }
  // 有序列表的二路归并：
  // 当前列表中自p_first起的first_size个元素，与列表lst中自p_second起的second_size个元素归并
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
  ListNode *InsertBefore(ListNode *pos, const T &data) {
    ++size_;
    return pos->InsertAsPred(data);
  }
  // 这里由于需要在函数里改变p_first所指的位置，需要指向p_first的引用
  void Merge(ListNode *&p_first, int first_size, List<T> &lst,
             ListNode *p_second, int second_size) {
    ListNode *pp = p_first->pre_;
    while (second_size > 0) { // 若第二个链表没合并完
      // 若第一个链表没合并完且第一个链表中节点的数据 <= 第二个链表中节点的数据
      if ((first_size > 0) && (p_first->data_ >= p_second->data_)) { //重载>=
        // 第一个链表归入合并的链表，并替换为其直接后继
        p_first = p_first->suc_;
        if (p_second == p_first)
          break; // 如果第一个链表耗尽则结束
        --first_size;
      } else {
        // 若第一个链表已经耗尽，或第一个链表中节点的数据>第二个链表中节点的数据
        // 在第一个链表的前面插入第二个链表中的p_second元素
        ListNode *temp = p_second;
        p_second = p_second->suc_;
        InsertBefore(p_first, lst.DeleteNode(temp));
        --second_size;
      }
    }
    p_first = pp->suc_; // 确定归并后区间的起点
  }
  // 这里由于需要在函数里改变p_first所指的位置，需要指向p_first的引用
  void MergeSort(ListNode *&p_begin, int size) {
    if (size < 2)
      return;
    int mid = size >> 1;
    ListNode *p_mid = p_begin;
    for (int i(0); i < mid; ++i)
      p_mid = p_mid->suc_;        // elem_mid指向mid处
    MergeSort(p_begin, mid);      // 归并排序[1, mid)
    MergeSort(p_mid, size - mid); // 归并排序[mid, tail)
    Merge(p_begin, mid, *this, p_mid, size - mid);
    // Print(p_begin, size);
  }
  void Print(ListNode *cur, int n) {
    while (n--) {
      cout << cur->data_;
      cur = cur->suc_;
    }
    cout << endl;
  }
};
List<Data> *Add(List<Data> *)
int main() {
  int n;
  cin >> n;
  cin.ignore();
  List<Data> poly1, poly2;
  while (n--) {
    int coe(0), exp(0);
    while (cin >> coe >> exp) {
      if (exp < 0)
        break;
      poly1.CreateNode(Data(coe, exp));
    }
    cin.ignore();
    while (cin >> coe >> exp) {
      if (exp < 0)
        break;
      poly2.CreateNode(Data(coe, exp));
    }
    // 这里必须先建立一个临时变量begin1保存第一个元素的地址
    // 然后MergeSort的第一个参数传入begin1
    // 而不能传入poly1.head_->suc_，因为MergeSort是引用传入

    // 如果传入的是poly1.head_->suc_的引用给begin
    // 当函数里面begin = begin->suc_;语句执行以后，
    // poly1.head_->suc_也就跟着改变了
    // 但在MergeSort里面使用了pp来保存begin->pre_的地址，也就是poly1.head_
    // 改变了begin就相当于就改变了poly1.head_->suc_，
    // 也就相当于pp->suc_的内容也会跟着一起改变
    Node<Data> *begin1 = poly1.head_->suc_;
    Node<Data> *begin2 = poly2.head_->suc_;
    poly1.MergeSort(begin1, poly1.size_);
    poly2.MergeSort(begin2, poly2.size_);
    cout << "**************************************" << endl;
    poly1.Print(poly1.head_->suc_, poly1.size_);
    poly2.Print(poly2.head_->suc_, poly2.size_);
    
  }
  return 0;
}
