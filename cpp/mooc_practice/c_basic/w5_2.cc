//奇数求和

#include <iostream>
using namespace std;

int main()
{
    int m, n, sum = 0; // m 不大于 n，且n 不大于300
    // cout << "Enter two odd number." << endl;
    cin >> m >> n;
    while (m <= n)
    {
        if (m % 2 == 1)
        {
            sum += m;
        }
        m++;
    }
    cout << sum << endl;

    return 0;
}