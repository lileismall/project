#include <func.h>

int main(int argc,char* argv[])
{
    int num=10000000;
    int shmid=shmget(2000,4096,0600|IPC_CREAT);
    printf("shmid=%d\n",shmid);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p=(int*)shmat(shmid,NULL,0);
    int semid=semget(2000,1,IPC_CREAT|0600);
    printf("semid=%d\n",semid);
    ERROR_CHECK(semid,-1,"semget");
    int ret=semctl(semid,0,SETVAL,1);
    ERROR_CHECK(ret,-1,"semctl");
    p[0]=0;
    struct sembuf sopp,sopv;
    sopp.sem_num=0;
    sopp.sem_op=-1;
    sopp.sem_flg=SEM_UNDO;
    sopv.sem_num=0;
    sopv.sem_op=1;
    sopv.sem_flg=SEM_UNDO;
    if(!fork())
    {
        for(int i=0;i<num;i++)
        {
            ret=semop(semid,&sopp,1);
            ERROR_CHECK(ret,-1,"semop");
            *p += 1;
            ret=semop(semid,&sopv,1);
            ERROR_CHECK(ret,-1,"semop");
        }
    }else{
        for(int i=0;i<num;i++)
        {
            ret=semop(semid,&sopp,1);
            ERROR_CHECK(ret,-1,"semop");
            *p += 1;
            ret=semop(semid,&sopv,1);
            ERROR_CHECK(ret,-1,"semop");
        }
        wait(NULL);
        printf("sum=%d\n",*p);
        shmdt(p);
        shmctl(shmid,IPC_RMID,NULL);
    }
    return 0;
}

