#include "process_pool.h"

int tranFile(int newFd)
{
    train_t t;
    t.dataLen=strlen(FILENAME);//要转为网络字节序，对端接收到以后，要转主机字节序
    strcpy(t.buf,FILENAME);
    send(newFd,&t,4+t.dataLen,0);//发送文件名
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    //发文件大小
    struct stat buf;
    fstat(fd,&buf);
    t.dataLen=sizeof(buf.st_size);
    memcpy(t.buf,&buf.st_size,t.dataLen);
    send(newFd,&t,4+t.dataLen,0);
    int ret;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    char *pMap=(char*)mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,fd,0);
    off_t pos=0;
    while(buf.st_size-pos>=1000)//发送文件内容
    {
        t.dataLen=1000;
        memcpy(t.buf,pMap+pos,1000);
        ret=send(newFd,&t,4+t.dataLen,0);
        if(-1==ret)
        {
            goto end;
        }       
        pos=pos+1000;
    }
    t.dataLen=buf.st_size-pos;
    memcpy(t.buf,pMap+pos,t.dataLen);
    if(t.dataLen>0)
    {
        send(newFd,&t,4+t.dataLen,0);
    }
    t.dataLen=0;
    send(newFd,&t,4+t.dataLen,0);//告诉客户端文件发送结束
    gettimeofday(&end,NULL);
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
end:
    close(fd);
    return 0;
}

