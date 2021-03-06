#include <func.h>
void sigFunc(int signum)//信号处理函数
{
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    printf("after sleep %d is coming\n",signum);
}
typedef void (*sighandler_t)(int);
int main()
{
    sighandler_t p;
    p=signal(SIGINT,sigFunc);
    ERROR_CHECK(p,SIG_ERR,"signal");
    signal(SIGQUIT,sigFunc);
    while(1);
    return 0;
}

