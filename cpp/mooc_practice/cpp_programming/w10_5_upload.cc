
// 在此处补充你的代码
class CMy_add {
    public:
    int &sum_; //只有引用my_sum才能直接修改它
    CMy_add(int &my_sum): sum_(my_sum) {}
    void operator()(int i) {
        sum_ += (i & 7); //位运算：保留低3位，其余置0
    }
};
