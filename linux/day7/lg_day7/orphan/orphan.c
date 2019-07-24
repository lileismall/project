#include <func.h>

int main()
{
    pid_t pid;
    int iStack=10;
    pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,ppid=%d %d\n",getpid(),getppid(),iStack);
        while(1);
    }else{
        printf("I am parent process,mychildpid=%d,pid=%d %d\n",pid,getpid(),iStack);
    }
    return 0;
}

