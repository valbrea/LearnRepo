/*
编程题＃2：字符串中次数第2多的字母
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
输入一串长度不超过500个符号的字符串，输出在串中出现第2多的英语字母(大小写字母认为相同)和次数（如果串中有其它符号，则忽略不考虑）。如果有多个字母的次数都是第2多，则按串中字母出现的顺序输出第1个。 

例 ab&dcAab&c9defgb 

这里，a 和 b都出现3次，c和d都出现2次，e、f 和 g 各出现1次，其中的符号&和9均忽略不考虑。因此，出现第2多的应该是 c 和 d，但是 d 开始出现的位置在 c 的前面，因此，输出为 

D+d:2 

(假定在字符串中，次数第2多的字母总存在)

输入
一个字符串

输出
大写字母+小写字母:个数

样例输入
ab&dcAab&c9defgb

样例输出
D+d:2
*/
#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;
struct data
{
    char letter;
    int count;
};
int main()
{
    char arr[500] = {0};
    cin >> arr; // arr记录输入字符串
    // 统计所有字母出现频次
    data stats[26] = {0}; // stats用来统计每个字母出现的次数
    for (int i(0); i < 26; ++i)
    {
        stats[i].letter = 'A' + i;
    }
    for (int i(0); i < strlen(arr); ++i)
    {
        if (isalpha(arr[i])) // 如果是字母
        {
            arr[i] = toupper(arr[i]); // 先转换成大写
            for (int j(0); j < 26; ++j) // 找到stats里面的对应字母，次数+1
            {
                if (stats[j].letter == arr[i]) 
                    ++stats[j].count;
            }
        }
    }

// 寻找频次第二高的字母
    data max = {0}, submax = {0};
    for (int i(0); i < 25; ++i)
    {
        if (stats[i].count > submax.count) // 加这个if是为了防止a(3), b(3), c(2)...这种降序排列的时候，submax没有值
        {
            if (stats[i].count > max.count) // 如果某字母的出现次数 > max值，那么max值就变成第二大，该字母就是最大值，不能用>=，防止多个相等max值出现
            {
                submax.count = max.count;
                submax.letter = max.letter;
                max.count = stats[i].count;
                max.letter = stats[i].letter;
            }
            else if (stats[i].count < max.count) // 考虑到可能多个字母值都等于max值的情况，必须限制这个条件而不能直接用else
            {
                submax.count = stats[i].count;
                submax.letter = stats[i].letter;
            }
        }
        else if (stats[i].count == submax.count) //多个submax出现时，以先出现的字母为准(index小的那个)。
        {
            int submax_index(0), temp_index(0);
            for (int j(0); j < strlen(arr); ++j)
            {
                if (submax.letter == arr[j])
                {
                    submax_index = j;
                    break; // 找到了就跳出循环，否则后面的index会覆盖前面的index
                }
            }
            for (int j(0); j < strlen(arr); ++j)
            {
                if (stats[i].letter == arr[j])
                {
                    temp_index = j;
                    break; // 同样要跳出循环， 而且和submax_index不能在同一个循环，否则前面break了后面就找不了。
                }
            }
            if (temp_index < submax_index)
            {
                submax.count = stats[i].count;
                submax.letter = stats[i].letter;
            }
        }
    }
    cout << submax.letter << '+' << (char)tolower(submax.letter) << ':' << submax.count << endl;
    return 0;
}