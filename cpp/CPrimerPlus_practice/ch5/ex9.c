#include <stdio.h>
void Temperatures(double temp_fahrenheit);

int main(void)
{
    double temp_fahrenheit;
    int n;

    printf("Enter a tempedrature in Fahrenheit:");
    n = scanf("%lf", &temp_fahrenheit);
    // Temperatures(temp_fahrenheit);

    while (n == 1)
    {
        Temperatures(temp_fahrenheit);
        printf("Enter a tempedrature in Fahrenheit(Enter q to quit):");
        n = scanf("%lf", &temp_fahrenheit);
    }
    printf("Done!\n");

    return 0;
}

void Temperatures(double temp_fahrenheit)
{
    const double ABSOLUTE_TEMP = 273.16;
    double temp_celsius, temp_kelvin;

    temp_celsius = 5.0 / 9.0 * (temp_fahrenheit - 32.0);
    temp_kelvin = temp_celsius + ABSOLUTE_TEMP;
    printf("%lfF\t %lfC\t %lfK\n", temp_fahrenheit, temp_celsius, temp_kelvin);
}