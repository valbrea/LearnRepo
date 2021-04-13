#include <iostream>
using namespace std;
int main() {
    int n, m, i, j;
    n = 9; m = 0;
for (i = 1; i <= n; i++)
   for (j = 2 * i; j <= n; j++)
       m = m + 1;
       cout << m;
    return 0;
}