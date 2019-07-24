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
    recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&clientAddr,&len);//除了接收buf中信息，还要将client的ip等信息接住，用于下面的sendto函数
    printf("gets %s\n",buf);
    printf("client ip=%s,client port=%d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
    sendto(socketFd,"world",5,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
    close(socketFd);
    return 0;
}

