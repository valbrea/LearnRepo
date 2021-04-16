#include <iostream>
using namespace std;

int main() {
    int f, d, t, h;
    for (f = 1; f <= 4; f++)
        for (d = 1; d <= 4; d++)
            for (t = 1; t <= 4; t++)
                for (h = 1; h <= 4; h++) {
                    if ((f + d + t + h == 10) && (f * d * t * h == 24)) {
                        if ((d == 1) + (h == 4) + (f == 3) == 1
                            && (h == 1) + (d == 4) + (f == 2) + (t == 3) == 1
                            && (h == 4) + (d == 3) == 1
                            && (f == 1) + (t == 4) + (h == 2) +(d == 3) == 1                          
                           )
                           cout << f  << endl << d << endl << t << endl << h << endl; 
                    }
                }
    return 0;
}