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
    ret=connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");
    char buf[128]={0};
    fd_set rdset;
    int readyFdCount;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);//标准输入添加到集合中
        FD_SET(socketFd,&rdset);
        readyFdCount=select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(readyFdCount>0)
        {
            if(FD_ISSET(socketFd,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=recv(socketFd,buf,sizeof(buf),0);
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
                send(socketFd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(socketFd);
    return 0;
}
