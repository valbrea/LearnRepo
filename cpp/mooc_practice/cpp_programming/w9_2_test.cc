#include <iostream>
#include <iterator>
using namespace std;
int main()
{
        istream_iterator<int> inputInt(cin);
        cout << * inputInt << "," ;
        inputInt ++;
        inputInt ++;
        cout << * inputInt;
        return 0;
}