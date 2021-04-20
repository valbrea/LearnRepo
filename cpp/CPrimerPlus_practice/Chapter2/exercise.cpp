#include<stdio.h>
void jolly(void);
void br(void);
void ic(void);
void smile(void)					//函数原型必须在调用前面，函数原型可以和定义一起放在文件前面，但是main函数前面一定要有该调用函数的原型声明
{
	printf("Smile!");
}
void one_three(void), two(void);	//函数原型也可以像变量声明一样一起写，但具体规则不知道是否一样

int main(void)
{
	//练习1
	printf("Zhang Xingyu\n");
	printf("Zhang\nXingyu\n");
	printf("Zhang ");
	printf("Xingyu\n\n");
	
	//练习2
	printf("姓名张兴宇，地址四川。\n\n");

	//练习3
	int days = 24 * 365;
	printf("我活了%d天。\n\n", days);
	
	//练习4
	jolly();
	jolly();
	jolly();
	printf("Which nobody can deny!\n\n");

	//练习5
	br(); printf(", "); ic(); printf("\n");
	ic(); printf(",\n");
	br(); printf("\n\n");

	//练习6
	int toes = 10, toes2 = toes * toes, doubletoes = toes * 2;	//可以直接声明变量的时候赋值
	printf("toes=%d, toes doubled=%d, toes squared=%d\n\n", toes, doubletoes, toes2);

	//练习7
	smile(); smile(); smile(); printf("\n");
	smile(); smile(); printf("\n");
	smile(); printf("\n\n");

	//练习8
	printf("starting now:\n");
	one_three();
	printf("done!\n\n");

	return 0;
}

void jolly(void)
{
	printf("For he's a jolly good fellow!\n");
	
}

void br(void)
{
	printf("Brazil, Russia");
}

void ic(void)
{
	printf("India, China");
}

void one_three(void)
{
	printf("one\n");
	two();
	printf("three\n");
}

void two(void)
{
	printf("two\n");
}