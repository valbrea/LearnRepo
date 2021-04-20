#include <iostream>
using namespace std;
int main()
{
    int i = 0;
    while (i < 3)
    {
        switch (i++)
        {
            case 0: cout << "0 ";
            case 1: cout << "1 ";
            case 2: cout << "2 ";
            default : cout << "oh no!";
        } 
        cout << endl;
    }
    
    return 0;
}