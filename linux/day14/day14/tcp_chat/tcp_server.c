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
    int recvLowVal=20;
    ret=setsockopt(newFd,SOL_SOCKET,SO_RCVLOWAT,&recvLowVal,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);//标准输入添加到集合中
        FD_SET(newFd,&rdset);
        readyFdCount=select(newFd+1,&rdset,NULL,NULL,NULL);
        if(readyFdCount>0)
        {
            if(FD_ISSET(newFd,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=recv(newFd,buf,sizeof(buf),0);//客户端断开，recv返回值为零，描述符一致可读
                if(0==ret)
                {
                    printf("byebye\n");
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                memset(buf,0,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf)-1);
                send(newFd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(newFd);
    close(socketFd);
    return 0;
}
