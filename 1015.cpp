#include <iostream>  
#include <cstring>  
#include <algorithm>  
using namespace std;  
  
/*排序一下，最后那个组合就是要找的最大组合*/  
int main()  
{  
//  freopen("data.txt", "r", stdin);  
    int num, flag, i, j, k, l, m;  
    int tag[15];  
    char str[15], ans[8];  
    while(cin >> num >> str && num)  
    {  
        int length = strlen(str);  
        flag = 1;  
        memset(tag, 0, sizeof(tag));  
        for(i = 0; i < length; i++)  
        {  
            tag[i] = str[i] - 'A' + 1;  
        }  
        sort(tag, tag + length);              //排序  
        for(i = 0; i < length; i++)           //枚举  
        for(j = 0; j < length; j++)  
        if(j != i)  
        for(k = 0; k < length; k++)  
            if(k != j && k != i)  
            for(l = 0; l < length; l++)  
                    if(l != k && l != j && l != i)  
                    for(m = 0; m < length; m++)  
                    {  
                        if(m != l && m != k && m != j && m != i &&   
                        tag[i] - tag[j] * tag[j] + tag[k] * tag[k] * tag[k]   
                        - tag[l] * tag[l] * tag[l] * tag[l]   
                        + tag[m] * tag[m] * tag[m] * tag[m] * tag[m] == num)  
                        {  
                            flag = 0;  
                            ans[0] = tag[i] - 1 + 'A';  
                            ans[1] = tag[j] - 1 + 'A';  
                            ans[2] = tag[k] - 1 + 'A';  
                            ans[3] = tag[l] - 1 + 'A';  
                            ans[4] = tag[m] - 1 + 'A';  
                            ans[5] = '\0';  
                        }  
                    }  
        if(flag)  
            cout << "no solution" << endl;  
        else  
            cout << ans << endl;  
    }  
    return 0;  
}