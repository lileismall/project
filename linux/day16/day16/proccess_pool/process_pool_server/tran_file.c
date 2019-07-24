#include "process_pool.h"

int tranFile(int newFd)
{
    train_t t;
    t.dataLen=strlen(FILENAME);//要转为网络字节序，对端接收到以后，要转主机字节序
    strcpy(t.buf,FILENAME);
    send(newFd,&t,4+t.dataLen,0);//发送文件名
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    int ret;
    while((t.dataLen=read(fd,t.buf,sizeof(t.buf))))//发送文件内容
    {
        ret=send(newFd,&t,4+t.dataLen,0);
        if(-1==ret)
        {
            goto end;
        }       
    }
    send(newFd,&t,4+t.dataLen,0);//告诉客户端文件发送结束
end:
    close(fd);
    return 0;
}

