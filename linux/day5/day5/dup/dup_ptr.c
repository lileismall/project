#include <func.h>
//dup后内核里只有一个文件对象，只有一个ptr指针
int main()
{
    int fd,fd1;
    fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    fd1=dup(fd);
    printf("fd1=%d\n",fd1);
    char buf[128]={0};
    int ret;
    lseek(fd,5,SEEK_SET);
    ret=read(fd1,buf,5);
    ERROR_CHECK(ret,-1,"read");
    printf("buf=%s\n",buf);
    return 0;
}

