// 并查集
template <class T> class ParTreeNode {
private:
  T value_;
  ParTreeNode<T> *parent_;
  int count_;

public:
  ParTreeNode() : value_(0), parent_(NULL), count_(0) {}
  virtual ~ParTreeNode() {}
  T GetValue() { return value_; }
  void SetValue(const T &val) { value_ = val; }
  ParTreeNode<T> *GetParent() { return parent_; }
  void SetParent(ParTreeNode<T> *par) { parent_ = par; }
  int GetCount() { return count_; }
  void SetCount(const int count) { count_ = count; }
};
template <class T> class ParTree {
public:
  ParTreeNode<T> *array_;
  int size_;
  ParTreeNode<T> *Find(ParTreeNode<T> *node) const {
    // 查
    ParTreeNode<T> *pointer = node;
    while (pointer->GetParent() != NULL)
      pointer = pointer->GetParent();
    return pointer;
  }
  ParTreeNode<T> *FindPC(ParTreeNode<T> *node) const {
    // 路径压缩
    if (node->GetParent == NULL)
      return node;
    node->SetParent(FindPC(node->GetParent()));
    return node->GetParent();
  }
  ParTree(const int size) : array_(), size_(size), {
    array = new ParTreeNode<T>[size];
  }
  virtual ~ParTree() {}
  void Union(int i, int j) {
    // 并，按秩合并
    ParTreeNode<T> *pointeri = Find(&array_[i]);
    ParTreeNode<T> *pointerj = Find(&array_[j]);
    if (pointeri != pointerj) {
      if (pointeri->GetCount >= pointerj->GetCount()) {
        pointerj->SetParent(pointeri);
        pointeri.SetCount(pointeri->GetCount() + pointerj->GetCount());
      } else {
        pointeri->SetParent(pointerj);
        pointerj->SetCount(pointerj->GetCount() + pointerj->GetCount());
      }
    }
  }
  bool Different(int i, int j) {
    ParTreeNode<T> *pointeri = Find(&array_[i]);
    ParTreeNode<T> *pointerj = Find(&array_[j]);
    return pointeri != pointerj;
    }
};