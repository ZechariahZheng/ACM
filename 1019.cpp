#include <iostream>
#include <cstring>

using namespace std;

void func(string *input)
{
    char *data = (char *)input->data();
    int num = input->size();
    int n = 1;
    
    for (int i = 0; i < num; i++)
    {
        if (data[i] == data[i+1])
        {
            n++;
        }
        else
        {
            if (n > 1)
                printf("%d", n);
            printf("%c", data[i])
        }
    }
    printf("\n");
}

int main(void)
{
    int n;
    string tmp;
    
    while (cin>>n && n>0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> tmp;
            func(&tmp);
        }
    }
}