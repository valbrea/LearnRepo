/* Programming Exercise 7-5 */
#include <stdio.h>
int main(void)
{
    char ch;
    int ct1 = 0;
    int ct2 = 0;
    while ((ch = getchar()) != '#')
    {
        switch (ch)
        {
        case '.':
            putchar('!');
            ++ct1;
            break;
        case '!':
            putchar('!');
            putchar('!');
            ++ct2;
            break;
        default:
            putchar(ch);
        }
    }
    printf("%d replacement(s) of . with !\n", ct1);
    printf("%d replacement(s) of ! with !!\n", ct2);
    return 0;
}