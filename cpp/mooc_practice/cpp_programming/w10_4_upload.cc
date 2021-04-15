
// 在此处补充你的代码
class CType {
  int num;

public:
  CType(int n = 0) : num(n) {}
  void setvalue(int n) { num = n; }
  CType operator++(int) {
    CType temp(*this);
    num *= num;
    return temp;
  }
  friend ostream &operator<<(ostream &os, const CType &obj);
};
ostream &operator<<(ostream &os, const CType &obj) {
    os << obj.num;
    return os;
}
