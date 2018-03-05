#include <iostream>

using namespace std;

int main(void)
{
    int n;
    while (cin>>n && n>0)
    {
        if (n%8==2 || n%8==6)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}