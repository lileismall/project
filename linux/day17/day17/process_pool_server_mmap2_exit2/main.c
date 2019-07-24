#include "process_pool.h"

int exitFds[2];
void sigExitFunc(int signum)
{
    printf("%d is coming\n",signum);
    write(exitFds[1],&signum,1);
}
int epollAdd(int epfd,int fd)
{
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=fd;
    int ret;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,4);
    pipe(exitFds);
    signal(SIGUSR1,sigExitFunc);
    int processNum=atoi(argv[3]);
    pProcessData_t pMainData=(pProcessData_t)calloc(processNum,sizeof(ProcessData_t));
    makeChild(pMainData,processNum);
    int socketFd;
    int ret;
    ret=tcpInit(&socketFd,argv[1],argv[2]);
    ERROR_CHECK(ret,-1,"tcpInit");
    int epfd=epoll_create(1);
    struct epoll_event *evs;
    evs=(struct epoll_event*)calloc(processNum+2,sizeof(struct epoll_event));
    epollAdd(epfd,socketFd);
    int i;
    for(i=0;i<processNum;i++)
    {
        epollAdd(epfd,pMainData[i].fds);
    }
    //accept接收任务，循环遍历，找到非忙碌子进程，将任务发送给它
    //如果发现子进程的管道对端可读，找到对应子进程，将其标识为非忙碌
    int readyFdCount,newFd,j;
    char flag;
    epollAdd(epfd,exitFds[0]);
    while(1)
    {
        readyFdCount=epoll_wait(epfd,evs,processNum+2,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(evs[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                for(j=0;j<processNum;j++)
                {
                    if(!pMainData[j].busy)
                    {
                        sendFd(pMainData[j].fds,newFd,0);
                        pMainData[j].busy=1;
                        printf("pid %d is busy\n",pMainData[j].pid);
                        break;
                    }
                }
                close(newFd);
            }
            if(evs[i].data.fd==exitFds[0])//服务器应用升级，要退出了
            {
                printf("exit start\n");
                for(j=0;j<processNum;j++)
                {
                    sendFd(pMainData[j].fds,0,1);//通知每个子进程退出
                }
                for(j=0;j<processNum;j++)
                {
                    int status;
                    pid_t pid;
                    pid=wait(&status);
                    if(WIFEXITED(status))
                    {
                        printf("pid=%d exit code=%d\n",pid,WEXITSTATUS(status));
                    }
                }
                close(socketFd);
                exit(0);
            }
            for(j=0;j<processNum;j++)
            {
                if(evs[i].data.fd==pMainData[j].fds)
                {
                    read(pMainData[j].fds,&flag,1);
                    printf("pid %d is not busy\n",pMainData[j].pid);
                    pMainData[j].busy=0;
                    break;
                }
            }
        }
    }
    return 0;
}

