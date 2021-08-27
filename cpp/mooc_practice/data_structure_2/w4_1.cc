/*
1. 置换选择排序
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述

给定初始整数顺串，以及大小固定并且初始元素已知的二叉最小堆（为完全二叉树或类似完全二叉树，且父元素键值总小于等于任何一个子结点的键值），要求利用堆实现置换选择排序，并输出第一个顺串。例如给定初始顺串29,14,35,13,以及堆（记为16
19 31 25 21 56 40）， 置换选择排序得到的第一个顺串为16 19 21 25。


输入
第一行包含两个整数，m为初始顺串的数的个数，n为二叉最小堆的大小

第二行包含m个整数，即初始顺串

第三行包含n个整数，即已经建好的堆的元素（有序，按照从堆顶到堆底，从左到右的顺序）

输出
输出包含一行，即第一个顺串。

样例输入
4 7
29 14 35 13
16 19 31 25 21 56 40
样例输出
16 19 21 25
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

void ReplacementSelect(queue<int> &runs, vector<int> &heap) {
  // 返回下次要用的堆
  make_heap(heap.begin(), heap.end(), greater<int>());
  //! 由于用的是stl的堆，会比较慢，而且不知道stl堆的shiftdown()
  //! 所以只有让其在插入时自动调整，所以结构和笔记上的稍有改动
  int mval, input;
  vector<int> next_heap;
  while (!runs.empty() && !heap.empty()) {
    mval = heap[0];                                     // 推出最小值
    pop_heap(heap.begin(), heap.end(), greater<int>()); // 弹出堆顶
    heap.pop_back();                                    // 弹出堆顶
    cout << mval << " ";                                // 输出堆顶
    input = runs.front(); // 从初始顺串读入一个记录
    runs.pop();
    if (input >= mval) {
      heap.push_back(input);
      push_heap(heap.begin(), heap.end(),
                greater<int>()); // 把合法输入放入堆顶，并调整
    } else {
      next_heap.push_back(input); // 把非法输入放到堆底，作为下一次建堆的初始值
      // --heap_last;                // 减小堆的大小（非实际大小）
    }
  }
  //把下次要用的堆建立好
  make_heap(next_heap.begin(), next_heap.end(), greater<int>());
  heap.assign(next_heap.begin(), next_heap.end());
}

int main() {
#ifdef LOCAL_DEBUG
  freopen("data_structure_2/.debug/w4_1.in", "r", stdin);
#endif

  int m, n;
  cin >> m >> n;
  queue<int> initial_runs;
  int key;
  for (int i(0); i < m; ++i) {
    cin >> key;
    initial_runs.push(key);
  }

  vector<int> initial_heap;
  for (int i(0); i < n; ++i) {
    cin >> key;
    initial_heap.push_back(key);
  }
  ReplacementSelect(initial_runs, initial_heap);

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
