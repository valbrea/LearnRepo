#include <stdio.h>
int main(void) 
{
    int day, week, left;
    const int dpw = 7; //days per week

    printf("Enter mumber in days, this program will convert it to weeks and days.\n");
    printf("Number <= 0 to quit.\n");
    scanf("%d", &day);
    while (day > 0)
    {
        week = day / dpw;
        left = day % dpw;
        printf("%d lefts is %d weeks, %d days.\n", day, week, left);
        printf("What's your next number?\n");
        scanf("%d", &day);
    }
    printf("Done!\n");

    return 0;
}