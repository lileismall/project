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
    int ret;
    while((t.datalen=read(fd,t.buf,sizeof(t.buf))))
    {
        ret=send(newFd,&t,4+t.datalen,0);
        if(ret==-1)
        {
            goto end;
        }
        
    }
    send(newFd,&t,4+t.datalen,0);
end:
    close(fd);
    return 0;
}

