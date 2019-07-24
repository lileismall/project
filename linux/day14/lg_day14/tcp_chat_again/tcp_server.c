#include <func.h>
int tcpInit(int *sFd,char* ip,char* port)
{
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(port));
    serAddr.sin_addr.s_addr=inet_addr(ip);
    int ret;
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
    tcpInit(&socketFd,argv[1],argv[2]);
    int newFd;
    struct sockaddr_in clientAddr;
    char buf[128]={0};
    fd_set rdset,needMonitorSet;
    int readyFdCount;
    int ret;
    FD_SET(STDIN_FILENO,&needMonitorSet);//标准输入添加到集合中
    FD_SET(socketFd,&needMonitorSet);
    while(1)
    {
        FD_ZERO(&rdset);
        memcpy(&rdset,&needMonitorSet,sizeof(fd_set));
        readyFdCount=select(15,&rdset,NULL,NULL,NULL);
        if(readyFdCount>0)
        {
            if(FD_ISSET(socketFd,&rdset))
            {
                bzero(&clientAddr,sizeof(clientAddr));
                socklen_t addrLen=sizeof(clientAddr);
                newFd=accept(socketFd,(struct sockaddr*)&clientAddr,&addrLen);
                ERROR_CHECK(newFd,-1,"accept");
                printf("client ip=%s,client port=%d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
                FD_SET(newFd,&needMonitorSet);//新建了一个连接，就添加到监控集合中
            }
            if(FD_ISSET(newFd,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=recv(newFd,buf,sizeof(buf),0);//客户端断开，recv返回值为零，描述符一致可读
                if(0==ret)
                {
                    printf("byebye\n");
                    close(newFd);
                    FD_CLR(newFd,&needMonitorSet);
                }else{
                    printf("%s\n",buf);
                    
                }
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
                if(0==ret)
                {
                    printf("byebye\n");
                    break;
                }
                send(newFd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(socketFd);
    return 0;
}
