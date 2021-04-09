class Array2 {
private:
  int **ptr_;
  int m_, n_;

public:
  Array2(const int &m = 0, const int &n = 0) : m_(m), n_(n) {
    if (m == 0 || n == 0)
      ptr_ = NULL;
    else {
      ptr_ = new int *[m];
      for (int i(0); i < m; ++i)
        ptr_[i] = new int[n];
    }
  }
  ~Array2() {
    if (ptr_) {

      for (int i(0); i < m_; ++i)
        delete[] ptr_[i];
      delete[] ptr_;
    }
  }
  int *operator[](const int &i) { return ptr_[i]; }
  int &operator()(const int &i, const int &j) { return ptr_[i][j]; }
  Array2 &operator=(const Array2 &arr) {
    if (ptr_ == arr.ptr_)
      return *this;
    if (arr.ptr_ == NULL) {
      if (ptr_)
        delete[] ptr_;
      ptr_ = NULL;
      m_ = 0;
      n_ = 0;
      return *this;
    }
    if (m_ < arr.m_ || n_ < arr.n_) {
      if (ptr_)
        delete[] ptr_;
      ptr_ = new int *[arr.m_];
      for (int i(0); i < arr.m_; ++i)
        ptr_[i] = new int[arr.n_];
    }
    for (int i(0); i < arr.m_; ++i)
      for (int j(0); j < arr.n_; ++j)
        ptr_[i][j] = arr.ptr_[i][j];
    m_ = arr.m_;
    n_ = arr.n_;
    return *this;
  }
};