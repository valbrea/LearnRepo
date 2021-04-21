template <typename T> void SelectSort(T &data, int n) {
  int max_index = 0;
  for (int i(n); i >= 0; --i) {
    for (int j(i - 1); j >= 0; --j) {
      if (data[j] >= data[max_index])
        max_index = j;
    }
    swap(data[max_index], data[i]);
  }
}