#include <iostream>
#include <string.h>

using namespace std;

int num = 0;
int i = 0;

void str2num(char *str, int n)
{
	while (n--)
	{
		str[n] = str[n] - 48;
	}
}

void num2str(char *num, int n)
{
	while (n--)
	{
		num[n] = num[n] + 48;
	}
}

void CalcRoot(char *str, int *n)
{
	if (*n > 1)
	{
		num = 0;
		for(i = 0; i < *n; i++)
			num += str[i];
		sprintf(str, "%d", num);
		*n = strlen(str);
		str2num(str, *n);
		CalcRoot(str, n);
	}
}

int main(void)
{
	char str[100006];
	char *tmp = "0";
	int n = 0;

	while (cin >> str && strcmp(str, tmp)!=0)
	{
		n = strlen(str);
		str2num(str, n);
		CalcRoot(str, &n);
		num2str(str, 1);
		cout << str << endl;
	}
	return 0;
}