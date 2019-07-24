#include <func.h>
int tcpInit(int *sFd,char* ip,char* port)
{
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    int ret;
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(port));
    serAddr.sin_addr.s_addr=inet_addr(ip);
    ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    *sFd=socketFd;
    return 0;
}
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    int ret;
    ret=tcpInit(&socketFd,argv[1],argv[2]);
    if(-1==ret)
    {
        return -1;
    }
    int newFd;
    struct sockaddr_in clientAddr;
    bzero(&clientAddr,sizeof(clientAddr));
    socklen_t addrLen=sizeof(clientAddr);
    newFd=accept(socketFd,(struct sockaddr*)&clientAddr,&addrLen);
    ERROR_CHECK(newFd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
    char buf[128]={0};
    fd_set rdset;
    int readyFdCount;
    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;
    event.data.fd=STDIN_FILENO;
    //开始监控标准输入的读事件
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=newFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int i;
    while(1)
    {
        readyFdCount=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(newFd==evs[i].data.fd)
            {
                memset(buf,0,sizeof(buf));
                ret=recv(newFd,buf,sizeof(buf),0);//客户端断开，recv返回值为零，描述符一致可读
                if(0==ret)
                {
                    printf("byebye\n");
                    goto end;
                }
                printf("%s\n",buf);
            }
            if(STDIN_FILENO==evs[i].data.fd)
            {
                memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf)-1);
                send(newFd,buf,strlen(buf)-1,0);
            }
        }
    }
end:
    close(newFd);
    close(socketFd);
    return 0;
}
