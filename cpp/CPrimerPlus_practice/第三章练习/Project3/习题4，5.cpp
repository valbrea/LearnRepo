#include <stdio.h>
int main(void)
{
	float a, b;
	printf("Enter a floating-point value:");
	scanf_s("%f", &a);
	printf("fixed-point notation: %f\nexponential notation: %e\np notation: %a\n", a, a, a);
	getchar();//œ∞Ã‚4

	printf("enter your age:");
	scanf_s("%f", &b);
	printf("you have lived %e", b * 3.156e7);//œ∞Ã‚5

	return 0;
}