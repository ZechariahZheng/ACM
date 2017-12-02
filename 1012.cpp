#include <iostream>
#include <math.h>

using namespace std;

/*网上函数*/
int CalcI(int n)
{
	if (n == 1 || n == 0)
		return 1;
	else
		return n*CalcI(n-1);
}	


/*参数sum：起始值必须为1*/
/*
void CalcI(int *n, int *sum)
{
	if (*n > 1)
	{
		*sum = (*sum) * (*n);
		*n = *n - 1;
		cout << *n << endl;
		CalcI(n, sum);
		return;
	}
}		*/

int sumI = 1;
int I[100006];

/*存储要用的分母*/
/*用到的几个分母*/

void GetI(int *i, int *I)
{
	for (int j = 0; j <= *i; j++)
	{
		I[j] = CalcI(j);
	}
}	

/*参数n:要计算的n个范围
*参数i：第几个数，从0开始
*参数e：求出的值
*参数I：用到的分母*/
void CalcE(int *n, int *i, double *e, int *I)
{
	if (*i == *n)
	{
		*e += 1.0/I[*i];
		printf("%d", *i);
		printf(" %.9f\n", *e);
	}
	else
	{
		*e += 1.0/I[*i];
		if (*i < 3)
			cout << *i << " " << *e << endl;
		else
		{
			printf("%d", *i);
			printf(" %.9f\n", *e);
		}
		(*i)++;
		CalcE(n, i, e, I);
	}
}

int main(void)
{
	int n = 5;
	int i = 1;
	double e = 0;

	cout << "n e" << endl;
	cout << "- -----------" << endl;
	GetI(&n, I);
	CalcE(&n, &i, &e, I);

	return 0;
}
