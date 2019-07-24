#include "process_poll.h"
int recvCycle(int fd,void*,int);

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
    ret=connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");
    char buf[1000]={0};
    int datalen;
    int fd;
    recvCycle(socketFd,&datalen,4);//读文件名
    recvCycle(socketFd,buf,datalen);
    fd=open(buf,O_WRONLY|O_CREAT,0600);
    while(1)
    {
        ret=recvCycle(socketFd,&datalen,4);
        if(ret>0)
        {
            recvCycle(socketFd,buf,datalen);
            write(fd,buf,datalen);
        }else{
            printf("下载成功\n");
            goto end;
        }
    }
end:
    close(socketFd);
    close(fd);
    return 0;
}

