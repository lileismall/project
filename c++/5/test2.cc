#include <iostream>
using namespace std;

#define MAX 1024*1024*1024

int main()
{
    int a[MAX];
    int i=0;
    for(i=0;i<MAX;i++)
    {
        a[i]=i;
    }
    cout << a[MAX-1] << endl;
    return 0;
}

