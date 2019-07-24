#include <func.h>

int main()
{
    int semArrId=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");
    int ret;
    struct semid_ds buf;
    ret=semctl(semArrId,0,IPC_STAT,&buf);
    ERROR_CHECK(ret,-1,"semctl");
    printf("uid=%d,mode=%o,nsems=%ld\n",buf.sem_perm.uid,buf.sem_perm.mode,buf.sem_nsems);
    buf.sem_perm.mode=0666;
    ret=semctl(semArrId,0,IPC_SET,&buf);
    return 0;
}

