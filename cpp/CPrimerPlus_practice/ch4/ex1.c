#include <stdio.h>
int main()
{
    char givename[20], familyname[20];
    
    printf("what's your given name and family name?\n");
    scanf("%s %s",givename, familyname);
    printf("%s, %s\n", familyname, givename);

    return 0;
}