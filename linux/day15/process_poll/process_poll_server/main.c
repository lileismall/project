#include "process_poll.h"

int epollAdd(int epfd,int fd)
{
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=fd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    return 0;
}

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,4);
    int processNum=atoi(argv[3]); //第四个参数是要创建的子进程数目
    process_data *processData=(process_data*)calloc(processNum,sizeof(processData));
    MakeChild(processData,processNum);
    int sfd=tcp_init(argv[1],argv[2]);
    ERROR_CHECK(sfd,-1,"tcp_init");
    int epfd=epoll_create(1);
    epollAdd(epfd,sfd);
    struct epoll_event *evs=(struct epoll_event*)calloc(processNum+1,sizeof(struct epoll_event));
    for(int i=0;i<processNum;i++)
    {
        epollAdd(epfd,processData[i].fd);  //注册所有子进程的描述符
    }
    int readyFdCount;
    int ret,i,j;
    char flag;
    int newFd;
    while(1)
    {
        readyFdCount=epoll_wait(epfd,evs,processNum+1,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(evs[i].data.fd==sfd)
            {
                newFd=accept(sfd,NULL,NULL); //这里不用接住客户端信息，用不到，但是内核里知道
                for(j=0;j<processNum;j++)
                {
                    if(0==processData[j].busy)
                    {
                        sendFd(processData[j].fd,newFd);
                        processData[j].busy=1;
                        printf("pid %d is busy\n",processData[j].pid);
                        break;
                    }
                }
                close(newFd);
            }
            for(j=0;j<processNum;j++)
            {
                if(evs[i].data.fd==processData[j].fd)
                {
                    read(processData[j].fd,&flag,1);
                    printf("%d i am not busy\n",processData[j].pid);
                    processData[j].busy=0;
                    break;
                }
            }
        }
    }
    return 0;
}

