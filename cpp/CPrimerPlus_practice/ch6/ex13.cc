#include <iostream>
using namespace std;
int main()
{   
    int array[8] = {0};
    int value(1);
    for (int i(0); i < 8; ++i)
    {
        array[i] = value;
        value *= 2;
    }
    int j(0);
    do
    {
        cout << array[j] << ' ';
        ++j;
    } while (j < 8);
    cout << endl;
    
        
    
    return 0;
}