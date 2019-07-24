#include <func.h>

int main()
{
    pid_t pid;
    pid=fork();
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
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

