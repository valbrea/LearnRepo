#include <iostream>
using namespace std;
int main()
{
    double array[8], array_cumul[8];
    cout << "input 8 values." << endl;
    for (int i(0); i < 8; ++i)
        cin >> array[i];
    array_cumul[0] = array[0];
    for (int i(1); i < 8; ++i)
        array_cumul[i] = array_cumul[i - 1] + array[i];
    for(int i(0); i < 8; ++i)
        cout << array[i] << ' ';
    cout << endl;
    for(int i(0); i < 8; ++i)
        cout << array_cumul[i] << ' ';
    cout << endl;

    return 0;
}