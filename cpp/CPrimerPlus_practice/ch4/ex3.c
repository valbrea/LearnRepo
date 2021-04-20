#include <stdio.h>
int main()
{
    float aa;

    scanf("%f", &aa);
    printf("The input is %.1f or %.1e.\n", aa, aa);
    printf("The input is %+.3f or %.3E.\n", aa, aa); //系统不同，指数记数法显示的位数可能不同

    return 0;
}