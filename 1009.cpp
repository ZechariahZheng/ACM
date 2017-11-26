#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int SIZE = 100005;
typedef struct {
	int GetFood;
	int UseFood;
}room;

room num[SIZE];

bool cmp(room &num1, room &num2)
{
	double tmp1 = num1.GetFood / (double)num1.UseFood;
	double tmp2 = num2.GetFood / (double)num2.UseFood;

	return tmp1 < tmp2;
}

double CalcGetFood(const room &num, int &cost)
{
	double result = 0;

	if (cost >= num.UseFood)
	{	
		cost -= num.UseFood;
		result = num.GetFood;
	}
	else
	{
		result = num.GetFood * cost /(double)num.UseFood;
		cost = 0;
	}
	return result;	
}

void CalcMaxFood(room *num, int &cost, int &i, double &result)
{
	/*只有一个房间*/
	if (i == 0 || cost < num[i].UseFood)
	{
		result += CalcGetFood(num[i], cost);
	}
	else
	{
		/*多个房间，从排序之后的最后一个房间开始*/
		result += CalcGetFood(num[i], cost);
		i--;
		CalcMaxFood(num, cost, i, result);
	}
}

int main(void)
{
	int n, m;
	int i,j;
	int tmp1, tmp2;
	double result = 0;

	while ( cin >> m && cin >> n && n != -1 && m != -1)
	{
		for (i = 0; i < n; i++)
		{
			if (cin >> tmp1 && cin >> tmp2)
			{
				num[i].GetFood = tmp1;
				num[i].UseFood = tmp2;
			}
		}
		/*将num从小到大重新排序，即x越大，y越小，越好*/
		sort(num, num+i, cmp);
		i--;
		CalcMaxFood(num, m, i, result);
		printf("%.3lf\n", result);
		result = 0;
	}

	return 0;
}