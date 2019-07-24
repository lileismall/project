#include <func.h>

void sigFunc(int signum,siginfo_t *p,void* p1)
{
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    sigset_t pending;
    sigpending(&pending);  //sigpending函数的参数类型是sigset_t型指针
    if(sigismember(&pending,SIGQUIT))   //判断SIGQUIT是否被阻塞(挂起)，成功返回0，失败返回-1
    {
        printf("SIGQUIT is pending\n");
    }else{
        printf("SIGQUIT is not pending\n");
    }
    printf("after sleep %d is coming\n",signum);
}
int main()
{
    int ret;
    struct sigaction act;  //要记住act只是一种行为
    /*
     *      struct sigaction {
     *      void     (*sa_handler)(int);
     *      void     (*sa_sigaction)(int, siginfo_t *, void *);
     *      sigset_t   sa_mask;
     *      int        sa_flags;
     *     };
     * 
     * */

    bzero(&act,sizeof(act)); 
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO;
    sigemptyset(&act.sa_mask);  //清空信号集
    sigaddset(&act.sa_mask,SIGQUIT); //增加阻塞信号,只会在SIGINT(因为是sigaction函数的第一个参数)前阻塞
    ret=sigaction(SIGINT,&act,NULL); 
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

