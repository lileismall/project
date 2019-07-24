#include <func.h>
//进程间的dup,两个文件描述符指向同一个文件对象
int main()
{
    pid_t pid;
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    pid=fork();
    if(0==pid)
    {
        char buf[128]={0};
        read(fd,buf,5);
        printf("I am child process,mypid=%d,ppid=%d %s\n",getpid(),getppid(),buf);
    }else{
        char buf[128]={0};
        read(fd,buf,5);
        printf("I am parent process,mychildpid=%d,pid=%d %s\n",pid,getpid(),buf);
        sleep(1);
    }
    return 0;
}

