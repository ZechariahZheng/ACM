/*��ƽ�� �����Եķ��������Ƿ��η���
�Ƚ���ֳ��������䣬����S1��S2��Ȼ��ֱ���S1�������Եĵ�d1��S2�������Եĵ�d2
����S1��S2�������� d=min��d1,d2��
���ǣ��������ǣ������Կ����� һ������S1һ������S2��
���������ǱȽϾ����Ĳ��֣�
����ĵ��λ�ã�һ������  mid-d,mid+d ֮�䡣
Ȼ�󣬾���������俪ʼ�ҵ㣬�����ϸ���dֵ�����Ϳ��Եõ�d�ˡ�*/

#include <stdio.h>  
#include <math.h>  
#include <algorithm>  
using namespace std;  
#define N 100001  
struct Point  
{  
    double x,y;  
}p[N];  
int arr[N];  
double Min(double a,double b)  
{  
    return a<b?a:b;  
}  
// ������֮��ľ���  
double dis(Point a,Point b)  
{  
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));  
}  
// ���ݵ������or����������  
bool cmp_y( int a,int b)  
{  
    return p[a].y<p[b].y;  
}  
bool cmp_x( Point a,Point b)  
{  
    return a.x<b.x;  
}  
// ��������  
double close_pair( int l,int r )  
{  
    // �ж������������������  
    if( r==l+1 )    return dis( p[l],p[r] );  
    else if( r==l+2 )   return Min( dis(p[l],p[r]),Min( dis(p[l],p[l+1]),dis(p[l+1],p[r]) ) );  
  
    int mid=(l+r)>>1;  
    double ans=Min(close_pair(l,mid),close_pair(mid+1,r));  
  
    int i,j,cnt=0;  
    // ��� ��ǰp[i]�� ������λ�� ��Χ���е������-ans���е������+ans��λ���ڣ����¼������  
    for(i=l; i<=r; ++i)  
        if(  p[i].x>=p[mid].x-ans && p[i].x<=p[mid].x+ans  )  
            arr[cnt++]=i;  
    // ������������С���� ����arr�����ڵ��������  
    sort(arr,arr+cnt,cmp_y);  
    for(i=0; i<cnt; i++)  
        for(j=i+1; j<cnt; j++)  
        {  
            if(p[arr[j]].y-p[arr[i]].y>=ans) break;  
            ans=Min(ans,dis(p[arr[i]],p[arr[j]]));  
        }  
  
    return ans;  
}  
  
int main()  
{  
    int i,n;  
    while( scanf("%d",&n)!=EOF && n)  
    {  
        for(i=0;i<n;++i)  
            scanf("%lf%lf",&p[i].x,&p[i].y);  
        // �Ƚ����е㰴�պ�������С��������  
        sort(p,p+n,cmp_x);  
        printf("%.2lf\n",close_pair(0,n-1)/2.0);  
    }  
    return 0;  
} 