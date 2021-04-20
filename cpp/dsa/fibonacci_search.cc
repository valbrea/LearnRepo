// 斐波那契查找（使前后两段的查找长度（比较次数）一致）
// 时间复杂度 = O(1.44∙log2n) 比二分A略有提高
#include "..\fibonacci\Fib.h" //引入Fib数列类
// Fibonacci查找算法（版本A）：在有序向量癿匙间[lo, hi)内查找元素e，0 <= lo <=
// hi <= _size
template <typename T> static int fibSearch(T *A, T const &e, int lo, int hi) {
  Fib fib(hi - lo); //用O(log_phi(n = hi - lo)时间创建Fib数列
  while (lo < hi) { //每步迭代可能要做两次比较刞断，有三个分支 while ( hi - lo <
                    // fib.get() ) fib.prev();
                    ////通过向前顺序查找（分摊O(1)）——至多迭代几次？ Rank mi =
                    // lo + fib.get() - 1; //确定形如Fib(k) - 1癿轴点
    if (e < A[mi])
      hi = mi; //深入前半殌[lo, mi)继续查找
    else if (A[mi] < e)
      lo = mi + 1; //深入后半殌(mi, hi)继续查找
    else
      return mi; //在mi处命中
  }              //成功查找可以提前终止
  return -1;     //查找失败
} //有多个命中元素时，不能保证返回秩最大者；失败时，简单地返回-1，而不能指示失败的位置