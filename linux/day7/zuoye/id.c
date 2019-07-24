#include <func.h>

int main(int argc,char* argv[])
{
    printf("真实用户ID：%d\n真实组ID:%d\n有效用户ID：%d\n有效组ID：%d\n", \
           getuid(),getgid(),geteuid(),getegid());
    return 0;
}

