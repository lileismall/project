#include "process_poll.h"

int MakeChild(process_data* p,int processNum)
{
    pid_t pid;
    int i;
    int fds[2];
    for(i=0;i<processNum;i++)
    {
        //将socketpair生成的套接字描述符的一段给子进程，一端给父进程，用来传递信息
        //可以用来传递是否忙碌，和描述符的传递
        int ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(!pid)
        {
            close(fds[0]);
            ChildHandle(fds[1]);
        }
        close(fds[1]);
        p[i].pid=pid;
        p[i].busy=0;
        p[i].fd=fds[0];
    }
    return 0;

int ChildHandle(int fd)
{
    int newFd;
    while(1)
    {
        recvFd(fd,&newFd);
        printf("i get task,the newFd is:%d\n",newFd);
        printf("finish\n");
        write(fd,&newFd,1);  //随便写点东西就可以，告诉父进程可读，即告诉自己不忙碌
        close(newFd);
    }
}
