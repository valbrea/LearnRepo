/*
编程题 ＃3
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
写一个二维数组类 Array2,使得下面程序的输出结果是：

0,1,2,3,

4,5,6,7,

8,9,10,11,

next

0,1,2,3,

4,5,6,7,

8,9,10,11,

程序：
#include <cstring>
#include <iostream>
using namespace std;
// 在此处补充你的代码
int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
*/
#include <cstring>
#include <iostream>
using namespace std;
// 在此处补充你的代码
class Array2 {
private:
  int **ptr_; // 指向动态分配二维空间的指针
  int m_, n_; // 用来记录二维数组行数和列数

public:
  // 构造函数
  Array2(const int &m = 0, const int &n = 0) : m_(m), n_(n) {
    if (m == 0 || n == 0)
      ptr_ = nullptr;
    else {
      ptr_ = new int *[m]; // 先分配m行
      for (int i(0); i < m; ++i)
        ptr_[i] = new int[n]; // 每一行都是一个n列的数组
    }
  }
  // 复制构造函数，深拷贝，本题不需要
  //   Array2(const Array2 &arr) {
  //     if (arr.ptr_) {
  //       ptr_ = new int *[arr.m_];
  //       for (int i(0); i < arr.m_; ++i)
  //         ptr_[i] = new int[arr.n_];
  //     } else {
  //       ptr_ = nullptr;
  //       m_ = 0;
  //       n_ = 0;
  //     }
  //   }
  // 析构函数 如果ptr_非空，就释放空间
  ~Array2() {
    if (ptr_) {
      // 注意：二维数组释放的时候，需要先释放每一行指向的n维数组，再释放ptr指向的m维数组
      for (int i(0); i < m_; ++i)
        delete[] ptr_[i];
      delete[] ptr_;
    }
  }

  // 重载[]运算符
  // 二维数组这里要返回int* 而不是int&，这样int*可以再使用后面的另一个[]
  int *operator[](const int &i) { return ptr_[i]; }

  // 重载()运算符
  int &operator()(const int &i, const int &j) { return ptr_[i][j]; }

  // 重载=运算符
  Array2 &operator=(const Array2 &arr) {
    if (ptr_ == arr.ptr_) // 如果arr = arr
      return *this;
    if (arr.ptr_ == nullptr) { // 如果输入的是空数组
      if (ptr_)
        delete[] ptr_;
      ptr_ = nullptr;
      m_ = 0;
      n_ = 0;
      return *this;
    }
    if (m_ < arr.m_ || n_ < arr.n_) { // 如果原本数组大小比输入数组小
      if (ptr_)                       // 如果原本数组不是空的
        delete[] ptr_;
      ptr_ = new int *[arr.m_];
      for (int i(0); i < arr.m_; ++i)
        ptr_[i] = new int[arr.n_];
    }
    for (int i(0); i < arr.m_; ++i)
      for (int j(0); j < arr.n_; ++j)
        ptr_[i][j] = arr.ptr_[i][j];
    m_ = arr.m_;
    n_ = arr.n_;
    return *this;
  }
};

int main() {
  Array2 a(3, 4); // 构造函数
  int i, j;
  for (i = 0; i < 3; ++i)
    for (j = 0; j < 4; j++)
      a[i][j] = i * 4 + j; // 运算符[]重载
  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 4; j++) {
      cout << a(i, j) << ","; // 这里不会是调用构造函数，因为不能返回值
      // 而且如果是<<重载也不可能（cout.operator<<(a(i,
      // j))）里面还是有未定义的a() 所以是运算符()的重载
    }
    cout << endl;
  }
  cout << "next" << endl;
  Array2 b;
  b = a; // 运算符=重载，这里不是调用复制构造函数，因为不是赋值初始化
  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 4; j++) {
      cout << b[i][j] << ",";
    }
    cout << endl;
  }
  return 0;
}