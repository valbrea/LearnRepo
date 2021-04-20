// 二分查找，版本B， 只分为[low, mid) 和[mid, high)两个区间
// 在这一版本中，只有在向量有效区间宽度缩短至1个单元时算法才会终止，而不能如版本A那样，
// 一旦命中就能及时返回。因此，最好情况下的效率有所倒退。当然，作为补偿，最坏情况下的
// 效率相应地有所提高。实际上无论是成功查找或失败查找，版本B各分支的查找长度更加接近，
// 故整体性能更趋稳定。

template <typename T>
static int BinarySearch(T *a, const T &val, int low, int high) {
  while (1 <hi - lo) { // 每步迭代仅需做一次比较判断，有两个分支；成功查找不能提前终止
    int mid = (low + high) >> 1;
    (val < a[mid]) ? high = mid : low = mid; // 经比较后确定深入[lo, mi)或[mi, hi)
  } //出口时high = low + 1，查找区间仅含一个元素a[low]
  return (val = a[low]) ? low : -1; //查找成功时返回对应的秩；否则统一返回-1
} //有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地迒回-1，而不能指示失败的位置