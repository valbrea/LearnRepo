// 前提：有序区间！
// 二分查找，版本A
// 成功和失败的时间复杂度大概是 O(1.5*logn)
template <typename T>
static int BinarySearch(T *a, T const &val, int low, int high) {
  while (low < high) {
    int mid = (low + high) >> 1; // 以中点为轴点
    if (val < a[mid])
      high = mid; // 查找前半段[low, mid)
    else if (a[mid] < val)
      low = mid + 1; // 查找后半段[mid + 1, high)
    else
      return mid; // mid处命中
  } //成功查找可以提前终止
  return -1; // 查找失败
}