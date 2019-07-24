#include <func.h>

int main()
{
    sigset_t procMask;
    sigemptyset(&procMask);
    sigaddset(&procMask,SIGINT);
    int ret=sigprocmask(SIG_BLOCK,&procMask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    sleep(5);
    ret=sigprocmask(SIG_UNBLOCK,&procMask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    return 0;
}

