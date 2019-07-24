#include <func.h>
void Newhandler(int signum,siginfo_t *pInfo,void *pReserved)
{
    printf("%d id coming\n",signum);
    sleep(2);
    printf("%d id ending\n",signum);
}
int main(int argc,char* argv[])
{
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));  //结构体清零
    act.sa_flags=SA_SIGINFO|SA_NODEFER;  //打开新处理函数
    act.sa_sigaction=Newhandler; //设置新处理函数
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
}

