/*
2. 树的镜面映射
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
一棵树的镜面映射指的是对于树中的每个结点，都将其子结点反序。例如，对左边的树，镜面映射后变成右边这棵树。
    a                                              a
/   |   \                                      /   |   \
b   c   f                ===>                 f    c   b
  /   \                                          /   \
d       e                                      e       d
我们在输入输出一棵树的时候，常常会把树转换成对应的二叉树，而且对该二叉树中只有单个子结点的分支结点补充一个虚子结点“$”，形成“伪满二叉树”。

例如，对下图左边的树，得到下图右边的伪满二叉树
　　 a                                             a
/   |   \                                       /    \
b   c   f                ===>                  b      $
   / \                                        / \
  d   e                                      $   c
                                                / \
                                               d   f
                                              / \
                                             $   e
然后对这棵二叉树进行前序遍历，如果是内部结点则标记为0，如果是叶结点则标记为1，而且虚结点也输出。

现在我们将一棵树以“伪满二叉树”的形式输入，要求输出这棵树的镜面映射的宽度优先遍历序列。

输入
输入包含一棵树所形成的“伪满二叉树”的前序遍历。

第一行包含一个整数，表示结点的数目。

第二行包含所有结点。每个结点用两个字符表示，第一个字符表示结点的编号，第二个字符表示该结点为内部结点还是外部结点，内部结点为0，外部结点为1。结点之间用一个空格隔开。

数据保证所有结点的编号都为一个小写字母。

输出
输出包含这棵树的镜面映射的宽度优先遍历序列，只需要输出每个结点的编号，编号之间用一个空格隔开。

样例输入
9
a0 b0 $1 c0 d0 $1 e1 f1 $1

样例输出
a f c b e d

提示
样例输入输出对应着题目描述中的树。
*/
#define LOCAL // 本地调试宏定义，提交代码时注释掉此行
#define STL   // STL库，不用时注释掉此行
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#ifdef STL
#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#endif

using namespace std;
typedef long long ll;

class BinaryTreeNode {
public:
  char label_;
  int is_leaf_;
  BinaryTreeNode *lchild_;
  BinaryTreeNode *rchild_;
  BinaryTreeNode() : label_('$'), is_leaf_(0), lchild_(NULL), rchild_(NULL) {}
  BinaryTreeNode(char label, int is_leaf)
      : label_(label), is_leaf_(is_leaf), lchild_(NULL), rchild_(NULL) {}
};
void PreOrderBuildBinaryTree(BinaryTreeNode *root) {
  char label;
  int is_leaf;
  stack<BinaryTreeNode *> stack_binary_tree;
  stack_binary_tree.push(NULL); // 监视哨
  BinaryTreeNode *cur = root;
  BinaryTreeNode *temp;
  while (cur) {
    switch (cur->is_leaf_) {
    case 0: // 内部节点
      cin >> label >> is_leaf;
      temp = new BinaryTreeNode(label, is_leaf);
      if (!cur->lchild_) {
        stack_binary_tree.push(cur);
        cur->lchild_ = temp;
        cur = cur->lchild_;
      } else {
        cur->rchild_ = temp;
        cur = cur->rchild_;
      }
      break;
    default: // 叶节点
      cur = stack_binary_tree.top();
      stack_binary_tree.pop();
      break;
    }
  }
}
void MirrorBfsPrintTree(BinaryTreeNode *root) {
  // 思路见：https://blog.csdn.net/melanieecd/article/details/71122168
  stack<BinaryTreeNode *> bfs_stack;
  queue<BinaryTreeNode *> bfs_queue;
  BinaryTreeNode *cur = root;
  while (cur && cur->label_ != '$') {
    bfs_stack.push(cur);
    cur = cur->rchild_;
  }
  while (!bfs_stack.empty()) {
    cur = bfs_stack.top();
    cout << cur->label_ << " ";
    bfs_queue.push(cur);
    bfs_stack.pop();
  }
  while (!bfs_queue.empty()) {
    cur = bfs_queue.front();
    bfs_queue.pop();
    if (cur->lchild_)
      MirrorBfsPrintTree(cur->lchild_);
    
  }
}
void BfsPrint(BinaryTreeNode *root) {
  queue<BinaryTreeNode *> bfs_queue;
  bfs_queue.push(root);
  BinaryTreeNode *cur;
  while (!bfs_queue.empty()) {
    cur = bfs_queue.front();
    bfs_queue.pop();
    if (cur->label_ != '$')
      cout << cur->label_ << " ";
    else
      continue;
    if (cur->lchild_)
      bfs_queue.push(cur->lchild_);
    if (cur->rchild_)
      bfs_queue.push(cur->rchild_);
  }
}
int main() {
#ifdef LOCAL
  freopen(".debug/data.in", "r", stdin);
#endif

  int node_num;
  cin >> node_num;
  BinaryTreeNode *root;
  char r_label;
  int r_is_leaf;
  cin >> r_label >> r_is_leaf;
  root = new BinaryTreeNode(r_label, r_is_leaf);
  PreOrderBuildBinaryTree(root);
  MirrorBfsPrintTree(root);
#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
