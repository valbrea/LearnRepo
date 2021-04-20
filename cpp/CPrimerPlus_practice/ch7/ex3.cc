#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int input; // 输入类型是数字！
    int sum_even(0), sum_odd(0), count_odd(0), count_even(0);
    while (cin >> input && input != 0) // 不要用input = cin.get() cin.get不会跳过空格，而且会把数字识别为ASCII码
    {
        if (input % 2 == 0)
        {
            sum_even += input;
            ++count_even;
        }
        else
        {
            sum_odd += input;
            ++count_odd;
        }
    }
    cout << "number of even: " << count_even << endl;
    if (count_even != 0)
        cout << "average of even: " << (double)sum_even / count_even << endl; // 均值是个double类型
    cout << "numbter of odd: " << count_odd << endl;
    if (count_odd != 0)
        cout << "average of odd: " << (double)sum_odd / count_odd << endl;

    return 0;
}
