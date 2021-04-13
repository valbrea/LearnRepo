
// 在此处补充你的代码
template <class T> class CMyistream_iterator {
  T data_;
  istream &is_;

public:
  CMyistream_iterator(istream &is) : data_(), is_(is) {
    is_ >> data_;
  }
  T operator*() const { return data_; }
  T operator++(int) {
    is_ >> data_;
    return data_;
  }
};
