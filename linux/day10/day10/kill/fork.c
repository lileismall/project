#include <func.h>

int main()
{
    if(!fork())
    {
        printf("I am child\n");
        while(1);
        return 0;
    }else{
        printf("I am parent\n");
        while(1);
        return 0;
    }
}

