/*
编程题＃4：寻找平面上的极大点
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个平面上，如果有两个点(x,y),(a,b),如果说(x,y)支配了(a,b)，这是指x>=a,y>=b;
用图形来看就是(a,b)坐落在以(x,y)为右上角的一个无限的区域内。
给定n个点的集合，一定存在若干个点，它们不会被集合中的任何一点所支配，这些点叫做极大值点。
编程找出所有的极大点，按照x坐标由小到大，输出极大点的坐标。
本题规定：n不超过100，并且不考虑点的坐标为负数的情况。

输入
输入包括两行，第一行是正整数n，表示是点数，第二行包含n个点的坐标，坐标值都是整数，坐标范围从0到100，输入数据中不存在坐标相同的点。

输出
按x轴坐标最小到大的顺序输出所有极大点。

输出格式为:(x1,y1),(x2,y2),...(xk,yk)

注意：输出的每个点之间有","分隔,最后一个点之后没有",",少输出和多输出都会被判错

样例输入
5
1 2 2 2 3 1 2 3 1 4

样例输出
(1,4),(2,3),(3,1)
*/
#include <iostream>
using namespace std;
int main()
{
    int n(0), coordinates[101][2];
    cin >> n;
    for (int i(0); i < n; ++i)
        cin >> coordinates[i][0] >> coordinates[i][1]; // 输入
    // 按x坐标从小到大排序
    for (int i(0); i < n - 1; ++i)
        for (int j(0); j < n - 1 - i; ++j)
        {
            if (coordinates[j][0] > coordinates[j + 1][0])
            {
                int temp_x = coordinates[j][0];
                coordinates[j][0] = coordinates[j + 1][0];
                coordinates[j + 1][0] = temp_x;
                int temp_y = coordinates[j][1];
                coordinates[j][1] = coordinates[j + 1][1];
                coordinates[j + 1][1] = temp_y;
            }
        }
    int out_coords[101][2], (*p)[2] = out_coords, count(0);
    for (int i(0); i < n; ++i)
    {
        int a = coordinates[i][0], b = coordinates[i][1];
        bool flag(0);
        for (int j(i + 1); j < n; ++j)
        {
            int x = coordinates[j][0], y = coordinates[j][1];
            if (x >= a && y >= b)
            flag = 1;
        }
        if (flag == 0)
        {
            (*p)[0] = a; // 必须要把输出记录再统一输出，因为循环的时候输出无法保证最后不会多输出一个逗号。
            (*p)[1] = b;
            ++p;
            ++count;
        }
    }
    for (p = out_coords; count > 1; --count, ++p)
        cout << '(' << (*p)[0] << ","<< (*p)[1] << "),";

    cout << '(' << (*p)[0] << "," << (*p)[1] << ")"<< endl; // 要分开输出， 防止最后多输出一个逗号


    return 0;
}