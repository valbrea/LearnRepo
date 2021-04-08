/*
编程题＃1
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
实现一个三维数组模版CArray3D，可以用来生成元素为任意类型变量的三维数组，使得下面程序输出结果是：

0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,

注意，只能写一个类模版，不能写多个。
提示
提示：类里面可以定义类，类模版里面也可以定义类模版。例如：
class A
{
    class B {

    };
};

template
class S
{
    T x;
    class K {
        T a;
    };
};
*/
#include <iostream>
using namespace std;
// 在此处补充你的代码
template <class T> class CArray3D {
  T m_, n_, k_;
  T ***arr_;

public:
  CArray3D(const T &ii, const T &jj, const T &kk)
      : m_(ii), n_(jj), k_(kk), arr_() {
    arr_ = new T **[m_];
    for (int i(0); i < m_; ++i) {
      arr_[i] = new T *[n_];
      for (int j(0); j < n_; ++j) {
        arr_[i][j] = new T[k_];
      }
    }
  }
  ~CArray3D() {
    for (int i(0); i < m_; ++i) {
      for (int j(0); j < n_; ++j) {
        delete[] arr_[i][j];
      }
      delete[] arr_[i];
    }
    delete arr_;
  }
  // 三维数组要返回T**类型，这样后面可以使用[][]
  T **operator[](const T &ii) {
      return arr_[ii];
  }
};
int main() {
  CArray3D<int> a(3, 4, 5);
  int No = 0;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      for (int k = 0; k < 5; ++k)
        a[i][j][k] = No++;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      for (int k = 0; k < 5; ++k)
        cout << a[i][j][k] << ",";
  return 0;
}