#include <func.h>

void sigFunc(int signum,siginfo_t *p,void* p1)
{
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    printf("after sleep %d is coming\n",signum);
}
int main()
{
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO|SA_NODEFER;  
    //在处理信号时，如果又发生了其它的信号，则立即进入其它信
    //号的处理，等其它信号处理完毕后，再继续处理当前的信号，
    //即递规地处理。
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

