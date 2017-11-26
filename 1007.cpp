#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

/*���÷���˼��*/
const int SIZE = 100005;
const int LEFT = 0;
const int RIGHT = 1;

typedef struct {
	int flag;		//��־λ��left or right��
	double x;
	double y;
}point;

point num[SIZE];
point c[SIZE];

/*��x�����С����*/
bool cmpx(point &p1, point &p2)
{
	if (p1.x == p2.x)
		return p1.y < p2.y;
	return p1.x < p2.x;
}

/*��y��������*/
bool cmpy(point &p1, point &p2)
{
	if (p1.y == p2.y)
		return p1.x < p2.x;
	return p1.y < p2.y;
}

/*����������ľ���*/
double GetDist(point &p1, point &p2)
{
	return sqrt(pow(p1.x - p2.x, 2.0) + pow(p1.y - p2.y, 2.0));
}

/*����������������Сֵ*/
double Min(double &a, double &b, double &c)
{
	double min;

	min = a > b ? b : a;
	min = c > min ? min : c;

	return min;
}

/*�Ƚ���������*/
double MinDist(double &a, double &b)
{
	return a < b ? a : b;
}

double MinRadius(int start, int end)
{
	int cnt;
	double dist;

	cnt = end - start;
	if (cnt == 0)
		return 0;
	else if (cnt == 1)			//������
	{
		return GetDist(num[start], num[end]);
	}
	else if (cnt == 2)			//������
	{
		double tmp1, tmp2, tmp3;

		tmp1 = GetDist(num[start], num[start+1]);
		tmp2 = GetDist(num[start], num[end]);
		tmp3 = GetDist(num[start+1], num[end]);

		return Min(tmp1, tmp2, tmp3);
	}
	else					//�����
	{
		/*1.��������ĵ㣬ʹ��������㾡��ͬ����*/
		double leftmin, rightmin, min;
		int mid = (start+end) / 2;

		/*�ݹ�ص���*/
		leftmin = MinRadius(start, mid);		//�����ߵ���С����
		rightmin = MinRadius(mid, end);			//����ұߵ���С����
		dist = MinDist(leftmin, rightmin);
		int p = 0;

		/*�ҳ�����������ľ���С��dist�ĵ�*/
		int i;
		for (i = 0; i <= mid; i++)
		{
			double leftline = num[mid].x - dist;		//����ߣ�������ұߵĵ��¼����

			if (num[i].x >= leftline)
			{
				c[p].flag = LEFT;		
				c[p].x = num[i].x;
				c[p].y = num[i].y;
				p++;
			}
		}
		for (; i <= end; i++)
		{
			double rightline = num[mid].x + dist;		//�Ҳ��ߣ��Ҳ�����ߵĵ��¼����
			
			if (num[i].x <= rightline)
			{
				c[p].flag = RIGHT;
				c[p].x = num[i].x;
				c[p].y = num[i].y;
				p++;
			}
		}
		sort(c, c+p, cmpy);			//�������ҵ��ĵ㰴��С������������
		for (i = 0; i < p; i++)
		{
			/*������ߺ������ߣ��Ҳ��ߺ������ߵ����������ڣ�ֻ��Ҫ����ĳ��������
			��Y���������ҽ����ŵ�7����֮��ľ���Ϳ����ˣ��ƽ����еĵ�*/
			for (int j = 1; (j <= 7) && (i+j < p); j++)
			{
				if (c[i].flag != c[i+j].flag)
				{
					min = GetDist(c[i], c[i+j]);
					if (min < dist)
						dist = min;
				}
			}
		}
	}
	return dist;
}

int main(void)
{
	int n;
	
	while (cin >> n && n != 0)
	{
		double result = 0;
		
		for (int i = 0; i < n; i++)
		{
			num[i].flag = 0;
			cin >> num[i].x >> num[i].y;
		}

		sort(num, num+n, cmpx);

		result = MinRadius(0, n-1);

		printf("%.2lf\n", result/2);
	}

	return 0;
}
