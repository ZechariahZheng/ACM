#include <iostream>

using namespace std;

const int SIZE = 100005;

int input[SIZE];

void CalcTime(const int *input, int &i, int &result)
{
	/*ֻ��һ������*/
	if (0 == i)
	{
		result += 5+6*input[i];
	}
	else
	{
		/*��ǰ����������һ����*/
		if (input[i] > input[i-1])
		{
			result += 6*(input[i]-input[i-1]) + 5;
			i--;
			CalcTime(input, i, result);
		}
		/*��ǰ����������һ����*/
		else 
		{
			result += 4*(input[i-1]-input[i]) + 5;
			i--;
			CalcTime(input, i, result);
		}
	}
}

int main(void)
{
	int n;
	int tmp, result = 0;
	int i;

	while (cin >> n && n != 0)
	{
		for (i = 0; i < n; i++)
		{
			if (cin >> tmp && tmp < 100)
			{
				input[i] = tmp;
			}
		}
		i--;
		CalcTime(input, i, result);
		printf("%d\n", result);
		result = 0;
	}
	return 0;
}