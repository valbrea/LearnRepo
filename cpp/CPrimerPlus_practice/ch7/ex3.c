/* Programming Exercise 7-3 */
#include <stdio.h>
int main(void)
{
    int n;
    double sumeven = 0.0;
    int ct_even = 0;
    double sumodd = 0.0;
    int ct_odd = 0;
    while (scanf("%d", &n) == 1 && n != 0)
    {
        if (n % 2 == 0)
        {
            sumeven += n;
            ++ct_even;
        }
        else // n % 2 is either 1 or -1
        {
            sumodd += n;
            ++ct_odd;
        }
    }
    printf("Number of evens: %d", ct_even);
    if (ct_even > 0)
        printf(" average: %g", sumeven / ct_even);
    putchar('\n');
    printf("Number of odds: %d", ct_odd);
    if (ct_odd > 0)
        printf(" average: %g", sumodd / ct_odd);
    putchar('\n');
    printf("\ndone\n");
    return 0;
}