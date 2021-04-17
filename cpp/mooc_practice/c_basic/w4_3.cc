// 奇偶排序（二）
// 输入十个整数，将十个整数按升序排列输出，并且奇数在前，偶数在后。

#include <iostream>
using namespace std;

int main()
{
    int a[10];

    // cout << "please enter 10 integers." << endl;
    for (int i(0); i < 10; ++i)
    {
        cin >> a[i];
    }
    // 冒泡
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 1; j < 10 - i; ++j)
        {
            bool left_is_even = a[j - 1] % 2 == 0;
            bool right_is_even = a[j] % 2 == 0;
            if ((left_is_even && !right_is_even) ||
                (left_is_even == right_is_even && a[j - 1] > a[j]))
            {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }
    // 输出结果
    for (int i{0}; i < 10; ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}