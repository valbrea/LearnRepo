/*
1. 森林的带度数层次序列存储
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
对于树和森林等非线性结构，我们往往需要将其序列化以便存储。有一种树的存储方式称为带度数的层次序列。我们可以通过层次遍历的方式将森林序列转化为多个带度数的层次序列。

例如对于以下森林：


两棵树的层次遍历序列分别为：C E F G K H J / D X I

每个结点对应的度数为：3 3 0 0 0 0 0 / 2 0 0

我们将以上序列存储起来，就可以在以后的应用中恢复这个森林。在存储中，我们可以将第一棵树表示为C
3 E 3 F 0 G 0 K 0 H 0 J 0，第二棵树表示为D 2 X 0 I 0。

现在有一些通过带度数的层次遍历序列存储的森林数据，为了能够对这些数据进行进一步处理，首先需要恢复他们。

输入
输入数据的第一行包括一个正整数n，表示森林中非空的树的数目。

随后的 n 行，每行给出一棵树的带度数的层次序列。

树的节点名称为A-Z的单个大写字母。

输出
输出包括一行，输出对应森林的后根遍历序列。

样例输入
2
C 3 E 3 F 0 G 0 K 0 H 0 J 0
D 2 X 0 I 0

样例输出
K H J E F G C X I D

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
class TreeNode {
public:
  char label_;
  int degree_;
  TreeNode *lchild_;
  TreeNode *rchild_;
  TreeNode() : label_(), degree_(0), lchild_(NULL), rchild_(NULL) {}
  TreeNode(char label, int degree)
      : label_(label), degree_(degree), lchild_(NULL), rchild_(NULL) {}
};
void BfsBuildTree(queue<TreeNode *> *queue_tree) {
  char label;
  int degree;
  while (!queue_tree->empty()) {
    TreeNode *cur = queue_tree->front();
    queue_tree->pop();
    TreeNode *parent = cur;
    TreeNode *temp = NULL;
    for (int i = 0; i < parent->degree_; ++i) {
      cin >> label >> degree;
      temp = new TreeNode(label, degree);
      if (degree != 0)
        queue_tree->push(temp);
      if (i == 0) {
        cur->lchild_ = temp;
        cur = cur->lchild_;
      } else {
        cur->rchild_ = temp;
        cur = cur->rchild_;
      }
    }
  }
}
void PostRootOrder(TreeNode *root) {
  while (root) {
    PostRootOrder(root->lchild_);
    cout << root->label_ << " ";
    root = root->rchild_;
  }
}
int main() {
#ifdef LOCAL
  freopen(".debug/data.in", "r", stdin);
#endif

  int n;
  cin >> n;
  cin.ignore();
  char r_label;
  int r_degree;
  TreeNode *root;
  queue<TreeNode *> *queue_tree = new queue<TreeNode *>[2];
  while (n--) {
    cin >> r_label >> r_degree;
    root = new TreeNode(r_label, r_degree);
    queue_tree->push(root);
    BfsBuildTree(queue_tree);
    PostRootOrder(root);
    ++queue_tree;
  }

#ifdef LOCAL
  cout << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif

  return 0;
}
