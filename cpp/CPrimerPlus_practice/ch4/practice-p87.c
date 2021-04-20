#include <stdio.h>
int main()
{
    char name[40];
    float cash = 1000;
    
    printf("What's your name?\n");
    scanf("%s", name); //只读取到空格处就会停止
    printf("The %s family just may be %.2f dollars richer!\n", name, cash);

    getchar();
    getchar();
    return 0;
}