#include <func.h>

void print()
{
    printf("I am print");
    exit(10);
    return;
}
int main()
{
    pid_t pid;
    pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,ppid=%d\n",getpid(),getppid());
        print();
        printf("after print\n");
        exit(5);
    }else{
        pid_t wPid;
        int status;
        wPid=wait(&status);
        if(WIFEXITED(status))
        {
            printf("child process exit code=%d\n",WEXITSTATUS(status));
        }else{
            printf("child crash\n");
        }
        printf("recycle process %d\n",wPid);
        return 0;
    }
}

