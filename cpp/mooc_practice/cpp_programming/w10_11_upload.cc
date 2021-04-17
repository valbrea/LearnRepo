
// 在此处补充你的代码
template <class T> class NameGreater {
public:
  bool operator()(const T &x, const T &y) { return x > y; }
};

template <class T1, class T2, class Pred = NameGreater<T1> > class MyMultimap {
public:
  multimap<T1, T2, Pred> mm_;
  typedef typename multimap<T1, T2>::iterator iterator;
  iterator insert(pair<T1, T2> pair) { return mm_.insert(pair); }
  iterator begin() { return mm_.begin(); }
  iterator end() { return mm_.end(); }
  iterator find(T1 t1) { return mm_.find(t1); }
  void Set(T1 t1, T2 t2) {
    iterator low, up;
    low = mm_.lower_bound(t1);
    up = mm_.upper_bound(t1);
    for (; low != up; ++low)
      low->second = t2;
  }
  void clear() { mm_.clear(); }
};
template <class T1, class T2>
ostream &operator<<(ostream &os, pair<T1, T2> &pair) {
  os << "(" << pair.first << "," << pair.second << ")";
  return os;
}
