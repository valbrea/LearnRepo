/*
2. 二叉搜索树
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意：总时间限制: 1000ms 内存限制: 1024kB

描述
   二叉搜索树在动态查表中有特别的用处，一个无序序列可以通过构造一棵二叉搜索树变成一个有序序列，构造树的过程即为对无序序列进行排序的过程。每次插入的新的结点都是二叉搜索树上新的叶子结点，在进行插入操作时，不必移动其它结点，只需改动某个结点的指针，由空变为非空即可。

   这里，我们想探究二叉树的建立和序列输出。

输入
只有一行，包含若干个数字，中间用空格隔开。（数字可能会有重复）

输出
输出一行，对输入数字建立二叉搜索树后进行前序周游的结果。

样例输入
41 467 334 500 169 724 478 358 962 464 705 145 281 827 961 491 995 942 827 436

样例输出
41 467 334 169 145 281 358 464 436 500 478 491 724 705 962 827 961 942 995
*/
#include <cstdio>
#include <deque>
#include <iostream>
using namespace std;
template <typename T> class BinaryTreeNode {
#define NodePos(T) BinaryTreeNode<T> *
public:
  T data_;
  NodePos(T) parent_;
  NodePos(T) left_child_;
  NodePos(T) right_child_;
  BinaryTreeNode()
      : data_(0), parent_(NULL), left_child_(NULL), right_child_(NULL) {}
  BinaryTreeNode(const T &data, NodePos(T) parent)
      : data_(data), parent_(parent), left_child_(NULL), right_child_(NULL) {}
};
template <typename T> void PreOrder(NodePos(T) & root) {
  if (root != NULL) {
    cout << root->data_ << " ";
    PreOrder(root->left_child_);
    PreOrder(root->right_child_);
  }
}
template <typename T>
NodePos(T) Search(NodePos(T) root, T &num, NodePos(T) & parent) {
  if (!root || num == root->data_) // 如果找到了该数据就返回，否则返回一个空指针
    return root;
  else {
    parent = root; // 记录父节点
    if (num < root->data_)
      return Search(root = root->left_child_, num, parent);
    else
      return Search(root = root->right_child_, num, parent);
  }
}
template <typename T> bool Insert(NodePos(T) & root, T &num) {
  NodePos(T) parent = NULL;
  // parent是引用传入，会被修改为最后找到的节点位置
  NodePos(T) cur = Search(root, num, parent);
  // 如果找到了已存在的数据，插入失败
  if (cur && num == cur->data_)
    return false;
  else { // 否则cur就是个空节点，parent就是该节点的父节点
         // 需要建立一个新的子节点，根据大小确定该节点插入左边还是右边
    cur = new BinaryTreeNode<T>(num, parent);
    if (cur->data_ < parent->data_)
      parent->left_child_ = cur;
    else
      parent->right_child_ = cur;
    return true;
  }
}
int main() {
  deque<int> nums;
  int n;
  while (cin >> n) {
    nums.push_back(n);
    if (getchar() == '\n')
      break;
  }
  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(nums.front(), NULL);
  nums.pop_front();
  while (!nums.empty()) {
    n = nums.front();
    nums.pop_front();
    Insert(root, n);
  }
  PreOrder(root);
  cout << endl;
  return 0;
}
