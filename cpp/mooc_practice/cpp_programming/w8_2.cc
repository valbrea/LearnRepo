/*
编程题＃1 List
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 4000ms 内存限制: 65536kB

描述
写一个程序完成以下命令：

new id ——新建一个指定编号为id的序列(id<10000)

add id num——向编号为id的序列加入整数num

merge id1 id2——合并序列id1和id2中的数，并将id2清空

unique id——去掉序列id中重复的元素

out id ——从小到大输出编号为id的序列中的元素，以空格隔开

输入
第一行一个数n，表示有多少个命令( n＜＝２０００００)。以后n行每行一个命令。

输出
按题目要求输出。
*/
#include <iostream>
#include <queue>
#include <vector>
#include <list>
using namespace std;

int main() {
  int n(0);
  cin >> n;
  cin.ignore();
  vector<list<int> > sequeces;
  while (n > 0) {
    string cmd;
    getline(cin, cmd);
    queue<string> argv;
    for (int begin(0), blank(0); blank != cmd.npos; begin = blank + 1) {
      blank = cmd.find(' ', begin);
      if (blank != cmd.npos) { // 如果没到末尾位置
        argv.push(cmd.substr(begin, blank - begin));
        begin = blank + 1; // 记录下一个命令的开始位置
      } else               // 如果是末尾位置
        argv.push(cmd.substr(begin, cmd.size() - begin));
    }
    if (argv.front() == "new") {
      argv.pop();
      int id;
      id = stoi(argv.front());
      sequeces.push_back(list<int>()); // 往序列的第id个位置加入一个新list
    }
    else if (argv.front() == "add") {
      argv.pop();
      int id, num;
      id = stoi(argv.front());
      argv.pop();
      num = stoi(argv.front());
      sequeces[id - 1].push_back(num);
    }
    else if (argv.front() == "merge") {
      argv.pop();
      int id1, id2;
      id1 = stoi(argv.front());
      argv.pop();
      id2 = stoi(argv.front());
      sequeces[id1 - 1].merge(sequeces[id2 - 1]);
    }
    else if (argv.front() == "unique") {
      argv.pop();
      int id;
      id = stoi(argv.front());
      sequeces[id - 1].sort();
      sequeces[id - 1].unique(); // 要先排序再unique，否则删不干净，unique只会清除和前面元素重复的元素

    }
    else if (argv.front() == "out") {
      argv.pop();
      int id;
      id = stoi(argv.front());
      list<int>::iterator ii;
      sequeces[id - 1].sort();
      for(ii = sequeces[id - 1].begin(); ii != sequeces[id - 1].end(); ++ii)
        cout << *ii << " ";
      cout << endl;
    }
    else {}

    --n;
  }
  return 0;
}
