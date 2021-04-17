
// 在此处补充你的代码
bool operator<(const A &a1, const A &a2) {
  return a1.get_size() < a2.get_size();
}

template <class T> class MyLarge {
public:
  bool operator()(const T &a1, const T &a2) {
    return a1.get_name().at(0) < a2.get_name().at(0);
  }
};
// 方法1： 是直接声明It是list<A>的迭代器，传入Print()的也是一个迭代器
// 缺点是It不能变
typedef list<A>::iterator It;
class Print {
public:
  void operator()(It &begin) { cout << begin->get_name() << " ";}
};
void Show(It begin, It last, Print p) {
  for (; begin != last; ++begin) {
    p(begin);
  }
}
