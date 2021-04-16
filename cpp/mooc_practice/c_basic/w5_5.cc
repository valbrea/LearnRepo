// 数组逆序重放
// 将一个数组中的值按逆序重新存放。例如，原来的顺序为8,6,5,4,1。要求改为1,4,5,6,8。

#include <iostream>
using namespace std;

int main()
{
    int length;
    // 输入为两行：第一行数组中元素的个数n（1<n<100)，第二行是n个整数，每两个整数之间用空格分隔。
    // cout << "Enter the length of array." << endl;
    cin >> length;

    int array[100];
    // cout << "Enter the elements of array." << endl;
    for (int i(0); i < length; ++i)
    {
        cin >> array[i];
    }
    while (length--) //常用的倒序计数循环，等价于while(n-->0)
    {
        cout << array[length];
        if (length > 0)
        {
            cout << " "; //如果不是最后一个数那么就要用空格分隔开
        }
    }
    cout << endl;
    
    return 0;
}