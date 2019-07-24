#include <func.h>

void setNonBlock(int fd)
{
    int status=fcntl(fd,F_GETFL);
    status=status|O_NONBLOCK;
    fcntl(fd,F_SETFL,status);
}
void setBlock(int fd)
{
    int status=fcntl(fd,F_GETFL);
    status=status&~O_NONBLOCK;
    fcntl(fd,F_SETFL,status);
}
int main()
{
    printf("this is line %d\n",__LINE__);
    char buf[128]={0};
    sleep(5);
    setNonBlock(0);
    setBlock(0);
    int ret=read(0,buf,sizeof(buf));
    printf("ret=%d,buf=%s,errno=%d\n",ret,buf,errno);
    return 0;
}

