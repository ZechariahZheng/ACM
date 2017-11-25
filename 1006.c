#include <stdio.h>

double ClockMinus(double n1, double n2)
{
    if (n1 > n2)
    {
        if (n1-n2 >= 180.0)
            return 360.0-(n1-n2);
        else
            return n1-n2;
    }
    else
    {
        if (n2-n1 >= 180.0)
            return 360.0-(n2-n1);
        else
            return n2-n1;
    }
}

void func(const double WantDegree)
{
    double HD,MD,SD,HM,HS,MS;
    double a=1, b=120, c=10;

    const double HSpead = a/b;
    const double MSpead = a/c;
    const double SSpead = c;
    const int sum = 3600*12;

    int times = 1;
    int cnt = 0;
    double precent;

    while (times <= sum)
    {
        HD = (HSpead*times); 
        MD = (MSpead*times);
        SD = (SSpead*times);

        HD -= ((int)(HD/360.0))*360.0;
        MD -= ((int)(MD/360.0))*360.0;
        SD -= ((int)(SD/360.0))*360.0;
        
		//到这一步都没有问题，下一步出现精度问题
        HM = ClockMinus(HD,MD);
        HS = ClockMinus(HD,SD);
        MS = ClockMinus(MD,SD);
        
        if (HM>=WantDegree&&HS>=WantDegree&&MS>=WantDegree)
            cnt++;
        times++;
    }
    precent = cnt*1.0/(12*36);
    
    printf("%.3lf\n", precent);
}

int main()
{
    double WantDegree;

    while (scanf("%lf", &WantDegree)!=EOF && 0<=WantDegree<=120)
    {
        func(WantDegree);
    }

    return 0;
}