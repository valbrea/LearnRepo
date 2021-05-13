/*
1. 由中根序列和后根序列重建二叉树
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 500ms 内存限制: 65535kB

描述

我们知道如何按照三种深度优先次序来周游一棵二叉树，来得到中根序列、前根序列和后根序列。
反过来，如果给定二叉树的中根序列和后根序列，或者给定中根序列和前根序列，可以重建一二叉树。
本题输入一棵二叉树的中根序列和后根序列，要求在内存中重建二叉树，最后输出这棵二叉树的前根序列。

用不同的整数来唯一标识二叉树的每一个结点，下面的二叉树


中根序列是9 5 32 67

后根序列9 32 67 5

前根序列5 9 67 32

输入
两行。第一行是二叉树的中根序列，第二行是后根序列。每个数字表示的结点之间用空格隔开。
结点数字范围0～65535。暂不必考虑不合理的输入数据。

输出
一行。由输入中的中根序列和后根序列重建的二叉树的前根序列。每个数字表示的结点之间用空格隔开。
*/
#include <cstdio>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
#define MAX 65565
typedef vector<int> tree;
int FindRoot(tree &post) { return post.back(); }
void PreOrder(tree &in, tree &post, tree &pre) {
  tree in_l, in_r, post_l, post_r;
  int root = FindRoot(post);
  pre.push_back(root);
  // 如果输入的只有1个节点，压入这个根节点就返回了
  if (post.size() <= 1) 
    return;
  // 如果输入只有2个节点，那压入剩余那个子树以后就可以返回了
  if (post.size() == 2) {
    pre.push_back(post.front());
    return;
  }
  // 否则中序和后序都拆成左右两个子树，递归
  tree::iterator root_index;
  root_index = find(in.begin(), in.end(), root);
  in_l.insert(in_l.end(), in.begin(), root_index);
  in_r.insert(in_r.end(), root_index + 1, in.end());
  post_l.insert(post_l.end(), post.begin(), post.begin() + in_l.size());
  post_r.insert(post_r.end(), post.begin() + in_l.size(), post.end() - 1);
  // 先进入左子树，后进入右子树
  PreOrder(in_l, post_l, pre);
  PreOrder(in_r, post_r, pre);
}
int main() {
  tree in_order, post_order;
  int n(0);
  while (cin >> n) {
    in_order.push_back(n);
    if (getchar() == '\n')
      break;
  }
  while (cin >> n) {
    post_order.push_back(n);
    if (getchar() == '\n')
      break;
  }
  tree pre_order;
  PreOrder(in_order, post_order, pre_order);
  tree::iterator ii;
  for(ii = pre_order.begin(); ii != pre_order.end(); ++ii)
    cout << *ii << " ";
  cout << endl;

  return 0;
}