#include <stdio.h>
#define GAL2LITRE 3.785
#define MILE2KM 1.609
int main(void)
{
    float mileage, consumption;

    printf("enter your travel mileage(mile):\n");
    scanf("%f", &mileage);
    printf("enter your travel fuel consumption(gallon):\n");
    scanf("%f", &consumption);
    printf("The distance of per gallon is:%f\n", mileage / consumption);
    printf("The fuel consumption per 100-kilometres is:%f\n", (consumption * GAL2LITRE) / (mileage * MILE2KM) * 100);

    return 0;
}