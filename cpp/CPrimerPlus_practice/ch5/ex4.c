#include <stdio.h>
int main(void) 
{
    float height, inch;
    int feet;
    const float CM_PER_FT = 30.48; //cm per feet
    const float CM_PER_IN = 2.54; //cm per inch
    const float IN_PER_FT = 12.0; //inch per feet

    printf("Enter your heights in cm, this program will convert it to feets and inches.\n");
    printf("Number <= 0 to quit.\n");
    scanf("%f", &height);
    while (height > 0)
    {
        feet = height / CM_PER_FT;
        inch = height / CM_PER_IN - (float)feet * IN_PER_FT;
   
        printf("%.1f cm is %d feets, %.1f inches.\n", height, feet, inch);
        printf("Enter your next number to continue or quit.\n");
        scanf("%f", &height);
    }

    printf("Done!\n");

    return 0;
}