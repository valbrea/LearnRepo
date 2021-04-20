#include <stdio.h>
int main()
{
    float speed, size;

    printf("Download Speed(Mb/s):\n");
    scanf("%f", &speed);
    printf("File size(MB):\n");
    scanf("%f", &size);
    printf("At %.2f megabits per second, a file of %.2f megabytes\n"
    "downloads in %.2f seconds\n", speed, size, size * 8 / speed);

    return 0;

}