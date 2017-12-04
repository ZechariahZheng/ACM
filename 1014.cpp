#include <iostream>

/*如果递归太深超出堆栈，考虑是否可以使用循环while或do while*/

using namespace std;

int main(void)
{
	int n, m;
	int i;
	int seed;

	while (cin >> n && cin >> m && n != 0 && m != 0)
	{
		i = 0;
		seed = 0;
		do{
			seed = (seed+n)%m;
			i++;
		}while(seed != 0);
		printf("%10d%10d    ", n, m);
		if (i == m)
			printf("%s\n","Good Choice"); 
		else
			printf("%s\n","Bad Choice");
		cout << endl;
	}

	return 0;
}