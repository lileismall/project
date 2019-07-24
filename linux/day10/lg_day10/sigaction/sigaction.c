#include <func.h>

void sigFunc(int signum,siginfo_t *p,void* p1)
{
    printf("%d is coming\n",signum);
}
int main()
{
    int ret;
    struct sigaction act; 
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;   //设置新处理函数
    act.sa_flags=SA_SIGINFO;    //将新处理函数打开
    ret=sigaction(SIGINT,&act,NULL); //第三个参数为回收老处理函数，为NULL，则不回收
    ERROR_CHECK(ret,-1,"sigaction");//sigaction函数成功返回0，失败返回-1
    while(1);
    return 0;
}

