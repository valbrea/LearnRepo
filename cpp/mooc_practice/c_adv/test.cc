
#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;


int main()
{
 
    char c[6] = {'h', 'e', 'l', 'l', 'o', '\0'}, *pc = c;
    cout << pc << endl << endl;
    int b[6] = {1, 2, 3, 4, 5, 6}, *pb = b;
    cout << pb << endl;

    return 0;
}