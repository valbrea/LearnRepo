#include <stdio.h>
int main(void)
{
    int num;
    int end;
    
    printf("Please enter an integer.\n");
    scanf("%d", &num);
    end = num + 10;
    while (num <= end)
    {
        printf("%d\t", num);
        num++;
    }
    printf("\nDone！\n");

    return 0;
}