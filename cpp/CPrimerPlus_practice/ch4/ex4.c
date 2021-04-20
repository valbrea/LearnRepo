#include <stdio.h>
int main()
{
    float height;
    char name[20];

    printf("your height(cm):\n");
    scanf("%f", &height);
    printf("your name:\n");
    scanf("%s", name);
    printf("%s, you are %.2f meters tall.\n", name, height / 100);

    return 0;

}