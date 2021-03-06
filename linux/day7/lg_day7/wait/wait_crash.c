#include <func.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,ppid=%d\n",getpid(),getppid());
        pid=1/0;
        return 5;
    }else{
        pid_t wPid;
        int status;
        wPid=wait(&status);
        printf("status=%d\n",status);
        if(WIFEXITED(status))    //根据其退出状态，WIFEXITED返回的是0
        {
            printf("child process exit code=%d\n",WEXITSTATUS(status));
        }else{
            printf("child crash\n");
        }
        printf("recycle process %d\n",wPid);
        return 0;
    }
}

