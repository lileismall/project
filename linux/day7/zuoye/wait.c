#include <func.h>

int main(int argc,char* argv[])
{
    int pid=fork();
    if(pid==0)
    {
        sleep(3);
        exit(1);
    }else{
        int status;
        pid=wait(&status);   //statu是传出参数
        if(WIFEXITED(status))  //根据返回状态，子进程正常退出，返回非零值
        {
            printf("子进程的退出码是：%d\n",WEXITSTATUS(status));
        }else{
            printf("crash\n");
        }
    }
}

