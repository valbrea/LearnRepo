#include <iostream>
using namespace std;
int main()
{
    double a(0), b(0);
    while(cin >> a >> b)
    {
        if (a >= b)
        cout << (a - b) / (a * b) << endl;
        else 
        cout << (b - a) / (a * b) << endl;
    }

    return 0;
}