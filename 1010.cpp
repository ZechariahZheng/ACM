#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int WALL = 0;
const int START = 1;
const int DOOR = 2;
const int EMPTY = 3;

const int SIZE = 100005;

struct block{
	int flag;		//标志位
	block *left;
	block *low;
	block *right;
	block *up;
	block *walked;
	bool leftpassed;
	bool leftpassedbkp;
	bool lowpassed;
	bool lowpassedbkp;
	bool rightpassed;
	bool rightpassedbkp;
	bool uppassed;
	bool uppassedbkp;
};

block num[SIZE];
block *tmp;
block *start;

/*设置标志位*/
void SetNum(block *num, const int &i, int flag)
{
	num[i].flag = flag;
	num[i].walked = NULL;
	num[i].leftpassed = false;
	num[i].lowpassed = false;
	num[i].rightpassed = false;
	num[i].uppassed = false;
}

/*设置经过位*/
void SetPass(block *num, const int &i, const int n, const int m)
{
	int tmp;

	if (n == 1)
	{
		/*只有一列的情况*/
		num[i].left = NULL;
		num[i].right = NULL;
		num[i].leftpassed = true;
		num[i].rightpassed = true;

		/*上下*/
		if (i == 0)
		{
			num[i].up = NULL;
			num[i].uppassed = true;
		}
		else
		{
			num[i].up = num+i-1;
			num[i].uppassed = false;
		}

		if (i == m-1)
		{
			num[i].low = NULL;
			num[i].lowpassed = true;
		}
		else
		{
			num[i].low = num+i+1;
			num[i].lowpassed = false;
		}
		num[i].leftpassedbkp = num[i].leftpassed;
		num[i].lowpassedbkp = num[i].lowpassed;
		num[i].rightpassedbkp = num[i].rightpassed;
		num[i].uppassedbkp = num[i].uppassed;
	}
	else
	{
		/*无左侧*/
		if ((i+1)%n == 1)
		{
			num[i].left = NULL;	
			num[i].leftpassed = true;
		}
		else
		{
			num[i].left = num+(i-1); 
			/*左侧为墙，则默认为走过*/
			if (num[i].left->flag == WALL)
				num[i].leftpassed = true;
		}
		num[i].leftpassedbkp = num[i].leftpassed;

		/*无下侧*/
		if ((((i+1)/n == m-1) && ((i+1)%n >= 1)) || ((i+1)/n == m))
		{
			num[i].low = NULL;
			num[i].lowpassed = true;
		}
		else
		{
			tmp = (((i+1)/n + 1)*n + (i+1)%n) - 1;
			num[i].low = num+tmp;
			if (num[i].low->flag == WALL)
				num[i].lowpassed = true;
		}		
		num[i].lowpassedbkp = num[i].lowpassed;

		/*无右侧*/
		if ((i+1)%n == 0)
		{
			num[i].right = NULL;
			num[i].rightpassed = true;
		}
		else
		{
			num[i].right = num+(i+1);
			if (num[i].right->flag == WALL)
				num[i].rightpassed = true;
		}
		num[i].rightpassedbkp = num[i].rightpassed;

		/*无上侧*/
		if ((((i+1)/n == 0) && ((i+1)%n > 0)) || (((i+1)/n == 1) && ((i+1)%n == 0)))
		{
			num[i].up = NULL;
			num[i].uppassed = true;
		}
		else
		{
			tmp = (((i+1)/n - 1)*n + (i+1)%n) - 1;
			num[i].up = num+tmp;
			if (num[i].up->flag == WALL)
				num[i].uppassed = true;
		}	
		num[i].uppassedbkp = num[i].uppassed;
	}
}

/*将所有格子恢复原值*/
void Reset(block *num, const int *n)
{
	for (int i = 0; i < *n; i++)
	{
		num[i].leftpassed = num[i].leftpassedbkp;
		num[i].lowpassed = num[i].lowpassedbkp;
		num[i].rightpassed = num[i].rightpassedbkp;
		num[i].uppassed = num[i].uppassedbkp;
	}
}

/*探索起点的一个方向的所有路径*/
void CalcWay(block *num, block *now, int &t, int *ret)
{
	/*成功返回*/
	if (now->flag == DOOR && t >= 0)
	{
		*ret = 1;
	}
	
	/*跳到一下边的条件：1、没有跳过；2、不是从那边跳过来的；3、跳过去的格子不是跳过来的点；4、当前不是终点；5、跳过去的不是墙*/
	if (now->leftpassed == false && now->flag != DOOR && now->left != now->walked && now->left->flag != START && t > 0)
	{
		/*跳往左边*/
	//	cout << "left" << endl;
		now->leftpassed = true;
		tmp = now;
		now = now->left;
		now->walked = tmp;
		t--;
		CalcWay(num, now, t, ret);	
		return;
	}
	if (now->lowpassed == false && now->flag != DOOR && now->low != now->walked && now->low->flag != START && t > 0)
	{
		/*跳往下边*/
	//	cout << "low" << endl;
		now->lowpassed = true;
		tmp = now;
		now = now->low;
		now->walked = tmp;
		t--;
		CalcWay(num, now, t, ret);	
		return;
	}
	if (now->rightpassed == false && now->flag != DOOR && now->right != now->walked && now->right->flag != START && t > 0)
	{
		/*跳往右边*/
//		cout << "right" << endl;
		now->rightpassed = true;
		tmp = now;
		now = now->right;
		now->walked = tmp;
		t--;
		CalcWay(num, now, t, ret);	
		return;
	}	
	if (now->uppassed == false && now->flag != DOOR && now->up != now->walked && now->up->flag != START && t > 0)
	{
		/*跳往上边*/
	//	cout << "up" << endl;
		now->uppassed = true;
		tmp = now;
		now = now->up;
		now->walked = tmp;
		t--;
		CalcWay(num, now, t, ret);	
		return;	
	}

	/*回退到上一格的情况*/
	/*1、时间到了*/
	if (t == 0 && now->flag != DOOR)
	{
	//	cout << "back" << endl;
		now = now->walked;
		t++;
		CalcWay(num, now, t, ret);		
		return;
	}

	//2、探测了该点周围的方向：除了跳过来的地方，全部不能走,即三个方向跳过*/
	if (((now->leftpassed == true) && (now->lowpassed == true) && (now->rightpassed == true) && (now->uppassed == false))
		|| (now->lowpassed == true && now->rightpassed == true && now->uppassed == true && now->leftpassed == false)
		|| (now->rightpassed == true && now->uppassed == true && now->leftpassed == true && now->lowpassed == false)
		|| (now->rightpassed == false && now->uppassed == true && now->leftpassed == true && now->lowpassed == false))
	{
		if (now->flag != DOOR)
		{
	//		cout << "back" << endl;
			now = now->walked;
			t++;
			CalcWay(num, now, t, ret);	
			return;
		}
	}

	/*如何退出:回退到起点则返回*/
	if (now->flag == START)
		ret = 0;
}

/*从起点开始向四周探索*/
int FindWay(block *num, block *now, const int *n, int &t)
{
	int ret = 0;

	/*从起点，一个方向走完，再走另一个方向，走一个方向时，把其他方向锁死*/
	if (now->leftpassed == false)
	{
	//	cout << "1" << endl;
		now->lowpassed = true;
		now->rightpassed = true;
		now->uppassed = true;
		CalcWay(num, now, t, &ret);
		if (ret == 1)
			return ret;
	}
	else if (now->lowpassed == false)
	{
	//	cout << "2" << endl;
		Reset(num, n);
		now->leftpassed = true;
		now->rightpassed = true;
		now->uppassed = true;
		CalcWay(num, now, t, &ret);
		if (ret == 1)
			return ret;
	}
	else if (now->rightpassed == false)
	{
	//	cout << "3" << endl;
		Reset(num, n);
		now->leftpassed = true;
		now->lowpassed = true;
		now->uppassed = true;
		CalcWay(num, now, t, &ret);
		if (ret == 1)
			return ret;
	}
	else if (now->uppassed == false)
	{
	//	cout << "4" << endl;
		Reset(num, n);
		now->leftpassed = true;
		now->lowpassed = true;
		now->rightpassed = true;
		CalcWay(num, now, t, &ret);
		if (ret == 1)
			return ret;
	}
	else
		return ret;
}

int main(void)
{
	int m, n;	//矩形的长、宽
	int t;
	int i;
	char tmp;
	block *now = NULL;
	int res;

	while (cin >> m && cin >>n && cin >> t && m != 0 && n != 0 && t != 0)
	{
		res = 0;
		for (i = 0; i < m*n; i++)
		{
			if (cin >> tmp)
			{
				switch (tmp)
				{
					case 'S':SetNum(num, i, START);
							 now = num+i;
							 start = now;
							 break;
					case 'X':SetNum(num, i, WALL);
							 break;
					case 'D':SetNum(num, i, DOOR);
							 break;
					case '.':SetNum(num, i, EMPTY);
							 break;
					default:break;
				}
			}
		}
		for (int j = 0; j < i; j++)
		{
			SetPass(num, j, n, m);
		}
		res = FindWay(num, now, &i, t);
		if (true == res)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;	
	}

	return 0;
}
