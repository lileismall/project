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
    //以上都是在联系服务器，不能说是连接
    //然后接下来就是直接发送信息到服务器
    sendto(socketFd,"hello",5,0,(struct sockaddr*)&serAddr,sizeof(serAddr));//因为没有与服务器建立连接，所以后面两个参数用于指定发往服务器
    char buf[128]={0};
    //接收信息
    recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
    printf("gets %s\n",buf);
    close(socketFd);
    return 0;
}

