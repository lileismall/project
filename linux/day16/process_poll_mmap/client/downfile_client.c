#include <func.h>
int recv_cycle(int,void*,int);
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
    recv_cycle(socketFd,&dataLen,4);
    recv_cycle(socketFd,buf,dataLen);
    //接收文件大小
    off_t filesize;
    recv_cycle(socketFd,&dataLen,4);
    recv_cycle(socketFd,&filesize,dataLen);
    printf("filesize:%ld\n",filesize);
    int fd;
    fd=open(buf,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    struct timeval start,end;
    gettimeofday(&start,NULL);
    ftruncate(fd,filesize);
    printf("this is line:%d\n",__LINE__);
    char *pMap=(char*)mmap(NULL,filesize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(pMap,(char*)-1,"mmap");
    printf("this is line:%d\n",__LINE__);
    ret=recv_cycle(socketFd,pMap,filesize);
    ERROR_CHECK(ret,-1,"recv_cycle");
    printf("this is line:%d\n",__LINE__);
    munmap(pMap,filesize);
    gettimeofday(&end,NULL);
    printf("use time is:%ld\n",end.tv_sec-start.tv_sec);
    close(fd);
    close(socketFd);
}
