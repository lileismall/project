#include "process_poll.h"

int tranFile(int newFd)
{
    tran_file t;
    //发文件名
    t.datalen=strlen(FILENAME);
    strcpy(t.buf,FILENAME);
    send(newFd,&t,4+t.datalen,0);
    int fd=open(FILENAME,O_RDONLY);
    int ret;
    //发内容
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

