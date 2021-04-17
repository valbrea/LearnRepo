
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
// 方法2：Show是一个函数模板，Show()传入的是一个list<A>的迭代器，所以begin就是该类型的迭代器
// Print传入的是*begin，也就是一个A类型的对象的引用
// 不过用这种方法不太好，函数模板毫无必要，因为Print()只能传入A类型的对象引用，所以如果*It指向别的类型就会报错
// 而且也不能把Print()写成类模板，因为show()里面调用的Print()并没有传入实参，所以无法通过传入实参实例化出Print的一个模板类
class Print {
public:
  void operator()(A &a) { cout << a.get_name() << " ";}
};

template <class It>
void Show(It begin, It last, Print p) {
  for (; begin != last; ++begin)
    p(*begin);
}
