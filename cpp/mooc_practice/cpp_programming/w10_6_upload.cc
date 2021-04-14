
// 在此处补充你的代码
class MyString : public string {
public:
  MyString(const string &str = "");
  MyString(const char *c);
  // MyString(const MyString&);
  MyString operator()(const int &a, const int &b);
  // friend ostream &operator<<(ostream &os, const MyString &str);
};
MyString::MyString(const string &str) : string(str) {}
MyString::MyString(const char *c) : string(c) {}
MyString MyString::operator()(const int &start, const int &len) {
  string::substr(); // 调用基类的函数
  return this->substr(start, len);
} 
