
    A(int n = 0) { val = n; }
    A & GetObj()
    {
        return *this;
    }
    // 第二种写法 返回int类型val的引用
    // int & GetObj()
    // {
    //     return val;
    // }