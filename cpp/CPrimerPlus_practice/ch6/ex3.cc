#include <iostream>
using namespace std;

int main()
{
    for (int i(0); i < 6; ++i)
    {
        char temp = 'F';
        for (int j(0); j < i + 1; ++j,--temp)
        {
            cout << temp;
        }
        cout << endl;
    }

    return 0;
}