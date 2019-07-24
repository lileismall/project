#include "process_poll.h"

int handleChild(int pipeFd)
{
    int newFd;
    while(1)
    {
        recvFd(pipeFd,&newFd);
        write(pipeFd,&newFd,1); //随便写点东西
        //中间来干自己想干的事情
        close(newFd); //最后关掉描述符
    }
}
int makeChild(process_data *p,int processNum)
{
    pid_t pid;
    int i,fds[2];
    for(i=0;i<processNum;i++)
    {
        socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        pid=fork();
        if(!pid)
        {
            close(fds[1]);
            handleChild(fds[0]); //里面要有循环
        }
        else
        {
            close(fds[0]);
            p[i].pid=pid;
            p[i].fd=fds[1];
            p[i].busy=0;

        }
    }
    return 0;
}


