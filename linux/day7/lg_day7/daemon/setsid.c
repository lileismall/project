#include <func.h>
//获得进程组ID
int main()
{
    pid_t pid;
    pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,ppid=%d pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
        setsid();
        printf("I am child process,mypid=%d,ppid=%d pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
        while(1);
    }else{
        printf("I am parent process,mychildpid=%d,pid=%d pgid=%d,sid=%d\n",pid,getpid(),getpgid(0),getsid(0));
        wait(NULL);
    }
    return 0;
}

