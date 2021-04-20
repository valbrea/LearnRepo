//  归并排序，T(n) = O(nlogn), 稳定排序
// 步骤1：无序向量的递归分解
template <typename T>
void MergeSort(T *data, int low, int high) { // 0 <= low < high <= size
  if (high - low < 2)                        // 只剩一个元素
    return;
  int mid = (low + high) >> 2; // 以中点为界
  MergeSort(data, low, mid);   // 分别排序
  MergeSort(data, mid, high);
  Merge(data, low, mid, high); // 归并
}
// 步骤2：有序向量的逐层归并
template <typename T> void Merge(T *data, int low, int mid, int high) {
  // 合并后的向量a[0, hi - lo) = data[lo, hi)
  T *a = data + low;
  // 前子向量b[0, len_b) = data[low, mid)
  int len_b = mid - low;
  T *b = new T[len_b];
  // 复制前子向量
  for (int i(0); i < len_b; b[i] = a[i++])
    ;
  // 后子向量c[0, len_c) = data[mid, high)
  int len_c = high - mid;
  T *c = data + mid;
  // b[j]和c[k]中的小者续至a末尾
  for (int i(0), j(0), k(0); (j < len_b) || (k < len_c); ) {
    // 这里的<=保证了稳定性，只有c[k]严格小于b[j]时，才会先归并c的元素
    //  否则在遇到相同大小的元素时都是优先归并b中的元素

    // 当b中的元素未耗尽，且b[j] <= c[k]，或者c中的元素已经耗尽时
    if ((j < len_b) && (!(k < len_c) || (b[j] <= c[k])))
      a[i++] = b[j++];
    if ((k < len_c) && (!(j < len_c) || (c[k] < b[j])))
      a[i++] = c[j++];

    // 可简化为：
    // 如果c未耗尽且c[k] < b[j]，优先归并c[k]
    // if ((k < len_c) && (c[k] < b[j]))
    //   a[i++] = c[k++];
    // 如果c耗尽了，或者b[j] <= c[k])，优先归并b[k]
    // if ((len_c <= k) || (b[j] <= c[k]))
    //   a[i++] = c[j++];
  }
  delete[] b;
  //归并后得到完整的有序向量[low, high)
}