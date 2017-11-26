#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

/*采用分治思想*/
const int SIZE = 100005;
const int LEFT = 0;
const int RIGHT = 1;

typedef struct {
	int flag;		//标志位（left or right）
	double x;
	double y;
}point;

point num[SIZE];
point c[SIZE];

/*按x坐标大小排序*/
bool cmpx(point &p1, point &p2)
{
	if (p1.x == p2.x)
		return p1.y < p2.y;
	return p1.x < p2.x;
}

/*按y坐标排序*/
bool cmpy(point &p1, point &p2)
{
	if (p1.y == p2.y)
		return p1.x < p2.x;
	return p1.y < p2.y;
}

/*计算两个点的距离*/
double GetDist(point &p1, point &p2)
{
	return sqrt(pow(p1.x - p2.x, 2.0) + pow(p1.y - p2.y, 2.0));
}

/*计算三个坐标点的最小值*/
double Min(double &a, double &b, double &c)
{
	double min;

	min = a > b ? b : a;
	min = c > min ? min : c;

	return min;
}

/*比较两个距离*/
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
	else if (cnt == 1)			//两个点
	{
		return GetDist(num[start], num[end]);
	}
	else if (cnt == 2)			//三个点
	{
		double tmp1, tmp2, tmp3;

		tmp1 = GetDist(num[start], num[start+1]);
		tmp2 = GetDist(num[start], num[end]);
		tmp3 = GetDist(num[start+1], num[end]);

		return Min(tmp1, tmp2, tmp3);
	}
	else					//多个点
	{
		/*1.计算出中心点，使两侧坐标点尽量同样多*/
		double leftmin, rightmin, min;
		int mid = (start+end) / 2;

		/*递归地调用*/
		leftmin = MinRadius(start, mid);		//求得左边的最小距离
		rightmin = MinRadius(mid, end);			//求得右边的最小距离
		dist = MinDist(leftmin, rightmin);
		int p = 0;

		/*找出两侧距离中心距离小于dist的点*/
		int i;
		for (i = 0; i <= mid; i++)
		{
			double leftline = num[mid].x - dist;		//左侧线，左侧线右边的点记录下来

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
			double rightline = num[mid].x + dist;		//右侧线，右侧线左边的点记录下来
			
			if (num[i].x <= rightline)
			{
				c[p].flag = RIGHT;
				c[p].x = num[i].x;
				c[p].y = num[i].y;
				p++;
			}
		}
		sort(c, c+p, cmpy);			//将两侧找到的点按从小到大重新排序
		for (i = 0; i < p; i++)
		{
			/*在左侧线和中心线，右侧线和中心线的两个区域内，只需要考察某个点与它
			按Y坐标排序且紧接着的7个点之间的距离就可以了，计较所有的点*/
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
