#include <func.h>
//标准输出放到A文件
//标准错误输出放到B文件
int main()
{
    int fd,fdError;
    fd=open("file",O_RDWR|O_TRUNC);
    ERROR_CHECK(fd,-1,"open");
    fdError=open("file_error",O_RDWR|O_TRUNC);
    ERROR_CHECK(fdError,-1,"open");
    printf("\n");
    int fd1,fdError1;
    fd1=dup2(fd,STDOUT_FILENO);         //不用再像dup那样要先关掉标准输出
    fdError1=dup2(fdError,STDERR_FILENO);
    printf("fd1=%d,fdError1=%d\n",fd1,fdError1);
    printf("you can't see me\n");
    perror("function ok");
    return 0;
}
