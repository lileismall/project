#include <func.h>
//子进程复制父进程的堆空间，与父进程的堆空间分割开来

int main()
{
    pid_t pid;
    char *p=(char*)malloc(20);
    strcpy(p,"hello");
    pid=fork();
    if(0==pid)
    {
        sleep(1);
        printf("I am child process,mypid=%d,ppid=%d %s\n",getpid(),getppid(),p);
    }else{
        printf("I am parent process,mychildpid=%d,pid=%d %s\n",pid,getpid(),p);
        strcpy(p,"world");
        printf("I am parent process,mychildpid=%d,pid=%d %s\n",pid,getpid(),p);
        sleep(5);
    }
    return 0;
}

