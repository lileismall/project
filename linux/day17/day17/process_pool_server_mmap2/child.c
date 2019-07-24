#include "process_pool.h"

int makeChild(pProcessData_t p,int processNum)
{
    int i;
    pid_t pid;
    int fds[2];
    int ret;
    for(i=0;i<processNum;i++)
    {
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(0==pid)
        {
            close(fds[1]);
            signal(SIGUSR1,SIG_DFL);
            childHandle(fds[0]);
        }//子进程不从这个if出来
        close(fds[0]);
        p[i].pid=pid;
        p[i].fds=fds[1];
        p[i].busy=0;
    }
    return 0;
}

int childHandle(int pipeFd)
{
    int newFd;
    while(1)
    {
        recvFd(pipeFd,&newFd);//接收任务
        printf("I am child,get task %d\n",newFd);
        tranFile(newFd);
        close(newFd);
        write(pipeFd,&newFd,1);//通知父进程我非忙碌
    }
}

