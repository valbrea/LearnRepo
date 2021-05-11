/*
2. 实现堆结构
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 3000ms 内存限制: 65535kB

描述
定义一个数组，初始化为空。在数组上执行两种操作：

1、增添1个元素，把1个新的元素放入数组。

2、输出并删除数组中最小的数。

使用堆结构实现上述功能的高效算法。

输入
第一行输入一个整数t，代表测试数据的组数。

对于每组测试数据，第一行输入一个整数n，代表操作的次数。

每次操作首先输入一个整数type。

当type=1，增添操作，接着输入一个整数u，代表要插入的元素。

当type=2，输出删除操作，输出并删除数组中最小的元素。

1<=n<=100000。

输出
每次删除操作输出被删除的数字。

样例输入
2
5
1 1
1 2
1 3
2
2
4
1 5
1 1
1 7
2

样例输出
1
2
1
*/
#include <deque>
#include <iostream>
using namespace std;

template <typename T> class Minheap {
public:
  T *heap_array_;
  int current_size_;
  int maxsize_;

  Minheap(const int maxsize) : maxsize_(maxsize) {}
  virtual ~Minheap(){delete[] heap_array_};

  int Parent(int pos) { return ((pos - 1) / 2); }
  bool InsertElem(const T &elem);
  int DeleteMinElem();
  void ShiftUp(int pos);
  void ShiftDown(int pos);
};

int main() {
  int t;
  cin >> t;
  cin.ignore();
  while (t--) {
    int n;
    cin >> n;
    cin.ignore();
    while (n--) {
      int type, u;
      cin >> type >> u;
      switch (type) {
      case 1:
        HeapInsertElem(u);
        break;
      case 2:
        HeapDeleteMinElem();
        break;

      default:
        break;
      }
    }
  }

  return 0;
}
template <typename T> void Minheap<T>::ShiftUp(int pos) {
  int temp_pos = pos;
  T temp = heap_array_[temp_pos];
  while ((temp_pos > 0) && (heap_array_[Parent(temp_pos) > temp])) {
    heap_array_[temp_pos] = heap_array_[Parent(temp_pos)];
    temp_pos = Parent(temp_pos);
  }
  heap_array_[temp_pos] = temp;
}
template <typename T> void Minheap<T>::ShiftDown(int pos) {
  int i = pos;             // 标识父节点
  int j = 2 * i + 1;       // 标识关键值较小的子节点
  T temp = heap_array_[i]; //  保存父节点
  while (j < current_size_) {
    if ((j < current_size_ - 1) && (heap_array_[j] > heap_array_[j + 1]))
      ++j; // 确保当前j指向关键值较小的子节点
    if (temp > heap_array_[j]) {
      heap_array_[i] = heap_array_[j];
      i = j;
      j = 2 * j + 1; // 如果temp更大就向下层继续
    } else
      break; // 到了叶层
  }
  heap_array_[i] = temp; // 如果当前层temp < 当前j的关键值（即大于i的所有叶节点)，
            // 当前层i = temp;
}
template <typename T> bool Minheap<T>::InsertElem(const T &elem) {
  if (current_size_ == maxsize_)
    return false;
  heap_array_[current_size_] = elem;
  ShiftUp(current_size_);
  ++current_size_;
  return true;
}
