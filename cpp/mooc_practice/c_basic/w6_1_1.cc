// 细菌繁殖

#include <iostream>
using namespace std;
/*
 * 输入有多行，第一行为整数n（n≤100），表示有n个培养皿。
 * 其余n行，每行有三个整数，分别代表培养皿编号，试验前细菌数量，试验后细菌数量。假设试验没有误差。
 */
int main() 
{
    int total;
    int id[100];
    double rate[100]; //reproduction rate
    
    // cout << "请输入培养皿总数" << endl;
    cin >> total;
    // cout << "请输入培养皿编号、培养前细菌数量、培养后细菌数量。" << endl;
    for (int i(0); i < total; ++i)
    {
        int initial, final;
        cin >> id[i] >> initial >> final;
        rate[i] = (double)final / initial;
    }

    //对整个细菌排序
    for (int i(0); i < total; ++i)
    {
        for (int j(0); j < total - i - 1; ++j)
        {
            if (rate[j + 1] > rate [j])
            {
                int tmpId = id[j];
                id[j] = id[j + 1];
                id[j + 1] = tmpId;
                double tmpRate = rate[j];
                rate[j] = rate[j + 1];
                rate[j + 1] = tmpRate;
            }
        }
    }

    // 记录最大的差
    double maxDiff(0);
    //和最大差的下标
    int maxDiffIndex(0);
    for (int i(0); i < total - 1; ++i)
    {
        double diff = rate[i] - rate[i + 1];
        if (maxDiff < diff)
        {
            maxDiff = diff;
            maxDiffIndex = i;
        }
    }

    //输出繁殖率较大的那组细菌
    // cout << "繁殖率较高的培养皿数量为：";
    cout << maxDiffIndex + 1 << endl;
    // cout << "该组细菌培养皿编号按繁殖率从大到小排列为：";
    for (int i(maxDiffIndex); i >= 0; --i)
    {
        cout << id[i] << endl;
    }

    // 输出繁殖率较小的那组细菌
    // cout << "繁殖率较低的培养皿数量为：";
    cout << total - 1 - maxDiffIndex << endl;
    // cout << "该组细菌培养皿编号按繁殖率从小到大排列为：";
    for (int i(total - 1); i >= maxDiffIndex + 1; --i)
    {
        cout << id[i] << endl;
    }
    cout << endl;

    return 0;
}