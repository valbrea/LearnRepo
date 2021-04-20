#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    double daphne(100), deirdre(100);
    int years(0);
    do
    {
        daphne += 10;
        deirdre *= 1.05;
        ++years;
    } while (deirdre < daphne);
    cout << "years\tdaphne\tdeirdre" << endl;
    cout << years << '\t'<< daphne << '\t' << deirdre << endl;

    return 0;
}