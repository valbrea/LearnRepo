#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int lower, upper, index;
    int square, cube;
    cout << "Enter starting integer" << endl;
    cin >> lower;
    cout << "Enter ending integer: " << endl;
    cin >> upper;
    cout << setw(5) << "num" << setw(10) << "square" << setw(15) << "cube" << endl;
    for (index = lower; index <= upper; index++)
    {
        square = index * index;
        cube = index * square;
        cout << setw(5) << index << setw(10) << square << setw(15) << cube << endl;
    }
    
    return 0;
}