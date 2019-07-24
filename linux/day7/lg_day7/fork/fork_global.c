#include <func.h>

int iStack=10;
int main()
{
    pid_t pid;
    pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,ppid=%d %d\n",getpid(),getppid(),iStack);
    }else{
        printf("I am parent process,mychildpid=%d,pid=%d %d\n",pid,getpid(),iStack);
        iStack=5;
        printf("I am parent process,mychildpid=%d,pid=%d %d\n",pid,getpid(),iStack);
        sleep(1);
    }
    return 0;
}
