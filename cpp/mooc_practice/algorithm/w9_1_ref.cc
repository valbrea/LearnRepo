#include <iostream>
#include <stdio.h>
using namespace std;
#define MAXN 100003

int cmp(const void *x, const void *y) { return *(int *)x - *(int *)y; }

int a[MAXN];

int N, C;

bool greed(int x) // 贪心法，间隔x 能否放下c 只羊

{

  int cn = 0;

  int p = a[0];

  for (int i = 1; i < N; i++)

    if (a[i] >= p + x)

    {

      cn++;

      p = a[i];
    }

  if (cn >= C - 1)

    return true;

  return false;
}

int main()

{

  while (scanf("%d%d", &N, &C) != EOF)

  {

    for (int i = 0; i < N; i++)

      scanf("%d", &a[i]);

    qsort(a, N, sizeof(a[0]), cmp); // 从小到大排序

    int left, right, mid;

    left = 0;

    right = (a[N - 1] - a[0]) / (C - 1); // 间隔最大的可能取值

    while (left <= right)

    {

      mid = (left + right) / 2;

      printf("%d %d %d/n", left, right, mid);

      if (greed(mid)) // 如果间隔为mid ，能够放下c 只羊，则最大间隔>=mid

        left = mid + 1;

      else // 没办法放下，则最大间隔<=mid-1

        right = mid - 1;
    }

    printf(
        "%d/n",
        left -
            1); // 这一点我开始错误，误以为是mid
                // ，最后一次循环肯定是left==right==mid, 但是mid 有可能不能放下c
                // 只羊，我们能够确定left 左边的能够放下c 只羊，right
                // 右边的不能放下c 只羊，可是mid 不能确定；如果mid
                // 能够放下，则left 右移，left=right+1 ，显然不能放下，则left-1
                // 是最大值；如果mid 不能放下，则left 不变，left
                // 依然不能不能放下，left-1 是最大值。
  }

  return 0;
}
