#include <func.h>

int main()
{
    pid_t pid;
    char *p=(char*)malloc(20);
    strcpy(p,"hello");
    pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,ppid=%d %s\n",getpid(),getppid(),p);
    }else{
        printf("I am parent process,mychildpid=%d,pid=%d %s\n",pid,getpid(),p);
        strcpy(p,"world");
        printf("I am parent process,mychildpid=%d,pid=%d %s\n",pid,getpid(),p);
        sleep(1);
    }
    return 0;
}

