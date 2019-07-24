#include <func.h>
int recvCycle(int,void*,int);
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
    int dataLen;
    char buf[1000]={0};
    //接收文件名
    recvCycle(socketFd,&dataLen,4);
    recvCycle(socketFd,buf,dataLen);
    off_t fileSize,downLoadSize=0;
    recvCycle(socketFd,&dataLen,4);
    recvCycle(socketFd,&fileSize,dataLen);
    printf("fileSize=%ld\n",fileSize);
    int fd;
    fd=open(buf,O_WRONLY|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    time_t before,now;
    //接文件内容
    before=now=time(NULL);
    while(1)
    {
        recvCycle(socketFd,&dataLen,4);
        if(dataLen>0)
        {
            recvCycle(socketFd,buf,dataLen);
            write(fd,buf,dataLen);
            downLoadSize+=dataLen;
            now=time(NULL);
            if(now>before)
            {
                printf("%5.2f%%\r",(double)downLoadSize/fileSize*100);
                fflush(stdout);
                before=now;
            }
        }else{
            printf("100.00%%\n");
            break;
        }
    }
    close(fd);
    close(socketFd);
}
