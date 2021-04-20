#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int num(0);
    bool prime(true);

    while (cin >> num && num > 0)
    {  
        for (int i(2); i <= num; ++i)
        {
            prime = true;
            for (int j(2); j * j <= i; ++j)
            {
                if (i % j == 0)
                    prime = false;
            }
            if (prime == true)
                cout << i << ' ';
        }
    }

    return 0;
}