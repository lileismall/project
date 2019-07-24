#include <func.h>

int main()
{
    signal(SIGINT,SIG_IGN);
    sigset_t procMask,pending;
    sigemptyset(&procMask);
    sigaddset(&procMask,SIGINT);
    int ret=sigprocmask(SIG_BLOCK,&procMask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    sleep(5);
    sigemptyset(&pending);
    sigpending(&pending);
    if(sigismember(&pending,SIGINT))
    {
        printf("SIGINT is pending\n");
    }else{
        printf("SIGINT is not pending\n");
    }
    ret=sigprocmask(SIG_UNBLOCK,&procMask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    return 0;
}

