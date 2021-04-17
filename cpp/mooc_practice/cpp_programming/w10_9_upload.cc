// 在此处补充你的代码
class A {
protected:
  int k_;

public:
  A(int k) : k_(k) {}
  virtual void PrintNum() { cout << "A " << k_ << endl; }
  friend class Comp;
};
class B : public A {
public:
  B(int k) : A(k) {}
  virtual void PrintNum() { cout << "B " << k_ << endl; }
  friend class Comp;
};
class Comp {
public:
  bool operator()(A *a, A *b) { return a->k_ < b->k_; }
};
void Print(A *a) { a->PrintNum(); }

