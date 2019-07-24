#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    //绑定以后端口就会开启
    ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in clientAddr;
    bzero(&clientAddr,sizeof(clientAddr));
    socklen_t len=sizeof(clientAddr);
    char buf[128]={0};
    recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&clientAddr,&len);
    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        ret=select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf)-1);
            sendto(socketFd,buf,strlen(buf)-1,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
        }
        if(FD_ISSET(socketFd,&rdset))
        {
            memset(buf,0,sizeof(buf));
            recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
            printf("%s\n",buf);
        }
    }
    close(socketFd);
    return 0;
}

