/* 编程题＃4：魔兽世界之一：备战
描述:
魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。
红司令部，City 1，City 2，……，City n，蓝司令部
两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf
五种。每种武士都有编号、生命值、攻击力这三种属性。
双方的武士编号都是从1开始计算。红方制造出来的第n个武士，编号就是n。同样，蓝方制造出来的第n个武士，编号也是n。
武士在刚降生的时候有一个生命值。
在每个整点，双方的司令部中各有一个武士降生。
红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。
蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。
制造武士需要生命元。
制造一个初始生命值为m的武士，司令部中的生命元就要减少m个。
如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司令部停止制造武士。
给定一个时间，和双方司令部的初始生命元数目，要求你将从0点0分开始到双方司令部停止制造武士为止的所有事件按顺序输出。
一共有两种事件，其对应的输出样例如下：
1) 武士降生
输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter
表示在4点整，编号为5的蓝魔lion武士降生，它降生时生命值为5，降生后蓝魔司令部里共有2个lion武士。（为简单起见，不考虑单词的复数形式）注意，每制造出一个新的武士，都要输出此时司令部里共有多少个该种武士。
2) 司令部停止制造武士
输出样例： 010 red headquarter stops making warriors
表示在10点整，红方司令部停止制造武士
输出事件时：
首先按时间顺序输出；
同一时间发生的事件，先输出红司令部的，再输出蓝司令部的。
输入
第一行是一个整数，代表测试数据组数。
每组测试数据共两行。
第一行：一个整数M。其含义为， 每个司令部一开始都有M个生命元( 1 <= M <= 10000)。
第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf
的初始生命值。它们都大于0小于等于10000。
输出
对每组测试数据，要求输出从0时0分开始，到双方司令部都停止制造武士为止的所有事件。
对每组测试数据，首先输出"Case:n" n是测试数据的编号，从1开始 。
接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。
样例输入
1
20
3 4 5 6 7
样例输出
Case:1
000 red iceman 1 born with strength 5,1 iceman in red headquarter
000 blue lion 1 born with strength 6,1 lion in blue headquarter
001 red lion 2 born with strength 6,1 lion in red headquarter
001 blue dragon 2 born with strength 3,1 dragon in blue headquarter
002 red wolf 3 born with strength 7,1 wolf in red headquarter
002 blue ninja 3 born with strength 4,1 ninja in blue headquarter
003 red headquarter stops making warriors
003 blue iceman 4 born with strength 5,1 iceman in blue headquarter
004 blue headquarter stops making warriors
*/
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
// *************类定义**************
class Camp {
private:
  string camp_name_;                // 司令部名字
  int worrior_number_,              // 记录生产编号
      qty_[5],                      // 记录每种武士的数量
      camp_strength_;               // 当前阵营的生命值
  string worrior_type_in_order_[5]; // 两个阵营按顺序记录的出兵名称
  int strength_in_order_[5], // 两个阵营按顺序记录的武士的生命值
      atk_in_order_[5],      // 两个阵营按顺序记录的武士的攻击力
      index_;                // 当前的出兵位置
public:
  static int min_strength_,             // 记录最少需要消耗生命的量
      time_,                            // 武士出兵时间
      camp_strength_per_,               // 输入的每个司令部的生命值
      strength_per_[5];                 // 每种武士的生命值
  static const int red_seq_[5],         // 红方武士制造序列
      blue_seq_[5];                     // 蓝方武士制造序列
  static const string worrior_type_[5]; //武士类型
  // 构造函数声明
  Camp(const string camp_name);
  int BuildWarriors(); // 给当前阵营制造武士
};
// *************构造函数定义**********
Camp::Camp(const string camp_name)
    // 注意：数组在构造函数列表初始化中不能加参数，应该在函数作用域中完成。
    // 例如：构造函数() : 数组名() {}，注意后面这个括号不能加0或其他数值
    // gnu++的标准好像允许在数组名()中间加东西，但是c++标准好像不行
    : camp_name_(camp_name), worrior_number_(0), qty_(),
      camp_strength_(camp_strength_per_), worrior_type_in_order_(),
      strength_in_order_(), atk_in_order_(), index_(0) {
  const int *seq;
  if (camp_name == "red") {
    seq = red_seq_;
  } else if (camp_name == "blue") {
    seq = blue_seq_;
  } else {
    cout << "camp_name error!" << endl;
  }
  min_strength_ = strength_per_[0]; // 最小值先设定一个
  for (int i(0); i < 5; ++i) {
    worrior_type_in_order_[i] = worrior_type_[seq[i]];
    strength_in_order_[i] = strength_per_[seq[i]];
    if (strength_in_order_[i] < min_strength_)
      min_strength_ = strength_in_order_[i];
  }
}
// **************主函数**************
int Camp::time_ = 0, Camp::min_strength_ = 0,
    Camp::camp_strength_per_(0), Camp::strength_per_[5] = {0};
const int Camp::red_seq_[5] = {2, 3, 4, 1, 0}, // 红方武士制造序列
    Camp::blue_seq_[5] = {3, 0, 1, 2, 4};      // 蓝方武士制造序列
const string Camp::worrior_type_[5] = {"dragon", "ninja", "iceman", "lion",
                                       "wolf"};
// 对于静态成员变量，必须在定义该类的文件中进行一次声明或初始化，否则编译能通过，链接无法通过！！！
// int Camp::time_ = 0, Camp::min_strength_ = 0;
// 对于静态成员变量，必须在定义该类的文件中进行一次声明或初始化，否则编译能通过，链接无法通过！！！
// int Camp::time_ = 0, Camp::min_strength_ = 0;
int main() {
  int n(0);
  cin >> n; // 输入测试组数
  cin.ignore();
  for (int test(0); test < n; ++test) {
    // 输入各组数据
    cin >> Camp::camp_strength_per_;
    for (int i(0); i < 5; ++i) {
      cin >> Camp::strength_per_[i];
    }
    cin.ignore();
    cout << "Case:" << test + 1 << endl;
    // 初始化两个阵营
    Camp red("red");
    Camp blue("blue");

    // 分别制造武士
    int r_end(0), b_end(0);
    while (r_end == 0 || b_end == 0) {
      if (r_end == 0)
        r_end = red.BuildWarriors();
      if (b_end == 0)
        b_end = blue.BuildWarriors();
      ++Camp::time_; // time是从000开始的，所以先在000生产，然后再+1
    }
  }

  return 0;
}
// ********生产武士函数*************
int Camp::BuildWarriors() {
  if (Camp::camp_strength_ < Camp::min_strength_) { // 2) 司令部停止制造武士
    cout << setw(3) << setfill('0') << Camp::time_ << ' ' << camp_name_
         << " headquarter stops making warriors" << endl;
    return 2; // 返回2，表示当前这个阵营出兵完毕
  } else {
    // 如果现有阵营生命值小于当前生产序列武士所需生命值，进入循环直到寻找到能生产的武士
    while (Camp::camp_strength_ < strength_in_order_[index_]) {
      if (index_ != 4) // 如果不是最后一种武士，就试图制造下一种
        ++index_;
      else
        index_ = 0; // 如果是最后一种武士，就回到第一种武士
    }
    ++worrior_number_; // 序号初始化为0，每生产一个+1，生产第一个就是1号
    Camp::camp_strength_ -= strength_in_order_[index_]; // 阵营生命值 - 生产消耗
    ++qty_[index_]; // 当前种类的武士数量+1

    // 输出
    cout << setw(3) << setfill('0') << Camp::time_ << ' ' << camp_name_ << ' '
         << worrior_type_in_order_[index_] << ' ' << worrior_number_
         << " born with strength " << strength_in_order_[index_] << ','
         << qty_[index_] << ' ' << worrior_type_in_order_[index_] << " in "
         << camp_name_ << " headquarter" << endl;
    if (index_ != 4)
      ++index_; // 制造下一种武士
    else
      index_ = 0;
    return 0; // 返回0 继续循环
  }
}