#include <stdio.h>
#define FORMAT "%s! C is cool!\n"
int main(void)
{
    char c1, c2;
    c1 = 'S', c2 = 'O';
    char n = 'a' - 1;
    printf("%d, %d\n", c1, c2);
    printf(FORMAT, FORMAT);
    while (n++ < 'g')
    {
        printf("%5c", n);
    }
    printf("\n");
    return 0;
}