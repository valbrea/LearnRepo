#include <stdio.h>
#define mph 60 //mins per hour
int main(void) 
{
    int min, hour, time;

    printf("Enter mumber in minutes, this program will convert it to hours and minutes.\n");
    printf("Number <= 0 to quit.\n");
    scanf("%d", &time);
    while (time > 0)
    {
        hour = time / mph;
        min = time % mph;
        printf("%d mins is %d hours, %d mins.\n", time, hour, min);
        printf("What's your next number?\n");
        scanf("%d", &time);
    }
    printf("Done!\n");

    return 0;
}