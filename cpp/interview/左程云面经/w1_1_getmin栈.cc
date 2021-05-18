#include <iostream>
#include <stack>
using namespace std;
class GetMinStack {
private:
  stack<int> data_;
  stack<int> min_;

public:
  void Push(int new_num) {
    if (min_.empty())
      min_.push(new_num);
    else if (new_num <= GetMin())
      min_.push(new_num);
    else
      ;
    data_.push(new_num);
  }
  int Pop() {
    if (data_.empty()) {
      cerr << "Your stack is empty." << endl;
      return -1;
    }
    int value = data_.top();
    data_.pop();
    if (value == GetMin())
      min_.pop();
    return value;
  }
  int GetMin() {
    if (min_.empty()) {
      cerr << "Your stack is empty." << endl;
      return -1;
    }
    return min_.top();
  }
};
class GetMinStack2 {
// 思路： min_中同步压入new_num和min_.top()两者中较小的元素；
// 一直弹出min_.top()
};