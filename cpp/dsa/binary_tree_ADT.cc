template <typename T> class BinaryTreeNode {
  friend class BirnaryTree<T>;

private:
  T data_;

public:
  BinaryTreeNode();
  BinaryTreeNode(const T &data);
  BinaryTreeNode(const T &data, BinaryTreeNode<T> *lc, BinaryTreeNode<T> *rc);
  T ShowData() const;
  BinaryTreeNode<T> *LeftChild() const;
  BinaryTreeNode<T> *RightChild() const;
  void SetLeftChild(BinaryTreeNode<T> *);
  void SetRightChild(BinaryTreeNode<T> *);
  void SetData(const T &data);
  bool IsLeaf() const;
  BinaryTreeNode<T> &operator=(const BinaryTreeNode<T> &Node);
};