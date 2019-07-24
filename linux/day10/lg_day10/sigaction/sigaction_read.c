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
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO|SA_RESTART;
    //如果在发生信号时，程序正阻塞在某个系统调用，例如调用
    //read()函数，则在处理完毕信号后，接着从阻塞的系统返回。如
    //果不指定该参数，中断处理完毕之后，read 函数读取失败。
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    char buf[128]={0};
    ret=read(STDIN_FILENO,buf,sizeof(buf));
    printf("ret=%d,buf=%s\n",ret,buf);
    return 0;
}

