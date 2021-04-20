#include <stdio.h>
#include <string.h>

int main()
{
    char givenname[20], familyname[20];

    printf("what's your given name?\n");
    scanf("%s",givenname);
    printf("what's your family name?\n");
    scanf("%s",familyname);
    printf("%s %s\n", familyname, givenname);
    printf("%*zd %*zd\n", strlen(familyname), strlen(familyname), strlen(givenname), strlen(givenname));
    printf("%s %s\n", familyname, givenname);
    printf("%-*zd %-*zd\n", strlen(familyname), strlen(familyname), strlen(givenname), strlen(givenname));

    return 0;
}