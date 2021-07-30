/*
编程题＃2： 文件结构“图”
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在计算机上看到文件系统的结构通常很有用。Microsoft
Windows上面的"explorer"程序就是这样的一个例子。
但是在有图形界面之前，没有图形化的表示方法的，那时候最好的方式是把目录和文件的结构显示成一个"图"的样子，
而且使用缩排的形式来表示目录的结构。
比如：
ROOT
|         dir1
|         |         file1
|         |         file2
|         |         file3
|         dir2
|         dir3
|         |         file1
file1
file2
这个图说明：ROOT目录包括两个文件和三个子目录。第一个子目录包含3个文件，第二个子目录是空的，第三个子目录包含一个文件。

输入
你的任务是写一个程序读取一些测试数据。每组测试数据表示一个计算机的文件结构。每组测试数据以'*'结尾，而
所有合理的输入数据以'#'结尾。一组测试数据包括一些文件和目录的名字（虽然在输入中我们没有给出，但是我们
总假设ROOT目录是最外层的目录）。在输入中,以']'表示一个目录的内容的结束。目录名字的第一个字母是'd'，文件
名字的第一个字母是'f'。文件名可能有扩展名也可能没有（比如fmyfile.dat和fmyfile）。文件和目录的名字中都
不包括空格。

输出
在显示一个目录中内容的时候，先显示其中的子目录（如果有的话），然后再显示文件（如果有的话）。文件要求
按照名字的字母表的顺序显示（目录不用按照名字的字母表顺序显示，只需要按照目录出现的先后显示）。对每一
组测试数据，我们要先输出"DATA SET
x:"，这里x是测试数据的编号（从1开始）。在两组测试数据之间要输出一个 空行来隔开。

你需要注意的是，我们使用一个'|'和5个空格来表示出缩排的层次。

样例输入
file1
file2
dir3
dir2
file1
file2
]
]
file4
dir1
]
file3
*
file2
file1
*
#
样例输出
DATA SET 1:
ROOT
|        dir3
|        |        dir2
|        |        file1
|        |        file2
|        dir1
file1
file2
file3
file4

DATA SET 2:
ROOT
file1
file2
*/
#define STL // STL库，不用时注释掉此行
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

#define LOCAL_DEBUG // 本地调试宏定义，提交代码时注释掉此行
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll INF_LL = 0x3f3f3f3f3f3f3f3f;

string str;
string prefix; // 前缀 "|        "
void Directory(string root) {
  set<string> files;
  while (str != "*") {
    getline(cin, str);
    switch (str[0]) {
    case 'd':
      prefix += "|        ";
      Directory(str);
      break;
    case 'f':
      files.insert(str);
      break;
    case ']':
      cout << prefix << root << endl;
      for (set<string>::iterator ii = files.begin(); ii != files.end(); ++ii) {
        cout << prefix << *ii << endl;
      }
      prefix -= "|        ";
      return;
      break;
    case '*':
      cout << prefix << root << endl;
      for (set<string>::iterator ii = files.begin(); ii != files.end(); ++ii) {
        cout << prefix << *ii << endl;
      }
      prefix -= "|        ";
      return;
      break;
    default:
      break;
    }
  }
}
int main() {
#ifdef LOCAL_DEBUG
  freopen("/home/asuka/linuxcodes/cpp/mooc_practice/algorithm/.debug/w3_2.in",
          "r", stdin);
#endif

  int data_num(1);
  while (str != "#") {
    Directory("ROOT");
  }

#ifdef LOCAL_DEBUG
  cout << endl
       << "-------------------------------------------------" << endl
       << "Runtime: " << 1000.0 * (double)clock() / CLOCKS_PER_SEC << "ms\n";
#endif
  return 0;
}
