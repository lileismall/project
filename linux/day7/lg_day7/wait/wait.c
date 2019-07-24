#include <func.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,ppid=%d\n",getpid(),getppid());
        return 5;
    }else{
        pid_t wPid;
        int status;
        wPid=wait(&status);      //wait是一直等着子进程的退出，然后清除其尸体，期间不干其他事情，返回的是子进程的pid
        printf("status=%d\n",status);      //status是传出参数，存放的是子进程的退出状态，不用太关心其值是多少
        if(WIFEXITED(status))    //如果子进程是正常结束,WIFEXITED返回是一个非零值，
        {
            printf("child process exit code=%d\n",WEXITSTATUS(status));  //如果 WIFEXITED 非零，返回的是子进程的退出码
        }else{
            printf("child crash\n");
        }
        printf("recycle process %d\n",wPid);
        return 0;
    }
}

