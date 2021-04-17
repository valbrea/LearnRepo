
// 在此处补充你的代码
class A {
public:
  static int count;
  A() { ++count; }
  A(int n) { ++count; }
  virtual ~A() { cout << "A::destructor" << endl; }
  // 最后count少了1，唯一区别就是用了delete，所以delete被重载了
  void operator delete(void *pa) { --count; } // delete的参数必须是void*类型
};
class B : public A {
public:
  B(int n) {}
  ~B() { cout << "B::destructor" << endl; }
};

