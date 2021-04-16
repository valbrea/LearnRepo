// 奇偶排序（一）
// 输入十个整数，将十个整数按升序排列输出，并且奇数在前，偶数在后。

#include <iostream>
using namespace std;

int main()
{
    int a[10];

    // cout << "please enter ten integers." << endl;
    for (int i(0); i < 10; ++i)
    {
        cin >> a[i];
    }
    // 把奇数放左侧，偶数放右侧
    int left(0), right(9);
    while (left <= right)
    {
        bool left_is_odd = a[left] % 2 == 1;
        bool right_is_even = a[right] % 2 == 0;

        if (left_is_odd)
        {
            left++;
        }
        else if (right_is_even)
        {
            right--;
        }
        else if (!left_is_odd && !right_is_even)
        {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
        }
    }
    //对左侧冒泡
    int start(0), end(left);
    for (int i{start}; i < end - 1; ++i)
    {
        for (int j{start + 1}; j < start + end - i; j++)
        {
            if (a[j - 1] > a[j])
            {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }
    //对右侧冒泡
    start = left, end = 10;
    for (int i{start}; i < end - 1; ++i)
    {
        for (int j{start + 1}; j < start + end - i; j++)
        {
            if (a[j - 1] > a[j])
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