#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    char a[20]={0};
    strcpy(a,"hello");
    char b[6]={0};
    strcpy(b,"world");
    strcat(a,b);
    puts(a);
}

