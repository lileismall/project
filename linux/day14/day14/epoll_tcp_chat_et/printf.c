#include <func.h>

int main()
{
    printf("this is line %d\n",__LINE__);
    char buf[128]={0};
    read(0,buf,sizeof(buf));
    return 0;
}

