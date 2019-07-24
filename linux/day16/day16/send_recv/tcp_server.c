#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    int newFd;
    struct sockaddr_in clientAddr;
    bzero(&clientAddr,sizeof(clientAddr));
    int addrLen=sizeof(clientAddr);
    newFd=accept(socketFd,(struct sockaddr*)&clientAddr,&addrLen);
    ERROR_CHECK(newFd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
    char buf[1000]={0};
    int i=0;
    while(i<1000)
    {
        ret=recv(newFd,buf,sizeof(buf),0);
        printf("I am server recv=%d\n",ret);
        i++;
    }
    close(newFd);
    close(socketFd);
    return 0;
}

