#include <func.h>

void change(const int* p)
{
    printf("get value=%d\n",*p);
    //*p=5;
}
int main()
{
    int i=10;
    change(&i);
    printf("i=%d\n",i);
    return 0;
}

