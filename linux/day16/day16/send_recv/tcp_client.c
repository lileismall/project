#include <func.h>
void sigFunc(int signum)
{
    printf("%d is coming\n",signum);
}
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
//    signal(SIGPIPE,sigFunc);
    //对端关闭后，再给对方send就会挂掉
    int total=0;
    while(1)
    {
        ret=send(socketFd,buf,sizeof(buf),0);
        total+=ret;
        printf("I am client send=%d\n",total);
       // if(-1==ret)
       // {
       //     break;
       // }
    }
    close(socketFd);
    return 0;
}
