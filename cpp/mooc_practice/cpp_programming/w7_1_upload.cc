
template <class T> class CArray3D {
  T m_, n_, k_;
  T ***arr_;
public:
  CArray3D(const T &ii, const T &jj, const T &kk)
      : m_(ii), n_(jj), k_(kk), arr_() {
    arr_ = new T **[m_];
    for (int i(0); i < m_; ++i) {
      arr_[i] = new T *[n_];
      for (int j(0); j < n_; ++j) {
        arr_[i][j] = new T[k_];
      }
    }
  }
  ~CArray3D() {
    for (int i(0); i < m_; ++i) {
      for (int j(0); j < n_; ++j) {
        delete[] arr_[i][j];
      }
      delete[] arr_[i];
    }
    delete arr_;
  }
  T **operator[](const T &ii) {
      return arr_[ii];
  }
};
