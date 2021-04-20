/* addemup.c -- five kinds of statements */
#include <stdio.h>
int main(void)                /* finds sum of first 20 integers */
{
    int count, sum, day;           /* declaration statement          */
    
    count = 0;                /* assignment statement           */
    sum = 0;                  /* ditto                          */
    printf("How many days do you want to culculate?");
    scanf("%d", &day);
    while (count++ < day)      /* while                          */
        sum = sum + count * count;    /*     statement                  */
    printf("sum = %d\n", sum);/* function statement             */
    
    return 0;                 /* return statement               */
}
