// 插入排序
template <typename T>
void InsertSort(T &data, int n) {
  for(int i(1); i < n; ++i) {
    T temp = data[i];
    for(int j(i - 1); j >= 0 && temp < data[j]; --j)
      data[j + 1] = data[j];
    data[j + 1] = temp;
  }
}