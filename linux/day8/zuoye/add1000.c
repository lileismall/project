#include <func.h>

int main(int argc,char* argv[])
{
    int num=10000000;
    int shmid=shmget(2000,4096,0600|IPC_CREAT);
    printf("shmid=%d\n",shmid);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p=(int*)shmat(shmid,NULL,0);
    p[0]=0;
    if(!fork())
    {
        for(int i=0;i<num;i++)
        {
            *p += 1;
        }
    }else{
        for(int i=0;i<num;i++)
        {
            *p += 1;
        }
        wait(NULL);
        printf("sum=%d\n",*p);
    }
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}

