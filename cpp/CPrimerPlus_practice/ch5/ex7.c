#include <stdio.h>

double CubeNumber(double n);

int main(void)
{
    double num;

    printf("Enter a number.\n");
    scanf("%lf", &num);
    printf("%lf ^ 3 = %lf\n", num, CubeNumber(num));

    return 0;
}

double CubeNumber(double n)
{
    double n3 = n * n * n;
    return n3;
}