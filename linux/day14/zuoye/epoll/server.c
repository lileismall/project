#include <func.h>


void setNonBlock(int fd)
{
    int status=fcntl(fd,F_GETFL);
    status=status|O_NONBLOCK;
    fcntl(fd,F_SETFL,status);
}

int tcp_init(const char* ip,char* port)  //用于初始化操作
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in serve_addr;
    bzero(&serve_addr,sizeof(serve_addr));
    serve_addr.sin_family=AF_INET;
    serve_addr.sin_port=htons(atoi(port));
    serve_addr.sin_addr.s_addr=inet_addr(ip);
    int ret=bind(sfd,(struct sockaddr*)&serve_addr,sizeof(serve_addr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sfd,10);
    return sfd;
}
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int sfd=tcp_init(argv[1],argv[2]);
    ERROR_CHECK(sfd,-1,"tcp_init");
    int newFd;
    struct sockaddr_in clientaddr;
    bzero(&clientaddr,sizeof(clientaddr));
    char buf[5]={0};
    int readyCount;
    //开始注册
    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");
    struct epoll_event event,evs[3];
    event.events=EPOLLIN;//表示对应的文件描述符可以读
    event.data.fd=STDIN_FILENO;
    //监控
    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=sfd;//监视sfd，一旦有客户连接，sfd就可读
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int i;
    while(1)
    {
        readyCount=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<readyCount;i++)
        {
            if(sfd==evs[i].data.fd)
            {
                bzero(&clientaddr,sizeof(clientaddr));
                socklen_t addrlen=sizeof(clientaddr);
                newFd=accept(sfd,(struct sockaddr*)&clientaddr,&addrlen);
                ERROR_CHECK(newFd,-1,"accept");
                setNonBlock(newFd);//将sfd设置为非阻塞
                printf("client ip:%s ,client port:%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
                event.data.fd=newFd;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newFd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
            }
            if(newFd==evs[i].data.fd)
            {
                while(1)
                {
                    memset(buf,0,sizeof(buf));
                    ret=recv(newFd,buf,sizeof(buf)-1,0);
                    if(0==ret)
                    {
                        printf("再见\n");
                        event.events=EPOLLIN;
                        event.data.fd=newFd;
                        ret=epoll_ctl(epfd,EPOLL_CTL_DEL,newFd,&event);
                        ERROR_CHECK(ret,-1,"epoll_ctl");
                        close(newFd);
                        break;
                    }else if(-1==ret&&errno==EAGAIN)
                    {
                        break;
                    }else
                    {
                        printf("%s\n",buf);
                    }
                }
            }
            if(STDIN_FILENO==evs[i].data.fd)
            {
                printf("this is %d\n",__LINE__);
                memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf)-1);
                if(0==ret)
                {
                    printf("bye\n");
                    goto end;
                }
                send(newFd,buf,strlen(buf)-1,0);
            }
        }
    }
end:
    close(newFd);
    close(sfd);
    return 0;
}

