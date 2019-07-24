#include "process_poll.h"

int epollAdd(int epfd,int fd)
{
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=fd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event); //注册fd
    return 0;
}
int main(int argc,char* argv[])
{
    process_data *processData;
    int processNum=atoi(argv[3]);
    processData=(process_data*)calloc(processNum+1,sizeof(process_data));
    MakeChild(processData,processNum);
    int sfd=tcp_init(argv[1],argv[2]);
    int epfd=epoll_create(1);
    epoll_event *evs;
    evs=(epoll_event*)calloc(processNum+1,sizeof(epoll_event));
    epollAdd(epfd,sfd);
    int i;
    for(i=0;i<processNum;i++)
    {
        epollAdd(epfd,processData[i].fd);
    }
    int readyFdCount;
    int newFd,j,flag;
    while(1)
    {
        readyFdCount=epoll_wait(epfd,evs,processNum+1,-1);
        for(i=0;i<processNum+1;i++)
        {
            if(evs[i].data.fd==sfd)
            {
                newFd=accept(sfd,NULL,NULL);
                for(j=0;j<processNum;j++)
                {
                    if(!processData[j].busy)
                    {
                        sendFd(sfd,newFd);
                        processData[j].busy=1;
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
                    processData[j].busy=0;
                    break;
                }
            }
        }
    }
    
}


