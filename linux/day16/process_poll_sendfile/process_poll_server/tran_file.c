#include "process_poll.h"

int tranFile(int newFd)
{
    tran_file t;
    t.datalen=strlen(FILENAME);//发文件名
    strcpy(t.buf,FILENAME);
    send(newFd,&t,4+t.datalen,0);
    int fd=open(FILENAME,O_RDONLY);
    struct stat buf;
    fstat(fd,&buf);
    t.datalen=sizeof(buf.st_size);
    memcpy(t.buf,&buf.st_size,t.datalen);
    send(newFd,&t,4+t.datalen,0);//发文件大小
    struct timeval start,end;
    gettimeofday(&start,NULL);
    sendfile(newFd,fd,NULL,buf.st_size);
    t.datalen=0;
    send(newFd,&t,4+t.datalen,0);//发送文件结束
    gettimeofday(&end,NULL);
    printf("use time is : %ld\n",end.tv_sec-start.tv_sec);
    close(fd);
    return 0;
}

