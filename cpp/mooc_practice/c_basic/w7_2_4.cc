/**********************************
 * #4 人民币支付
 * 从键盘输入一指定金额（以元为单位，如345），
 * 然后输出支付该金额的各种面额的人民币数量，
 * 显示100元，50元，20元，10元，5元，1元各多少张，
 * 要求尽量使用大面额的钞票。
 * ********************************/

#include <iostream>
using namespace std;
int main()
{
    // cout << "输出一个小于1000的整数" << endl;
    int money(0);
    cin >> money;
    // int num_100(0), num_50(0), num_20(0), num_10(0), num_5(0), num_1(0);
    int num[6] = {};
    int value[6] = {100, 50, 20, 10, 5, 1};
    for (int i = 0; i < 6; i++)
    {
        num[i] = money / value[i];
        money -= num[i] * value[i];
        cout << num[i] << endl;
    }
    // 笨逼方法
    /* num_100 = money / 100;
    money = money - num_100 * 100;
    num_50 = money / 50;
    money -= num_50 * 50;
    num_20 = money / 20;
    money -= num_20 * 20;
    num_10 = money / 10;
    money -= num_10 * 10;
    num_5 = money / 5;
    money -= num_5 * 5;
    num_1 = money;

    cout << num_100 << endl;
    cout << num_50 << endl;
    cout << num_20 << endl;
    cout << num_10 << endl;
    cout << num_5 << endl;
    cout << num_1 << endl; */

    return 0;
}