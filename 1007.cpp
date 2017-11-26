/*求平面 最近点对的方法，就是分治法。
先将点分成两个区间，假设S1，S2，然后分别求S1内最近点对的点d1，S2内最近点对的点d2
再求S1与S2内最近点对 d=min（d1,d2）
但是，不能忘记，最近点对可能是 一个点在S1一个点在S2。
接下来就是比较精华的部分：
所求的点的位置，一定在于  mid-d,mid+d 之间。
然后，就在这个区间开始找点，并不断更新d值，最后就可以得到d了。*/

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
// 求两点之间的距离  
double dis(Point a,Point b)  
{  
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));  
}  
// 根据点横坐标or纵坐标排序  
bool cmp_y( int a,int b)  
{  
    return p[a].y<p[b].y;  
}  
bool cmp_x( Point a,Point b)  
{  
    return a.x<b.x;  
}  
// 求最近点对  
double close_pair( int l,int r )  
{  
    // 判断两个点和三个点的情况  
    if( r==l+1 )    return dis( p[l],p[r] );  
    else if( r==l+2 )   return Min( dis(p[l],p[r]),Min( dis(p[l],p[l+1]),dis(p[l+1],p[r]) ) );  
  
    int mid=(l+r)>>1;  
    double ans=Min(close_pair(l,mid),close_pair(mid+1,r));  
  
    int i,j,cnt=0;  
    // 如果 当前p[i]点 横坐标位于 范围（中点横坐标-ans，中点横坐标+ans）位置内，则记录点的序号  
    for(i=l; i<=r; ++i)  
        if(  p[i].x>=p[mid].x-ans && p[i].x<=p[mid].x+ans  )  
            arr[cnt++]=i;  
    // 按照纵坐标由小到大 对于arr数组内点进行排序  
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
        // 先将所有点按照横坐标由小到大排序  
        sort(p,p+n,cmp_x);  
        printf("%.2lf\n",close_pair(0,n-1)/2.0);  
    }  
    return 0;  
} 