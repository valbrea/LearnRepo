#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    char input;
    int count1(0), count2(0);
    while ((input = cin.get())!= '#') // 要读入空格， 且输入类型为字符。
    {
        switch (input)
        {
        case '.':
            cout << '!';
            ++count1;
            break;
        case '!':
            cout << "!!";
            ++count2;
            break;
        default:
            cout << input;
            break;
        }
    }
    cout << endl;
    cout << count1 << " replacement(s) of . with !" << endl;
    cout << count2 << " replacement(s) of ! with !!" << endl;

    return 0;
}
