#include <stdio.h>
int main(void)
{
	float a, b, c, d;

	b = 2.0e20 + 1.0;
	a = b - 2.0e20;
	printf("%f \n", a);//舍入错误

	c = 0.1234e-38;
	d = c / 10;
	printf("%f, %f, %e, %e\n", c, d, c, d);//下溢

	getchar();
	return 0;
}