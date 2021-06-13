/*
思路：https://blog.csdn.net/niushuai666/article/details/6981689
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define N 50010

struct node {
  int pre;
  int relation;
};
node p[N];

int find(int x) //查找根结点
{
  int temp;
  if (x == p[x].pre)
    return x;
  temp = p[x].pre; //路径压缩
  p[x].pre = find(temp);
  p[x].relation = (p[x].relation + p[temp].relation) % 3; //关系域更新
  return p[x].pre;                                        //根结点
}

int main() {
  int n, k;
  int ope, a, b;
  int root1, root2;
  int sum = 0; //假话数量
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) //初始化
  {
    p[i].pre = i;
    p[i].relation = 0;
  }
  for (int i = 1; i <= k; ++i) {
    scanf("%d%d%d", &ope, &a, &b);
    if (a > n || b > n) //条件2
    {
      sum++;
      continue;
    }
    if (ope == 2 && a == b) //条件3
    {
      sum++;
      continue;
    }
    root1 = find(a);
    root2 = find(b);
    if (root1 != root2) // 合并
    {
      p[root2].pre = root1;
      p[root2].relation = (3 + (ope - 1) + p[a].relation - p[b].relation) % 3;
    } else {
      if (ope == 1 && p[a].relation != p[b].relation) {
        sum++;
        continue;
      }
      if (ope == 2 && ((3 - p[a].relation + p[b].relation) % 3 != ope - 1)) {
        sum++;
        continue;
      }
    }
  }
  printf("%d\n", sum);
  return 0;
}