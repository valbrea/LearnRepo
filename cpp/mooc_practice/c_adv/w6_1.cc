/*
编程题＃1：分配病房
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
某个科室的病房分为重症和普通，只有当病人的疾病严重程度超过了入住重症病房的最低严重值，才可以安排入住重症病房。 

现在要求设计一个程序，给病人安排好病房。疾病的严重程度用0到10来表示，0表示小毛病，10表示非常严重。

输入
第一行输入病人的个数m(m < 50)，以及安排住入重症病房的最低严重值a

紧接着m行，每行表示病人编号（三个位，用0补齐）及其疾病的严重程度（浮点数，1位小数）。

每个病人的疾病严重程度都不一样。

输出
要求按照病人的严重程度输出住在重症病房里的病人的编号

注意：
如果当前所有病人的严重程度并不满足住在重症病房里，则输出“None.”（不包括引号）

样例输入
10 7.55
006 6.5
005 8.0
004 3.5
009 8.5
011 7.0
043 9.5
003 5.0
103 6.0
112 4.0
118 9.0

样例输出
043 9.5
118 9.0
009 8.5
005 8.0
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int m(0), number[50] = {0}, out_number[50] = {0}, *pnum = out_number, out_qty(0);
    double a(0), critical_value[50], out_value[50], *pvalue = out_value;

    cin >> m >> a;
    for (int i(0); i < m; ++i) // 先筛选出症状严重的患者
    {
        cin >> number[i] >> critical_value[i];
        if (critical_value[i] >= a)
        {
            *pnum = number[i];
            ++pnum;
            *pvalue = critical_value[i];
            ++pvalue;
            ++out_qty;
        }
    }
    // cout << GetArrLength(out_number) << ' ' << GetArrLength(out_value) << ' '  << GetArrLength(number) << ' '  << GetArrLength(critical_value) << endl;
    if (out_qty == 0) // 如果没有严重患者就输出没有
        cout << "None." << endl;
    else
    {
        for (int i(0); i < out_qty - 1; ++i) // 冒泡排序所有病人，重症优先
            for (int j(0); j < out_qty - 1 - i; ++j)
            {
                if (out_value[j] < out_value[j + 1])
                {
                    int temp = out_number[j];
                    out_number[j] = out_number[j + 1];
                    out_number[j + 1] = temp;
                    double temp1 = out_value[j];
                    out_value[j] = out_value[j + 1];
                    out_value[j + 1] = temp1;
                }
            }

        for (int i(0); i < out_qty; ++i) // 输出所有病例编号和危急值
            cout << setw(3) << setfill('0') << out_number[i] << ' ' << fixed << setprecision(1) << out_value[i] << endl;
    }

    return 0;
}
