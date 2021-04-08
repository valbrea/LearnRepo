
  // 在此处补充你的代码
  MyInt &operator-(const int &n) {
      nVal -= n;
      return *this;
  }
