#include <iostream>
#include <algorithm>
#include <malloc.h>

using namespace std;

struct node {
	int n;
	struct node *pre;
	struct node *next;
};

char all[100][20];
int num = 0;

/*检查两个数的和是否是素数*/
int IsPrime(int a, int b)
{
	int c = a+b;
	int i;

	for (i = 2; i <= c-1; i++)
	{
		if (c%i == 0)
			break;
	}
	if (i < c)
		return 0;		//非素数
	return 1;			//素数
}

/*检查数组是否符合要求*/
int Check(int *a, const int n)
{
	int i = 0;
	int res;

	for (i = 0; i < n-1; i++)
	{
		res = IsPrime(a[i], a[i+1]);
		if (!res)
			return 0;
	}
	return 1;
}

/*数字转化为字符串*/
char *Num2Str(int *a, int n)
{
	char *str;
	int i;

	str = (char *)malloc(n+1);
	for (i = 0; i < n; i++)
	{
		str[i] = a[i]+48;
	}
	str[i] = '\0';

	return str;
}

/*将队列转换为数组*/
void Queue2Arr(node *head, int *a)
{
	int i = 0;
	node *tmp = head;

	do{
		a[i] = tmp->n;
		tmp = tmp->next;
		i++;
	}while(tmp->next != NULL);
}


/*列出所有的组合可能：从数组中选出一个元素，插入到剩余数组中的某一位置*/
void Sort(int *a, const int n)
{
	node *tmp;
	node *head;
	node *old = NULL;
	node *location;
	node *aim;
	int cnt;
	int res = 0;
	char *str;

	/*将数组转化为队列*/
	for (int i = 0; i < n; i++)
	{
		tmp = (node *)malloc(sizeof(node));
		tmp->pre = NULL;
		tmp->next = NULL;
		tmp->n = a[i];
		if (i == 0)
		{
			head = tmp;
		}
		if (i > 0)
		{
			tmp->pre = old;
			old->next = tmp;
		}
		old = tmp;
	}

	/*取出一个元素，插入剩余的数组，元素为n-1个*/
	for (int i = 0; i < n-1; i++)
	{
		cnt = i;
		tmp = head;

		/*取第几个元素*/
		do{
			location = tmp->next;
			tmp = location;
		}while(cnt-- > 0);

		aim = location;				//取出的元素
		cout << aim->n << endl;

		/*取出一个元素，插入剩余的数组，元素为n-1个*/
	for (int i = 0; i < n-1; i++)
	{
		cnt = i;
		tmp = head;

		if (tmp->next == NULL)
			cout << "hllo";
		/*取第几个元素*/
		do{
			location = tmp->next;
			tmp = location;
		}while(cnt-- > 0);

		aim = location;				//取出的元素
		/*取出一个元素，剩余的元素重新组成一个队列*/
		tmp->pre->next = tmp->next;
		if (tmp->next != NULL)
			tmp->next->pre = tmp->pre;

		/*开始插入*/
		/*把选出来的元素，依次插入剩余队列的每个元素的前后，再比较条件*/
		for (int j = 0; j < n-1; j++)
		{
			/*定位要插入的元素位置*/
			cnt = j;
			tmp = head;

			do{
				location = tmp->next;
				tmp = location;
			}while(cnt-- >= 0);
			
			/*向前插入*/
			tmp->pre->next = aim;
			tmp->pre = aim;
			aim->pre = tmp->pre;
			aim->next = tmp;
			Queue2Arr(head, a);
			res = Check(a, n);
			if (res)
			{
				str = Num2Str(a, n);
				cout << str << endl;
			}

			/*向后插入*/
			aim->next = NULL;
			if (tmp->next != NULL)
			{
				tmp->next->pre = aim;
				aim->next = tmp->next;
			}
			tmp->next = aim;
			aim->pre = tmp;
			Queue2Arr(head, a);
			res = Check(a, n);
			if (res)
			{
				str = Num2Str(a, n);
				cout << str << endl;
			}
		}
	}
		
	}
}


int main(void)
{
	int n;
	int i = 1;
	int j;
	int *a;

	while (cin >> n && n > 0)
	{
		a = (int *)malloc(n*sizeof(int));
		for (j = 0; j < n; j++)
			a[j] = j+1;
		Sort(a, n);
		free(a);
	//	cout << all[0] << endl;
	//	cout << num << endl;
	}
	return 0;
}