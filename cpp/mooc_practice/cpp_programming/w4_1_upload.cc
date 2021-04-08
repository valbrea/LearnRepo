
  Complex &operator=(const string &s) {
    int pos = s.find("+", 0);
    string sTmp = s.substr(0, pos);
    r = atof(sTmp.c_str());
    sTmp = s.substr(pos + 1, s.length() - pos - 2);
    i = atof(sTmp.c_str());
    return *this; // 返回值不要写const Complex & 不然返回的值就和a不同类型了
  }
