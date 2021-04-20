#include <iostream>
using namespace std;
void QuickSort(int a[], int low, int high) {
  if (low < high) {
    int i = low;
    int j = high;
    int index = a[i];
    while (i < j) {
      // 从右往左扫描，找比基准大的元素
      while (i < j && a[j] >= index)
        --j;
      // 找到后交换
      if (i < j)
        a[i++] = a[j];
      // 从左往右扫，找比基准小的元素
      while (i < j && a[i] < index)
        ++i;
      // 找到后交换
      if (i < j)
        a[j--] = a[i];
    }
    a[i] = index;
    QuickSort(a, low, i - 1);
    QuickSort(a, i + 1, high);
  } else {
    return;
  }
}
int main() {
  int a[] = {5, 3, 15, 24, 24, 15, 165, 43, 111, 3, 32, 25, 73, 86};
  QuickSort(a, 0, sizeof(a) / 4 - 1);
  for (int i(0); i < sizeof(a) / 4; ++i)
    cout << a[i] << " ";
  cout << endl;
  return 0;
}