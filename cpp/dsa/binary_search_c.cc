template <typename T>
static int BinarySearch(T *a, const T &val, int low, int high) {
  while (low < high) { // 每步迭代仅需做一次比较判断，有两个分支
    int mid = (low + high) >> 1;
    (val < a[mid]) ? high = mid : low = mid + 1; // 经比较后确定深入[low, mid)或[mid + 1, high)
  } // 成功查找不能提前终止
  return --low; //循环结束时，low为大于val的元素的最小秩，故low - 1即不大于e的元素的最大秩
} //有多个命中元素时，总能返回秩最大者；查找失败时，返回失败的位置