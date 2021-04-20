#include <stdio.h>
#include<string.h>
#define BOOK "War and Peace"
int main(void)
{
    float cost = 12.99;
    float percent = 80.0;
    printf("This copy of \"%s\" sells for $%.2f.\n"
    "That is %.0f%% of list.\n", BOOK, cost, percent);
    printf("%-7.5s", "sdfasd");

    getchar();
    return 0;
}